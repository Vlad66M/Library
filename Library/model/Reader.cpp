#include "stdafx.h"
#include "Reader.h"


namespace Model {
	static std::vector<Reader> g_readers;
	std::ofstream readersFile;
	std::ifstream getReaders;

	Address AddAddress()
	{
		std::cout << "\nAdding person's registration address\n";
		Address tmp;
		std::cout << "\nEnter the city name:\n";
		std::cin >> tmp.city;
		std::cout << "Enter the street name:\n";
		std::cin >> tmp.street;
		std::cout << "Enter the bulding number:\n";
		std::cin >> tmp.building;
		std::cout << "Enter the appartment number:\n";
		std::cin >> tmp.apartment;
		return tmp;
	}

	void GetReaders() {
		getReaders.open("data/readers.txt");
		if (getReaders.is_open()) {
			std::string tmp;
			std::string previous{ "" };
			Reader empty;
			while (!getReaders.eof()) {
				std::getline(getReaders, tmp);
				if (tmp == "Id") {
					g_readers.push_back(empty);
				}
				if (previous == "Id") {
					g_readers.back().idReader = std::stoi(tmp);
				}
				if (previous == "Document number") {
					g_readers.back().documentNumber = std::stoi(tmp);
				}
				if (previous == "Name") {
					g_readers.back().who.name = tmp;
				}
				if (previous == "Patrinomic") {
					g_readers.back().who.patrinomic = tmp;
				}
				if (previous == "Surname") {
					g_readers.back().who.surname = tmp;
				}
				if (previous == "City") {
					g_readers.back().address.city = tmp;
				}
				if (previous == "Street") {
					g_readers.back().address.street = tmp;
				}
				if (previous == "Building") {
					g_readers.back().address.building = std::stoi(tmp);
				}
				if (previous == "Apartment") {
					g_readers.back().address.apartment = std::stoi(tmp);
				}
				previous = tmp;
			}
			getReaders.close();
		}
		else {
			std::cout << "\nThere are no readers! You need to add a reader first";
		}
	}

	void UpdateReadersFile() {
		readersFile.open("data/readers.txt");
		if (readersFile.is_open()) {
			for (int i = 0; i < g_readers.size(); i++) {
				readersFile << "Id\n" << g_readers[i].idReader << "\nDocument number\n" << g_readers[i].documentNumber <<
					"\nName\n" << g_readers[i].who.name << "\nPatrinomic\n" << g_readers[i].who.patrinomic <<
					"\nSurname\n" << g_readers[i].who.surname << "\nAddress\nCity\n" << g_readers[i].address.city <<
					"\nStreet\n" << g_readers[i].address.street << "\nBuilding\n" << g_readers[i].address.building <<
					"\nApartment\n" << g_readers[i].address.apartment << "\n";
			}
			readersFile.close();
		}
		else {
			std::cout << "\nThere are no readers! You need to add a reader first";
		}
	}

	void AddReader()
	{
		std::cout << "\nAdding a new reader";
		Reader tmp;
		Human tmpHuman;
		tmpHuman = AddHuman();
		Address tmpAddress;
		tmpAddress = AddAddress();
		tmp.who = tmpHuman;
		tmp.address = tmpAddress;
		std::cout << "\nEnter the reader's document number\n";
		std::cin >> tmp.documentNumber;
		if (g_readers.empty()) {
			tmp.idReader = 0;
		}
		else {
			tmp.idReader = g_readers.back().idReader + 1;
		}
		g_readers.push_back(tmp);
		readersFile.open("data/readers.txt", std::ofstream::app);
		readersFile << "\nId\n" << g_readers.back().idReader << "\nDocument number\n" << g_readers.back().documentNumber <<
			"\nName\n" << g_readers.back().who.name << "\nPatrinomic\n" << g_readers.back().who.patrinomic <<
			"\nSurname\n" << g_readers.back().who.surname << "\nAddress\nCity\n" << g_readers.back().address.city <<
			"\nStreet\n" << g_readers.back().address.street << "\nBuilding\n" << g_readers.back().address.building <<
			"\nApartment\n" << g_readers.back().address.apartment << "\n";
		readersFile.close();
	}

	void ChangeReaderName() {
		std::cout << "\nChanging the name of the reader\nEnter Id of the reader\n";
		int id;
		std::cin >> id;
		bool isFound{ false };
		for (int i = 0; i < g_readers.size(); i++) {
			if (g_readers[i].idReader == id) {
				std::cout << "\nEnter the correct name\n";
				std::cout << "Enter reader's name\n";
				std::string tmpName;
				std::cin >> tmpName;
				std::cout << "Enter reader's patrinomic\n";
				std::string tmpPatrinomic;
				std::cin >> tmpPatrinomic;
				std::cout << "Enter reader's surname\n";
				std::string tmpSurname;
				std::cin >> tmpSurname;
				g_readers[i].who.name = tmpName;
				g_readers[i].who.patrinomic = tmpPatrinomic;
				g_readers[i].who.surname = tmpSurname;
				UpdateReadersFile();
				isFound = true;
				break;
			}
		}
		if (!isFound) {
			std::cout << "The reader has not been found";
		}
	}

	void ChangeReaderDocument() {
		std::cout << "\nChanging document number of the reader\nEnter Id of the reader\n";
		int id;
		std::cin >> id;
		bool isFound{ false };
		for (int i = 0; i < g_readers.size(); i++) {
			if (g_readers[i].idReader == id) {
				std::cout << "\nEnter the correct document number\n";
				int tmpDocument;
				std::cin >> tmpDocument;
				g_readers[i].documentNumber = tmpDocument;
				UpdateReadersFile();
				isFound = true;
				break;
			}
		}
		if (!isFound) {
			std::cout << "The reader has not been found";
		}
	}

	void DeleteReader() {
		std::cout << "\nDeleting the reader\nEnter Id of the reader you want to delete\n";
		int id;
		std::cin >> id;
		bool isDeleted{ false };
		for (int i = 0; i < g_readers.size(); i++) {
			if (g_readers[i].idReader == id) {
				g_readers.erase(g_readers.begin() + i);
				UpdateReadersFile();
				std::cout << "The reader with Id " << id << " has been deleted";
				isDeleted = true;
				break;
			}
		}
		if (!isDeleted) {
			std::cout << "The reader with Id " << id << " has not been found";
		}
	}
}

