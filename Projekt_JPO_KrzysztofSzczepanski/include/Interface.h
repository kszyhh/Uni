#pragma once
#include "Calculator.h" 

class ConsoleInterface {
private:
    CalculatorEngine kalkulator;

    void wyczyscEkran();
    void pokazNaglowek();

public:
    void uruchom();
};