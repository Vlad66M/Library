#include "stdafx.h"
#include "bookRecord.h"

namespace Model{

	static std::vector<BookRecord> g_book_record;
	std::ofstream bookRecordFile;
	std::ifstream getBookRecord;

	void AddBookRecord() {
		BookRecord tmp;
		bookRecordFile.open("data/book_record.txt", std::ofstream::app);
		std::cout << "\nAdding a new book record\nEnter the book id\n";
		int id;
		std::cin >> id;
		std::cout << "\nEnter the number of the book in the library\n";
		int count;
		std::cin >> count;
		tmp.idBook = id;
		tmp.count = count;
		g_book_record.push_back(tmp);
		bookRecordFile << "\nBook Id\n" << tmp.idBook << "\nCount\n" << tmp.count;
		bookRecordFile.close();
	}

	void GetBookRecords() {
		getBookRecord.open("data/book_record.txt");
		if (getBookRecord.is_open()) {
			std::string tmp;
			std::string previous{ "" };
			BookRecord empty;
			while (!getBookRecord.eof()) {
				std::getline(getBookRecord, tmp);
				if (tmp == "Book Id") {
					g_book_record.push_back(empty);
				}
				if (previous == "Book Id") {
					g_book_record.back().idBook = std::stoi(tmp);
				}
				if (previous == "Count") {
					g_book_record.back().count = std::stoi(tmp);
				}
				previous = tmp;
			}
			getBookRecord.close();
		}
		else {
			std::cout << "\nThere're no book records! You need to add a book record first";
		}
	}

	void UpdateBookRecord() {
		bookRecordFile.open("data/book_record.txt");
		if (bookRecordFile.is_open()) {
			for (int i = 0; i < g_book_record.size(); i++) {
				bookRecordFile << "\nBook Id\n" << g_book_record[i].idBook << "\nCount\n" << g_book_record[i].count;
			}
			bookRecordFile.close();
		}
		else {
			std::cout << "\nThere're no book records! You need to add a book record first";
		}
	}

	void DeleteBookRecord() {
		int idBook;
		bool isDeleted{ false };
		std::cout << "\nDeleting the book record\nEnter the book Id\n";
		std::cin >> idBook;
		for (int i = 0; i < g_book_record.size(); i++) {
			if (idBook == g_book_record[i].idBook) {
				g_book_record.erase(g_book_record.begin() + i);
				UpdateBookRecord();
				std::cout << "The book record has been deleted";
				isDeleted = true;
				break;
			}
		}
		if (!isDeleted) {
			std::cout << "The book record has not been found";
		}
	}

	void ChangeRecordBook() {
		std::cout << "\nChanging the book record's book id\nEnter the book's Id\n";
		int idBook;
		std::cin >> idBook;
		bool isFound{ false };
		for (int i = 0; i < g_book_record.size(); i++) {
			if (idBook == g_book_record[i].idBook) {
				std::cout << "Enter the correct book Id\n";
				int correctId;
				std::cin >> correctId;
				g_book_record[i].idBook = correctId;
				UpdateBookRecord();
				isFound = true;
				break;
			}
		}
		if (!isFound) {
			std::cout << "\nThe book record wasn't found";
		}
	}

	void ChangeRecordCount() {
		std::cout << "\nChanging the book record's number of books\nEnter the book's Id\n";
		int idBook;
		std::cin >> idBook;
		bool isFound{ false };
		for (int i = 0; i < g_book_record.size(); i++) {
			if (idBook == g_book_record[i].idBook) {
				std::cout << "Enter the correct number of books\n";
				int booksCount;
				std::cin >> booksCount;
				g_book_record[i].count = booksCount;
				UpdateBookRecord();
				isFound = true;
				break;
			}
		}
		if (!isFound) {
			std::cout << "\nThe book record wasn't found";
		}
	}
}
