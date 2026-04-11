#include<vector>
#include <iostream>
#include <map>
#include <string>

class EMatrix
{
    public:
    int rows{};
    int columns{};
    std::vector<std::vector<int>> G;
    int liczba{};
    
    EMatrix(int x = 1, int y = 1) : rows(x) , columns(y) , G(x,std::vector<int>(y,1)) {};
    
    std::tuple<int,int> wymiary(void)
    {
        return {rows,columns};
    }
    
    void odczyt (int row,int column)
    {
        std::cout << G[row][column] << std::endl;
        
    }
    
    void zapis(int row, int column, int liczba)
    {
        G[row][column] = liczba;
    }
};

int main()
{
    EMatrix cos(5,6);
    
    auto g = cos.wymiary();
    std::cout << std::get<0>(g) <<" "<< std::get<1>(g) << std::endl;
    
    cos.zapis(4,3,10);
    cos.odczyt(4,3);

}



