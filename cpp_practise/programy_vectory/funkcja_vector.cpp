#include <iostream>
#include <vector>
using std::cin,std::cout,std::vector,std::endl;


//Kod tworzy vector wypelniony jedynkami o liczbie kolumn wprowadzonej jako argument


vector<double> rozmiar(int k){
	vector<double> G(k,1.0);
	for (auto r:G) cout << r << "\t";
return G;
}	

int kolumny,wiersze;
int main(){

	//cout<< "Podaj liczbe wierszy:" <<endl;
	//cin >> wiersze;
	cout<<"Podaj liczbe kolumn:" << endl;
	cin >> kolumny;
	rozmiar(kolumny);




return 0;
}

