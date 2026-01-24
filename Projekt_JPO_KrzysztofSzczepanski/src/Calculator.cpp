#include "Calculator.h"
#include <cmath> // do log10

using std::make_unique;

// Konstruktor: Inicjalizuje wynik na 0 i ustawia domyslny system (DEC).
CalculatorEngine::CalculatorEngine() : aktualnyWynik(0) {
    aktualnySystem = make_unique<SystemDec>();
}

// Ustawia nowa wartosc biezacego wyniku (nadpisuje stary).
// INPUT: w (nowa wartosc typu double)
// OUTPUT: brak (void)
void CalculatorEngine::ustawWynik(double w) { aktualnyWynik = w; }

void CalculatorEngine::dodaj(double w) { aktualnyWynik += w; }       // }    Odejmuje/mnozy/dodaje podana liczbe od aktualnego wyniku
void CalculatorEngine::odejmij(double w) { aktualnyWynik -= w; }     // }    INPUT: w (liczba która dodajemy/odejmujemy/mnozymy)
void CalculatorEngine::pomnoz(double w) { aktualnyWynik *= w; }      // }    OUTPUT: brak(void)

// Dzieli aktualny wynik przez podana liczbe.
// INPUT: w (dzielnik)
// OUTPUT: true jesli sukces, false jesli proba dzielenia przez 0
bool CalculatorEngine::podziel(double w) {
    if (w == 0) return false;
    aktualnyWynik /= w;
    return true;
}
// Przelicza aktualny wynik na decybele (Moc: 10*log10).
// INPUT: brak (operuje na stanie wewnetrznym)
// OUTPUT: true jesli sukces, false jesli wynik <= 0 (blad matematyczny)
bool CalculatorEngine::konwertujNaDbMoc() {
    if (aktualnyWynik <= 0) return false;
    aktualnyWynik = 10.0 * log10(aktualnyWynik);
    return true;
}
// Przelicza aktualny wynik na decybele (Napiecie: 20*log10).
// INPUT: brak (operuje na stanie wewnetrznym)
// OUTPUT: true jesli sukces, false jesli wynik <= 0 (blad matematyczny)
bool CalculatorEngine::konwertujNaDbNapiecie() {
    if (aktualnyWynik <= 0) return false;
    aktualnyWynik = 20.0 * log10(aktualnyWynik);
    return true;
}

// Resetuje wynik do zera.
void CalculatorEngine::wyczysc() { aktualnyWynik = 0; }

// Zmienia strategie formatowania wyniku (System liczbowy).
// INPUT: tryb (1=DEC, 2=BIN, 3=HEX, 4=OCT)
// OUTPUT: brak
void CalculatorEngine::ustawSystem(int tryb) {
    switch (tryb) {
    case 1: aktualnySystem = make_unique<SystemDec>(); break;
    case 2: aktualnySystem = make_unique<SystemBin>(); break;
    case 3: aktualnySystem = make_unique<SystemHex>(); break;
    case 4: aktualnySystem = make_unique<SystemOct>(); break;
    default: aktualnySystem = make_unique<SystemDec>(); break;
    }
}

// Zwraca sformatowany tekst wyniku (zaleznie od wybranego systemu).
// INPUT: brak
// OUTPUT: string z reprezentacja liczby
std::string CalculatorEngine::pobierzWynikString() {
    return aktualnySystem->sformatujLiczbe(aktualnyWynik);
}

// Zwraca nazwe aktualnie uzywanego systemu liczbowego.
// INPUT: brak
// OUTPUT: string z nazwa systemu
std::string CalculatorEngine::pobierzNazweSystemu() {
    return aktualnySystem->pobierzNazwe();
}