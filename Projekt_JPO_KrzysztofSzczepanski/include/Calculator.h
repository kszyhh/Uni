#pragma once
#include <memory>
#include <string>
#include "Systems.h" 

class CalculatorEngine {
private:
    double aktualnyWynik{};
    std::unique_ptr<ISystemWyswietlania> aktualnySystem{};

public:
    CalculatorEngine();

  
    void ustawWynik(double w);
    void dodaj(double w);
    void odejmij(double w);
    void pomnoz(double w);
    bool podziel(double w);


    bool konwertujNaDbMoc();
    bool konwertujNaDbNapiecie();

    void wyczysc();
    void ustawSystem(int tryb);

    std::string pobierzWynikString();
    std::string pobierzNazweSystemu();
};