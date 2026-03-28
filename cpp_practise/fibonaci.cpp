#include <iostream>
#include <vector> 

int main()
{

	std::vector<int> G;

	int a{},i{},b{1};

	while(i < 50)
	{
	//	G.push_back(a);
		G.push_back(b);

		int tmp_a = a; 
		a = b;
		b = tmp_a + b;
		i++;
	}

	for (auto i : G)
	{
		std::cout << i << " ";
	}










}
