#include <iostream>
#include <vector>
#include <random>
using std::cin,std::cout,std::vector,std::endl;


//Kod tworzy macierz  wypelniona liczbami losowymi o liczbie kolumn i wierszy wprowadzonej jako argument

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(0, 100);




vector<vector<double>> rozmiar(int w,int k){
        vector<vector<double>> G(w,vector<double>(k,1.0));
        for (auto& r:G) {
                for (auto& j:r){
 			j = dist(gen);
			cout<< j << "\t";}
        cout<<endl;}
return G;
}

vector<vector<double>> mnozenie(vector<vector<double>> L,vector<vector<double>> O){
if (L[0].size()==O.size()){
	int wiersze = L.size();
		int kolumny = O[0].size();
		int kolumny_L = L[0].size();
	vector<vector<double>> wynik(wiersze,vector<double>(kolumny,0.0));
for (auto i:wiersze){
	for (auto j:kolumny){
		for(auto k:kolumny_L){
			wynik[i][j] +=L[i][k] * O[k][j];
		}
	}
}


	return wynik;
}
else {
	cout<<"ZLY ROZMIAR MACIERZY"<<endl;}
}



int kolumny,wiersze,kolumny2,wiersze2;
int main(){

        cout<< "Podaj liczbe wierszy:" <<endl;
        cin >> wiersze;
        cout<<"Podaj liczbe kolumn:" << endl;
        cin >> kolumny;
        cout<< "Podaj liczbe wierszy2:" <<endl;
       cin >> wiersze2;
        cout<<"Podaj liczbe kolumn2:" << endl;
      cin >> kolumny2;

  rozmiar(wiersze,kolumny);
       vector<vector<double>> C =  rozmiar(wiersze,kolumny);
       vector<vector<double>> P =  rozmiar(wiersze2,kolumny2);


return 0;
}


