#include "stdafx.h"
#include "Author.h"

namespace Model {
    static std::vector<Author> g_authors;
    std::ofstream authorsFile;
    std::ifstream getAuthors;

    void AddAuthor()
    {
        std::cout << "\nAdding a new author\n";
        Human tmpHuman = AddHuman();
        Author tmp;
        tmp.who = tmpHuman;
        if (g_authors.empty()) {
            tmp.id = 0;
        }
        else {
            tmp.id = g_authors.back().id + 1;
        }
        g_authors.push_back(tmp);
        authorsFile.open("data/authors.txt", std::ofstream::app);
        authorsFile << "\nId\n" << tmp.id << "\nName\n" << tmp.who.name << "\nPatrimomic\n" <<
            tmp.who.patrinomic << "\nSurname\n" << tmp.who.surname;
        authorsFile.close();
    }

	void GetAuthors() {
		getAuthors.open("data/authors.txt");
		if (getAuthors.is_open()) {
			std::string tmp;
			std::string previous{ "" };
			Author empty;
			while (!getAuthors.eof()) {
				std::getline(getAuthors, tmp);
				if (tmp == "Id") {
					g_authors.push_back(empty);
				}
				if (previous == "Id") {
					g_authors.back().id = std::stoi(tmp);
				}
				if (previous == "Name") {
					g_authors.back().who.name = tmp;
				}
				if (previous == "Patrimomic") {
					g_authors.back().who.patrinomic = tmp;
				}
				if (previous == "Surname") {
					g_authors.back().who.surname = tmp;
				}
				previous = tmp;
			}
			getAuthors.close();
		}
		else {
			std::cout << "\nThere are no authors! You need to add an author first";
		}
	}

	void UpdateAuthorsFile() {
		authorsFile.open("data/authors.txt");
		if (authorsFile.is_open()) {
			for (int i = 0; i < g_authors.size(); i++) {
				authorsFile << "\nId\n" << g_authors[i].id << "\nName\n" << g_authors[i].who.name << "\nPatrimomic\n" <<
					g_authors[i].who.patrinomic << "\nSurname\n" << g_authors[i].who.surname;
			}
			authorsFile.close();
		}
		else {
			std::cout << "\nThere are no authors! You need to add an author first";
		}
	}

	void DeleteAuthor() {
		std::cout << "\nDeleting the author\nEnter Id of the author you want to delete\n";
		int id;
		std::cin >> id;
		bool isDeleted{ false };
		for (int i = 0; i < g_authors.size(); i++) {
			if (g_authors[i].id == id) {
				g_authors.erase(g_authors.begin() + i);
				UpdateAuthorsFile();
				std::cout << "The author with Id " << id << " has been deleted";
				isDeleted = true;
				break;
			}
		}
		if (!isDeleted) {
			std::cout << "The author with Id " << id << " was not found";
		}
	}

	void ChangeAuthorName() {
		std::cout << "\nChanging the name of the author\nEnter Id of the author\n";
		int id;
		std::cin >> id;
		bool isFound{ false };
		for (int i = 0; i < g_authors.size(); i++) {
			if (g_authors[i].id == id) {
				std::cout << "\nEnter the correct name\n";
				std::cout << "Enter authors's name\n";
				std::string tmpName;
				std::cin >> tmpName;
				std::cout << "Enter authors's patrinomic\n";
				std::string tmpPatrinomic;
				std::cin >> tmpPatrinomic;
				std::cout << "Enter authors's surname\n";
				std::string tmpSurname;
				std::cin >> tmpSurname;
				g_authors[i].who.name = tmpName;
				g_authors[i].who.patrinomic = tmpPatrinomic;
				g_authors[i].who.surname = tmpSurname;
				UpdateAuthorsFile();
				isFound = true;
				break;
			}
		}
		if (!isFound) {
			std::cout << "The author has not been found";
		}
	}
}
