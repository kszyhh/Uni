#include <gtest/gtest.h>
#include "../include/Calculator.h" 

TEST(KalkulatorTest, PodstawoweDodawanie) {
    CalculatorEngine calc;
    calc.ustawWynik(10.5);
    calc.dodaj(2.5);
    
    EXPECT_EQ(calc.pobierzWynikString(), "13.0000");
}

TEST(KalkulatorTest, OdejmowanieUjemne) {
    CalculatorEngine calc;
    calc.ustawWynik(10);
    calc.odejmij(15); 
 
    EXPECT_EQ(calc.pobierzWynikString(), "-5.0000");
}

TEST(KalkulatorTest, Mnozenie) {
    CalculatorEngine calc;
    calc.ustawWynik(4);
    calc.pomnoz(2.5);
   
    EXPECT_EQ(calc.pobierzWynikString(), "10.0000");
}

TEST(KalkulatorTest, DzieleniePoprawne) {
    CalculatorEngine calc;
    calc.ustawWynik(20);
    bool sukces = calc.podziel(4);
    
    EXPECT_TRUE(sukces); 
    EXPECT_EQ(calc.pobierzWynikString(), "5.0000");
}



TEST(KalkulatorTest, OchronaPrzedDzieleniemPrzezZero) {
    CalculatorEngine calc;
    calc.ustawWynik(100);
    
    
    bool sukces = calc.podziel(0);
    
    EXPECT_FALSE(sukces); 
    EXPECT_EQ(calc.pobierzWynikString(), "100.0000"); 
}

TEST(KalkulatorTest, OchronaLogarytmuLiczbaUjemna) {
    CalculatorEngine calc;
    calc.ustawWynik(-50); 
    
   
    bool sukces = calc.konwertujNaDbMoc();
    
    EXPECT_FALSE(sukces); 
}



TEST(KalkulatorSystemy, KonwersjaNaHex) {
    CalculatorEngine calc;
    calc.ustawWynik(255); 
    
    
    calc.ustawSystem(3);
    
    EXPECT_EQ(calc.pobierzWynikString(), "0xFF");
    EXPECT_EQ(calc.pobierzNazweSystemu(), "HEX (Szesnastkowy)");
}

TEST(KalkulatorSystemy, KonwersjaNaBin) {
    CalculatorEngine calc;
    calc.ustawWynik(5); 
    
    calc.ustawSystem(2); 
    
    
    EXPECT_EQ(calc.pobierzWynikString(), "0000000000000101");
}