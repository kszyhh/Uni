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
        for (auto r:G) {
                for (auto j:r){
 			j = dist(gen);
			cout<< j << "\t";}
        cout<<endl;}
return G;
}

int kolumny,wiersze;
int main(){

        cout<< "Podaj liczbe wierszy:" <<endl;
        cin >> wiersze;
        cout<<"Podaj liczbe kolumn:" << endl;
        cin >> kolumny;
        rozmiar(wiersze,kolumny);




return 0;
}


