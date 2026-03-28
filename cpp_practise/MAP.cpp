#include <iostream>
#include <map>
#include <vector>

using std::string, std::map, std::vector, std::cout, std::cin, std::endl;

int main() {

	map<string, vector<string>> tłumacz;

	tłumacz["car"] = vector<string>{"auto","samochod"};
	tłumacz["lamp"] = vector<string>{ "lampa" };
	tłumacz["keyboard"] = vector<string>{ "klawiatura" };

	string g;

    while (1) {
        cout << endl << "Tlumacz czy quiz?" << endl;
        cin >> g;
        if (g == "tlumacz")
        {
            cout << "Podaj slowo po angielsku" << endl;
            cin >> g;

            auto it = tłumacz.find(g);

            if (it != tłumacz.end()) {
                cout << "Tlumaczenia dla \"" << g << "\":" << endl;
                for (auto& polskie : it->second) {
                    cout << "- " << polskie << endl;
                }
            }
            else {
                cout << "Brak tlumaczenia dla \"" << g << "\"" << endl;
            }
        }
        else if (g == "quiz") {
          
            int idx = rand() % tłumacz.size();
            auto it = tłumacz.begin();
            std::advance(it, idx);

            cout << "Podaj tlumaczenie dla: " << it->first << endl;
            string odpowiedz;
            cin >> odpowiedz;

            // sprawdzanie odpowiedzi
            bool poprawne = false;
            for (auto& polskie : it->second) {
                if (odpowiedz == polskie) {
                    poprawne = true;
                    break;
                }
            }

            if (poprawne) {
                cout << "Brawo! Poprawna odpowiedz." << endl;
            }
            else {
                cout << "Niestety, poprawne tlumaczenia to:" << endl;
                for (auto& polskie : it->second) {
                    cout << "- " << polskie << endl;
                }
            }
        }
        else cout << "nie ma takiej opcji" << endl;
        
       

    }
}