#include <KCCSVParser.hpp>
#include <iostream>
int main()
{
	std::cout << "Trying to start parser.." << std::endl;
	KC::CSVParser<int,std::string,double> parser("data.csv",1);
	std::cout << "Trying to read from file..." << std::endl;
	auto lines = parser.ReadFile();
	std::cout << "done" << std::endl;
	for (auto i : lines)
	{
		int a = std::get<0>(i);
		std::string b = std::get<1>(i);
		double c = std::get<2>(i);
		std::cout << a << " " << a + 1 << std::endl;
		std::cout << b << std::endl;
		std::cout << c << " " << c / 2 << std::endl;
		std::cout << std::endl;
	}

	std::cin.get();
}
