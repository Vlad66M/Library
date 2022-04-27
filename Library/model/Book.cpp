#include "stdafx.h"
#include "Book.h"
#include "Reader.h"

#pragma warning(disable : 4996)

namespace Model {
	static std::vector<Book> g_all_books;
	static std::vector<Book> g_available_books;
	std::ofstream allBooksFile;
	std::ifstream getAllBooks;
	std::ofstream availableBooksFile;
	std::ifstream getAvailableBooks;

	void GetAllBooks() {
		getAllBooks.open("data/all_books.txt");
		std::string tmp;
		std::string previous{ "" };
		Book empty;
		if (getAllBooks.is_open()) {
			while (!getAllBooks.eof()) {
				std::getline(getAllBooks, tmp);
				if (tmp == "Id") {
					g_all_books.push_back(empty);
				}
				if (previous == "Id") {
					g_all_books.back().id = std::stoi(tmp);
				}
				if (previous == "Author Id") {
					g_all_books.back().authorId = std::stoi(tmp);
				}
				if (previous == "Name") {
					g_all_books.back().name = tmp;
				}
				if (previous == "Year") {
					g_all_books.back().bookYear = std::stoi(tmp);
				}
				if (previous == "Rack") {
					g_all_books.back().location.rack = std::stoi(tmp);
				}
				if (previous == "Shelf") {
					g_all_books.back().location.shelf = std::stoi(tmp);
				}
				if (previous == "Section") {
					g_all_books.back().location.section = std::stoi(tmp);
				}
				if (previous == "Registration") {
					auto secondsSinceEpoch = std::stoi(tmp);
					std::chrono::system_clock::time_point tp{ std::chrono::seconds{secondsSinceEpoch} };
					g_all_books.back().regestration = tp;
					/*time_t t = std::chrono::system_clock::to_time_t(g_all_books.back().regestration);
					std::cout << std::endl << "secondsSinceEpoch " << secondsSinceEpoch;
					std::cout << std::endl << "Date is " << ctime(&t);*/
				}
				previous = tmp;
			}
			getAllBooks.close();
		}
		else {
			std::cout << "\nThere're no books! You need to add a book first";
		}
		
	}

	void GetAvailableBooks() {
		getAvailableBooks.open("data/available_books.txt");
		std::string tmp;
		std::string previous{ "" };
		Book empty;
		if (getAvailableBooks.is_open()) {
			while (!getAvailableBooks.eof()) {
				std::getline(getAvailableBooks, tmp);
				if (tmp == "Id") {
					g_available_books.push_back(empty);
				}
				if (previous == "Id") {
					g_available_books.back().id = std::stoi(tmp);
				}
				if (previous == "Author Id") {
					g_available_books.back().authorId = std::stoi(tmp);
				}
				if (previous == "Name") {
					g_available_books.back().name = tmp;
				}
				if (previous == "Year") {
					g_available_books.back().bookYear = std::stoi(tmp);
				}
				if (previous == "Rack") {
					g_available_books.back().location.rack = std::stoi(tmp);
				}
				if (previous == "Shelf") {
					g_available_books.back().location.shelf = std::stoi(tmp);
				}
				if (previous == "Section") {
					g_available_books.back().location.section = std::stoi(tmp);
				}
				if (previous == "Registration") {
					auto secondsSinceEpoch = std::stoi(tmp);
					std::chrono::system_clock::time_point tp{ std::chrono::seconds{secondsSinceEpoch} };
					g_available_books.back().regestration = tp;
				}
				previous = tmp;
			}
			getAvailableBooks.close();
		}
		else {
			std::cout << "\nThere're no books! You need to add a book first";
		}
		
	}

	void UpdateAllBooksFile() {
		allBooksFile.open("data/all_books.txt");
		if (allBooksFile.is_open()) {
			for (int i = 0; i < g_all_books.size(); i++) {
				allBooksFile << "\nId\n" << g_all_books.back().id << "\nAuthor Id\n" <<
					g_all_books.back().authorId << "\nName\n" << g_all_books.back().name <<
					"\nYear\n" << g_all_books.back().bookYear << "\nLocation\nRack\n" <<
					g_all_books.back().location.rack << "\nShelf\n" <<
					g_all_books.back().location.shelf << "\nSection\n" <<
					g_all_books.back().location.section << "\nRegistration\n" <<
					std::chrono::duration_cast<std::chrono::seconds>(g_all_books.back().regestration.time_since_epoch()).count();
			}
			allBooksFile.close();
		}
		else {
			std::cout << "\nThere're no books! You need to add a book first";
		}
	}

