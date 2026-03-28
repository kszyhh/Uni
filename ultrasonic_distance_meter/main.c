#include "MKL05Z4.h"
#include "frdm_bsp.h"
#include "lcd1602.h"
#include "TPM.h"
#include "tsi.h"
#include "DAC.h"
#include "klaw.h"
#include <stdio.h>

typedef enum {
    UNIT_M = 0, UNIT_CM = 1, UNIT_MM = 2, UNIT_INCH = 3
} Unit_Type;

volatile uint16_t start_czas = 0, koniec_czas = 0, wynik_ticks = 0;
volatile uint8_t gotowe = 0;
volatile uint8_t alarm_wlaczony = 0;
volatile uint8_t wave_index = 0;

char buffer[16]; 
Unit_Type current_unit = UNIT_CM; 
uint8_t bariera_alarmu = 10; 
uint8_t tsi_val = 0;
uint8_t tryb_edycji = 0;

// Dzwiek z DAC 
void SysTick_Handler(void) {
    if (alarm_wlaczony) {
        // generowanie fali prostokątnej 
        DAC_Load_Trig((wave_index < 16) ? 4095 : 0); 
        wave_index = (wave_index + 1) & 31; 
    } else {
        DAC_Load_Trig(0);
        wave_index = 0;
    }
}

void Ultrasonice_Init(void) {
	//konfiguracja pinów do sonika
    SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
    PORTB->PCR[5] = PORT_PCR_MUX(1UL); //PTB5 GPIO trigger
    PTB->PDDR |= (1UL << 5);  
    PTB->PCOR = (1UL << 5); 
    PORTB->PCR[7] = PORT_PCR_MUX(2UL); //PTB7 do licznika TPM0

	//konfiguracja timera
    SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK; 
    SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1); 
    TPM0->SC = TPM_SC_PS(5); // Prescaler 32
    TPM0->MOD = 0xFFFF; // max zakres
    TPM0->CONTROLS[2].CnSC = TPM_CnSC_ELSB_MASK | TPM_CnSC_ELSA_MASK | TPM_CnSC_CHIE_MASK; //reakcja na oba zbocza, przerwanie
    TPM0->SC |= TPM_SC_CMOD(1); //start licznika
    NVIC_ClearPendingIRQ(TPM0_IRQn);
    NVIC_EnableIRQ(TPM0_IRQn); //wlaczenie przerwan
}

// przerwanie sonika
void TPM0_IRQHandler(void) {
    if (TPM0->CONTROLS[2].CnSC & TPM_CnSC_CHF_MASK) {  
        TPM0->CONTROLS[2].CnSC |= TPM_CnSC_CHF_MASK; // kasowaniee flagi jedynka
        if (PTB->PDIR & (1<<7)) { 
            start_czas = TPM0->CONTROLS[2].CnV; //zapisujemy czas start czasu 
        } else { //jesli zbocze opadajace 
            koniec_czas = TPM0->CONTROLS[2].CnV; //zapisujemy koniec czasu 
            wynik_ticks = (koniec_czas >= start_czas) ? // obliczanie czasu trwania impulsu 
                          (koniec_czas - start_czas) : 
                          ((0xFFFF - start_czas) + koniec_czas);
            gotowe = 1; //flaga sukces
        }
    }
}

// Zwraca przeliczoną wartość i ustawia wskaźnik na nazwę jednostki
float Convert_Unit(uint8_t val_cm, const char **unit_str) {
    switch(current_unit) {
        case UNIT_M:    *unit_str = "m "; return val_cm / 100.0f;
        case UNIT_MM:   *unit_str = "mm"; return val_cm * 10.0f;
        case UNIT_INCH: *unit_str = "in"; return val_cm / 2.54f;
        default:        *unit_str = "cm"; return (float)val_cm;
    }
}

int main(){
	//odpalanie sprzętu 
    LCD1602_Init();
    LCD1602_Backlight(TRUE);
    LCD1602_ClearAll();
    
    Klaw_Init();
    Klaw_S2_4_Int(); 
    Ultrasonice_Init();
    
    DAC_Init(); 
    SysTick_Config(1500);  // dla dźwięku ~1000hz 
    TSI_Init();

    // menu wyboru 
    LCD1602_Print("S1:m  S2:cm");
    LCD1602_SetCursor(0, 1);
    LCD1602_Print("S3:mm S4:cal");

    while(1) {
        if(!(PTA->PDIR & S1_MASK)) { 
            DELAY(100) //eliminacja drgan
            if(!(PTA->PDIR & S1_MASK)) { current_unit = UNIT_M; break; }
        }
        if(S2_press) { S2_press = 0; current_unit = UNIT_CM; break; }
        if(S3_press) { S3_press = 0; current_unit = UNIT_MM; break; }
        if(S4_press) { S4_press = 0; current_unit = UNIT_INCH; break; }
    }
    
    LCD1602_ClearAll();
    LCD1602_Print("Dystans:");

    while(1) {
        // obsluga miziaka, ustawianie alarmu
        tsi_val = TSI_ReadSlider();
        
        if (tsi_val > 0) {
            if (!tryb_edycji) {
                LCD1602_ClearAll();
                LCD1602_Print("Ustaw alarm:");
                tryb_edycji = 1;
            }
            
            bariera_alarmu = (tsi_val / 2);
            if (bariera_alarmu == 0) bariera_alarmu = 1; 
            
            const char *u_str; //*
            float val = Convert_Unit(bariera_alarmu, &u_str);
            
            // mm jako int reszta float
            if(current_unit == UNIT_MM) sprintf(buffer, "Lim: %d %s    ", (int)val, u_str);
            else sprintf(buffer, "Lim: %.2f %s   ", val, u_str);
            
            LCD1602_SetCursor(0, 1);
            LCD1602_Print(buffer);
            alarm_wlaczony = 0;
            
            DELAY(500)
            continue; 
        } else if (tryb_edycji) {  //po zabraniu palca 
            LCD1602_ClearAll();  
            LCD1602_Print("Dystans:");
            tryb_edycji = 0;
        }

        // pomiar
        PTB->PSOR = (1UL << 5);
        DELAY(1);                //wyslanie impulsu
        PTB->PCOR = (1UL << 5);

        int timeout = 50000; 
        while(!gotowe && timeout > 0) timeout--;  //czekamy na powrot fali

        if(gotowe) {
					uint32_t dist_cm = wynik_ticks * 78 / 5800; 
            if (dist_cm > 400) dist_cm = 400; //bo limit sonika 

            alarm_wlaczony = (dist_cm < bariera_alarmu);

            const char *u_str;
            float val_disp = Convert_Unit((uint8_t)dist_cm, &u_str);
						float lim_disp = Convert_Unit(bariera_alarmu, &u_str); // przeliczanie limitu alarmu

            LCD1602_SetCursor(0, 1);
            if(current_unit == UNIT_MM) {
                sprintf(buffer, "%d%s (L:%d)   ", (int)val_disp, u_str, (int)lim_disp);
            } else {
                sprintf(buffer, "%.2f%s(L:%.1f)  ", val_disp, u_str, lim_disp);
            }
            LCD1602_Print(buffer);
            gotowe = 0;
        }
        DELAY(500);
    }
}