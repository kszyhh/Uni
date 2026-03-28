#include <iostream>
#include <vector>
using std::cout,std::endl,std::vector;

int main(){
	vector v{3,5,1};
	cout << "Rozmiar wektora="<<v.size()<<endl;

	for (auto e:v) cout << e << endl;
	
	vector<vector<double>> m = { {3,5,7,1},{23,6,2.2,5},{5,1,11,3}};
	cout << "Rozmiar wektora="<<m.size()<<"x"<<m[0].size()<<endl;
	
	for (auto r : m){
	      
	
		for (auto g : r) cout << g << "\t";
	cout <<endl;
	}

cout<< endl;
	
	return 0;

}
// wyswietlanie wektora i macierzy