	void UpdateAvailableBooksFile() {
		availableBooksFile.open("data/available_books.txt");
		if (availableBooksFile.is_open()) {
			for (int i = 0; i < g_available_books.size(); i++) {
				availableBooksFile << "\nId\n" << g_available_books.back().id << "\nAuthor Id\n" <<
					g_available_books.back().authorId << "\nName\n" << g_available_books.back().name <<
					"\nYear\n" << g_available_books.back().bookYear << "\nLocation\nRack\n" <<
					g_available_books.back().location.rack << "\nShelf\n" <<
					g_available_books.back().location.shelf << "\nSection\n" <<
					g_available_books.back().location.section << "\nRegistration\n" <<
					std::chrono::duration_cast<std::chrono::seconds>(g_available_books.back().regestration.time_since_epoch()).count();
			}
			availableBooksFile.close();
		}
	}

	void DeleteBookFromAll() {
		int id;
		bool isDeleted{ false };
		std::cout << "\nDeleting the book from collection of all books\nEnter the book Id\n";
		std::cin >> id;
		for (int i = 0; i < g_all_books.size(); i++) {
			if (id == g_all_books[i].id) {
				g_all_books.erase(g_all_books.begin() + i);
				UpdateAllBooksFile();
				std::cout << "The book with Id " << id << " has been deleted";
				isDeleted = true;
				break;
			}
		}
		if (!isDeleted) {
			std::cout << "The book with Id has not been found";
		}
	}

	void DeleteBookFromAvailable() {
		int id;
		bool isDeleted{ false };
		std::cout << "\nDeleting the book from collection of available books\nEnter the book Id\n";
		std::cin >> id;
		for (int i = 0; i < g_available_books.size(); i++) {
			if (id == g_available_books[i].id) {
				g_available_books.erase(g_available_books.begin() + i);
				UpdateAvailableBooksFile();
				std::cout << "The book with Id " << id << " has been deleted";
				isDeleted = true;
				break;
			}
		}
		if (!isDeleted) {
			std::cout << "The book with Id " << id << " has not been found";
		}
	}

	void ChangeBookName() {
		std::cout << "\nChanging the book's name\nEnter the book's Id\n";
		int id;
		std::cin >> id;
		std::string name;
		bool isFound{ false };
		for (int i = 0; i < g_all_books.size(); i++) {
			if (id == g_all_books[i].id) {
				std::cout << "Enter the correct name\n";
				std::cin >> name;
				g_all_books[i].name = name;
				UpdateAllBooksFile();
				isFound = true;
				break;
			}
		}
		if (!isFound) {
			std::cout << "\nThe book wasn't found";
		}
		for (int i = 0; i < g_available_books.size(); i++) {
			if (id == g_available_books[i].id) {
				g_available_books[i].name = name;
				UpdateAvailableBooksFile();
				break;
			}
		}
	}

	void ChangeBookAuthor() {
		std::cout << "\nChanging the book's author\nEnter the book's Id\n";
		int id;
		std::cin >> id;
		bool isFound{ false };
		int authorId;
		for (int i = 0; i < g_all_books.size(); i++) {
			if (id == g_all_books[i].id) {
				std::cout << "Enter the correct author Id\n";
				std::cin >> authorId;
				g_all_books[i].authorId = authorId;
				UpdateAllBooksFile();
				isFound = true;
				break;
			}
		}
		if (!isFound) {
			std::cout << "\nThe book wasn't found";
		}
		for (int i = 0; i < g_available_books.size(); i++) {
			if (id == g_available_books[i].id) {
				g_available_books[i].authorId = authorId;
				UpdateAvailableBooksFile();
				break;
			}
		}
	}
	
	void ChangeBookYear() {
		std::cout << "\nChanging the book's year of publishing\nEnter the book's Id\n";
		int id;
		std::cin >> id;
		bool isFound{ false };
		int year;
		for (int i = 0; i < g_all_books.size(); i++) {
			if (id == g_all_books[i].id) {
				std::cout << "Enter the correct year\n";
				std::cin >> year;
				g_all_books[i].bookYear = year;
				UpdateAllBooksFile();
				isFound = true;
				break;
			}
		}
		if (!isFound) {
			std::cout << "\nThe book wasn't found";
		}
		for (int i = 0; i < g_available_books.size(); i++) {
			if (id == g_available_books[i].id) {
				g_available_books[i].bookYear = year;
				UpdateAvailableBooksFile();
				break;
			}
		}
	}

