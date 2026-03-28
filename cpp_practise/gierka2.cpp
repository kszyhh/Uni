#include <iostream>
#include <vector>
#include <random>
using std::cin, std::cout,std::endl,std::vector;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dist(0,9);

int main(){
	
	vector<vector<char>> matrix(10,vector<char>(10,'.'));
	int x =0 , y=0;
	matrix[x][y] = 'P';	
	while(1){
		for (auto& i : matrix){
			for (auto& j:i){
				if(j == 'X') j = '.';
			}
		}
		int cos = 0;	
		while (cos <3){	
			int a = dist(gen);
			int b = dist(gen);
			if(! (a == 0 && b == 0)){
				if (matrix[a][b] == '.'){
				matrix[a][b] = 'X';
				cos++;
				}
				else if (matrix[a][b] == 'P'){
				       	system("clear");
					cout << "GAME OVER" << endl;
					break;
				}
			}	
		}	
		system("clear");
		for (auto i : matrix){
		 	cout << endl;
			for(auto j : i) cout << j << "    ";
			}	
	cout << "Poruszanie się za pomocą AWSD, wyjscie za pomoca q" << endl;
	char move{};
	cin >> move; 
	matrix[x][y] = '.';	

if (move == 'w' && x > 0 ) x-- ;
else if ( move == 's' && x < 9 ) x++;
else if ( move == 'd' && y < 9 ) y++;
else if (move == 'a' && y > 0) y--;
else if (move == 'q') break;
matrix[x][y] = 'P';
	}
system("clear");
cout << "GAME OVER"<<endl;
}
