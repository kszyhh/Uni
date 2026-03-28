#include <iostream>
#include <vector>
#include <string>
#include <fstream>

struct Addr
{
	std::string ulica;
	int numer_domu{};
	std::string miasto;
};


struct Person
{
	int age{};
	std::string imie;
	Addr adres{};
};


std::ostream& operator<<(std::ostream& o, Person& p)
{
	o << p.age << " ";
	o << p.imie << " ";
	o << p.adres.ulica << " " ;
	o << p.adres.numer_domu << " ";
	o << p.adres.miasto; 
	return o;
}

std::istream& operator>>(std::istream& i, Person& p)
{

	std::cout<<"Podaj wiek:"<<std::endl;
	i >> p.age;

	std::cout<<"Podaj imie:"<<std::endl;
	i >> p.imie;

	std::cout<<"Podaj ulice:"<<std::endl;
	i >> p.adres.ulica;

	std::cout<<"Podaj nr domu:"<<std::endl;
	i >> p.adres.numer_domu;

	std::cout<<"Podaj miasto:"<<std::endl;
	i >> p.adres.miasto; 
	return i;
}

int main(){

	std::vector<Person> baza;

	Person y{};
	std::cin>>y;
	baza.push_back(y);
	std::cout<<y<<std::endl;



}
