#include <iostream>
#include <vector>
#include <random>
using std::cin, std::cout, std::vector, std::endl;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<double> dist(0.0, 100.0); // Zmiana na double dla spójności

vector<vector<double>> rozmiar(int w, int k) {
    vector<vector<double>> G(w, vector<double>(k, 1.0));
    for (auto& r : G) {
        for (auto& j : r) {
            j = dist(gen);
            cout << j << "\t";
        }
        cout << endl;
    }
    return G;
}

vector<vector<double>> mnozenie(vector<vector<double>> L, vector<vector<double>> O) {
    if (L[0].size() == O.size()) {
        vector<vector<double>> wynik(L.size(), vector<double>(O[0].size(), 0.0));
        
        int i = 0;
        for (auto& wiersz_wyniku : wynik) {
            int j = 0;
            for (auto& element : wiersz_wyniku) {
                int k = 0;
                for (auto& element_L : L[i]) {
                    element += element_L * O[k][j];
                    k++;
                }
                j++;
            }
            i++;
        }
        return wynik;
    }
    else {
        cout << "ZLY ROZMIAR MACIERZY" << endl;
        return vector<vector<double>>();
    }
}

int main() {
    int kolumny, wiersze, kolumny2, wiersze2;
    
    cout << "Podaj liczbe wierszy:" << endl;
    cin >> wiersze;
    cout << "Podaj liczbe kolumn:" << endl;
    cin >> kolumny;
    cout << "Podaj liczbe wierszy2:" << endl;
    cin >> wiersze2;
    cout << "Podaj liczbe kolumn2:" << endl;
    cin >> kolumny2;

    cout << "Macierz C:" << endl;
    vector<vector<double>> C = rozmiar(wiersze, kolumny);
    
    cout << "Macierz P:" << endl;
    vector<vector<double>> P = rozmiar(wiersze2, kolumny2);
    
    // Mnożenie macierzy
    vector<vector<double>> wynik = mnozenie(C, P);
    
    // Wyświetlenie wyniku
    cout << "Wynik mnozenia:" << endl;
    for (auto& wiersz : wynik) {
        for (auto& element : wiersz) {
            cout << element << "\t";
        }
        cout << endl;
    }

    return 0;
}
