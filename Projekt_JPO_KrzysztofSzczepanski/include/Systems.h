#pragma once
#include <string>


class ISystemWyswietlania {
public:
    virtual std::string sformatujLiczbe(double liczba) = 0;
    virtual std::string pobierzNazwe() = 0;
};

// --- SystemDec --------------------------------------------
class SystemDec : public ISystemWyswietlania {
public:
    std::string sformatujLiczbe(double liczba) override;
    std::string pobierzNazwe() override;
};

// --- SystemBin ---------------------------------------------
class SystemBin : public ISystemWyswietlania {
public:
    std::string sformatujLiczbe(double liczba) override;
    std::string pobierzNazwe() override;
};

// --- SystemHex ---------------------------------------------
class SystemHex : public ISystemWyswietlania {
public:
    std::string sformatujLiczbe(double liczba) override;
    std::string pobierzNazwe() override;
};

// --- SystemOct ---------------------------------------------
class SystemOct : public ISystemWyswietlania {
public:
    std::string sformatujLiczbe(double liczba) override;
    std::string pobierzNazwe() override;
};