	void ChangeBookLocation() {
		std::cout << "\nChanging the book's location info\nEnter the book's Id\n";
		int id;
		std::cin >> id;
		bool isFound{ false };
		int rack, shelf, section;
		for (int i = 0; i < g_all_books.size(); i++) {
			if (id == g_all_books[i].id) {
				std::cout << "Enter the correct rack number\n";
				std::cin >> rack;
				g_all_books[i].location.rack = rack;
				std::cout << "Enter the correct shelf number\n";
				std::cin >> shelf;
				g_all_books[i].location.shelf = shelf;
				std::cout << "Enter the correct section number\n";
				std::cin >> section;
				g_all_books[i].location.section = section;
				UpdateAllBooksFile();
				isFound = true;
				break;
			}
		}
		if (!isFound) {
			std::cout << "\nThe book wasn't found";
		}
		for (int i = 0; i < g_available_books.size(); i++) {
			if (id == g_available_books[i].id) {
				g_available_books[i].location.rack = rack;
				g_available_books[i].location.shelf = shelf;
				g_available_books[i].location.section = section;
				UpdateAvailableBooksFile();
				break;
			}
		}
	}

	void AddBook()
	{
		Book tmp;
		std::cout << "\nEnter the book's name\n";
		std::string tmpName;
		std::cin >> tmpName;
		std::cout << "\nEnter the author's id\n";
		int tmpAuthor;
		std::cin >> tmpAuthor;
		std::cout << "\nEnter the year of publishing\n";
		Year tmpYear;
		std::cin >> tmpYear;
		std::cout << "Enter the book's location\nRack\n";
		int tmpRack;
		std::cin >> tmpRack;
		std::cout << "\Shelf\n";
		int tmpShelf;
		std::cin >> tmpShelf;
		std::cout << "\nSection\n";
		int tmpSection;
		std::cin >> tmpSection;
		tmp.authorId = tmpAuthor;
		tmp.bookYear = tmpYear;
		tmp.name = tmpName;
		tmp.location.rack = tmpRack;
		tmp.location.shelf = tmpShelf;
		tmp.location.section = tmpSection;
		tmp.regestration = std::chrono::system_clock::now();
		if (g_all_books.empty()) {
			tmp.id = 0;
		}
		else {
			tmp.id = g_all_books.back().id + 1;
		}
		g_all_books.push_back(tmp);
		allBooksFile.open("data/all_books.txt", std::ofstream::app);
		allBooksFile << "\nId\n" << g_all_books.back().id << "\nAuthor Id\n" <<
			g_all_books.back().authorId << "\nName\n" << g_all_books.back().name <<
			"\nYear\n" << g_all_books.back().bookYear << "\nLocation\nRack\n" <<
			g_all_books.back().location.rack << "\nShelf\n" <<
			g_all_books.back().location.shelf << "\nSection\n" <<
			g_all_books.back().location.section << "\nRegistration\n" <<
			std::chrono::duration_cast<std::chrono::seconds>(g_all_books.back().regestration.time_since_epoch()).count();
		allBooksFile.close();
		std::cout << "\nIs this book available in the library?\nEnter 1 - if yes, 0 - if not\n";
		int answer;
		std::cin >> answer;
		if (answer == 1) {
			g_available_books.push_back(tmp);
			availableBooksFile.open("data/available_books.txt", std::ofstream::app);
			availableBooksFile << "\nId\n" << g_available_books.back().id << "\nAuthor Id\n" <<
				g_available_books.back().authorId << "\nName\n" << g_available_books.back().name <<
				"\nYear\n" << g_available_books.back().bookYear << "\nLocation\nRack\n" <<
				g_available_books.back().location.rack << "\nShelf\n" <<
				g_available_books.back().location.shelf << "\nSection\n" <<
				g_available_books.back().location.section << "\nRegistration\n" <<
				std::chrono::duration_cast<std::chrono::seconds>(g_available_books.back().regestration.time_since_epoch()).count();
			availableBooksFile.close();
		}
	}
}
