#include "Systems.h"
#include <sstream>
#include <iomanip>
#include <bitset>

using std::string;

// --- SystemDec -------------------------------------------------------------------------------
// Formatuje liczbe w systemie dziesietnym (4 miejsca po przecinku).
// INPUT: liczba (wartosc do wyswietlenia)
// OUTPUT: string w formacie "X.XXXX"
string SystemDec::sformatujLiczbe(double liczba) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(4) << liczba;
    return ss.str();
}

// Zwraca czytelna nazwe systemu dziesietnego.
// INPUT: brak
// OUTPUT: nazwa systemu
string SystemDec::pobierzNazwe() { return "DEC (Dziesietny)"; }

// --- SystemBin -------------------------------------------------------------------------------
// Konwertuje czesc calkowita liczby na system dwojkowy (16 bitow).
// INPUT: liczba (czesc ulamkowa jest ignorowana)
// OUTPUT: string zlozony z 0 i 1
string SystemBin::sformatujLiczbe(double liczba) {
    long long calkowita = static_cast<long long>(liczba);
    return std::bitset<16>(calkowita).to_string();
}

// Zwraca czytelna nazwe systemu binarnego.
// INPUT: brak
// OUTPUT: nazwa systemu
string SystemBin::pobierzNazwe() { return "BIN (Binarny)"; }

// --- SystemHex -------------------------------------------------------------------------------
// Konwertuje czesc calkowita liczby na system szesnastkowy.
// INPUT: liczba (czesc ulamkowa jest ignorowana)
// OUTPUT: string z prefiksem 0x i wielkimi literami
string SystemHex::sformatujLiczbe(double liczba) {
    long long calkowita = static_cast<long long>(liczba);
    std::stringstream ss;
    ss << "0x" << std::uppercase << std::hex << calkowita;
    return ss.str();
}
string SystemHex::pobierzNazwe() { return "HEX (Szesnastkowy)"; }

// --- SystemOct -------------------------------------------------------------------------------
// Konwertuje czesc calkowita liczby na system osemkowy.
// INPUT: liczba (czesc ulamkowa jest ignorowana)
// OUTPUT: string z prefiksem 0
string SystemOct::sformatujLiczbe(double liczba) {
    long long calkowita = static_cast<long long>(liczba);
    std::stringstream ss;
    ss << "0" << std::oct << calkowita;
    return ss.str();
}

// Zwraca czytelna nazwe systemu osemkowego.
// INPUT: brak
// OUTPUT: nazwa systemu
string SystemOct::pobierzNazwe() { return "OCT (Osemkowy)"; }