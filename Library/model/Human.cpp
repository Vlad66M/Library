#include "stdafx.h"
#include "Human.h"

namespace Model {
	Human AddHuman()
	{
		Human tmp;
		std::cout << "\nEnter the person's name\n";
		std::cin >> tmp.name;
		std::cout << "Enter the person's patrinomic\n";
		std::cin >> tmp.patrinomic;
		std::cout << "Enter the person's surname\n";
		std::cin >> tmp.surname;
		return tmp;
	}
}
