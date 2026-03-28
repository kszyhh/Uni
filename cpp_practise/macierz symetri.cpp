
#include <iostream>
#include <vector>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(0, 100);

std::vector<std::vector<int>> funkcja(int w, int k){              //funkcja tworząca macierz w x k wypełnioną zerami

	std::vector<std::vector<int>> matrix(w,std::vector<int>(k,dist(gen))); 
	
	for(auto& x:matrix) {
		for( auto& g: x) {
			g = dist(gen);
			std::cout << g << '\t';
		}
		std::cout<<std::endl;
	}

//	for(int i{};i < w, i++){
//		for ( int j{};j < k, j++){
//			if(matrix[i][j] == matrix[j][i]) std::cout<<"Macierz symetryczna"<<std::endl;
//			else std::cout<<"macierz niesymetryczna"<<std::endl;
//		}
//	}


	return matrix;
}

int w = 0, k = 0;

int main(){
	
	std::cout<<"podaj liczbe wierszy:"<<std::endl;
	std::cin >> w;
	std::cout << "podaj liczbe kolumn" << std::endl;
	std::cin>>k;
	
	std::vector<std::vector<int>> matrix;
	matrix = funkcja(w,k);

bool symetria;
 for(int i{};i < w; i++){
                for ( int j{};j < k; j++){
                        if(matrix[i][j] != matrix[j][i]) 
			{
				symetria = false; 
				break;}
			else{	symetria == true;
				break;}
		}
		if (symetria == false) break;
		else{ symetria == true;
			break;
		}
        }

if (symetria == true) std::cout<<"Macierz symetryczna" << std::endl;
else std::cout << "Macierz niesymetryczna" << std::endl;
















}



