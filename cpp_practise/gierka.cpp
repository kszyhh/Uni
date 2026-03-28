#include <iostream>
#include <vector>
#include <random>
using std::cin, std::cout,std::endl,std::vector;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(0,9);


int main(){



vector<vector<char>> matrix(10,vector<char>(10,'.'));


matrix[0][0] = 'P';
matrix[9][9] = 'T';
while(1){
	int cos = 0;
	while ( cos < 3 ) {
	int x = dist(gen);
	int y = dist(gen);

	if(!( x == 0 && y == 0)){
	       if(!(x == 9 && y == 0)){	
	
	if (matrix[x][y] == '.'){
		matrix [x][y] = 'X';
			cos++;
	}
	}
	}
	}

for(auto i : matrix) {
	for (auto j : i) cout << j << "  ";
	cout << endl;
}

char move {};
cin >> move
;

}


}

