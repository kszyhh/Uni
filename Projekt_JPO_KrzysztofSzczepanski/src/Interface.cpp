#include "Interface.h"
#include <iostream>
#include <cstdlib> // Dla system()

using std::cout;
using std::endl;
using std::cin;

// Czysci ekran konsoli (kompatybilne z Windows i Linux/macOS).
void ConsoleInterface::wyczyscEkran() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Wyswietla naglowek aplikacji, aktualny system liczbowy oraz wynik.
void ConsoleInterface::pokazNaglowek() {
    wyczyscEkran();
    cout << "==========================================" << endl;
    cout << "   KALKULATOR INZYNIERSKI (JPO)            " << endl;
    cout << "==========================================" << endl;
    cout << "System: " << kalkulator.pobierzNazweSystemu() << endl;
    cout << "WYNIK:  [" << kalkulator.pobierzWynikString() << "]" << endl;
    cout << "==========================================" << endl;
}

// Glowna petla programu. Obsluguje menu i interakcje z uzytkownikiem.
void ConsoleInterface::uruchom() {
    int opcja = 0;
    double liczba = 0;


    while (true) {
        pokazNaglowek();
        // Wyswietlenie menu glownego
        cout << "--- Dzialania ---" << endl;
        cout << "1. Wpisz nowa liczbe (Reset i ustaw)" << endl;
        cout << "2. Dodaj (+)" << endl;
        cout << "3. Odejmij (-)" << endl;
        cout << "4. Pomnoz (*)" << endl;
        cout << "5. Podziel (/)" << endl;
        cout << "--- Konwersja na dB (przelicz aktualny wynik) ---" << endl;
        cout << "6. Na dB (Moc: 10*log)" << endl;
        cout << "7. Na dB (Napiecie: 20*log)" << endl;
        cout << "--- Ustawienia ---" << endl;
        cout << "8. Zmien System (DEC/BIN/HEX/OCT)" << endl;
        cout << "9. Wyjscie" << endl;
        cout << "Twoj wybor: ";
        cin >> opcja;

        if (opcja == 9) break;
        // --- Sekcja dzialan arytmetycznych (1-5) ---
        if (opcja >= 1 && opcja <= 5) {
            cout << "Podaj liczbe: ";
            cin >> liczba;

            switch (opcja) {
            case 1: kalkulator.ustawWynik(liczba); break;
            case 2: kalkulator.dodaj(liczba); break;
            case 3: kalkulator.odejmij(liczba); break;
            case 4: kalkulator.pomnoz(liczba); break;
            case 5:
                if (!kalkulator.podziel(liczba)) {
                    cout << "Blad: Dzielenie przez 0! Wcisnij Enter.";
                    cin.ignore(); cin.get();
                }
                break;
            }
        }
        // --- Sekcja konwersji  (6-7) ---
        else if (opcja == 6) {
            if (!kalkulator.konwertujNaDbMoc()) {
                cout << "Blad: Nie mozna liczyc logarytmu z liczby <= 0! Enter...";
                cin.ignore(); cin.get();
            }
        }
        else if (opcja == 7) {
            if (!kalkulator.konwertujNaDbNapiecie()) {
                cout << "Blad: Nie mozna liczyc logarytmu z liczby <= 0! Enter...";
                cin.ignore(); cin.get();
            }
        }
        // --- Sekcja ustawiania systemu (8) ---
        else if (opcja == 8) {
            cout << "Wybierz system: 1.DEC, 2.BIN, 3.HEX, 4.OCT: ";
            int s{}; cin >> s;
            kalkulator.ustawSystem(s);
        }
    }
}