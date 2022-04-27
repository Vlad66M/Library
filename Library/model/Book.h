#pragma once
//#include "../stdafx.h"
#include "Human.h"
#ifndef BOOK_H
#define BOOK_H

namespace Model {
	using Year = int;

	struct BookLocation {
		int rack;
		int shelf;
		int section;
	};

	struct Book
	{
		int id;
		std::string name;
		int authorId;
		BookLocation location;
		std::chrono::system_clock::time_point regestration;
		Year bookYear;
	};

	void AddBook();
	void GetAllBooks();
	void GetAvailableBooks();
	void UpdateAllBooksFile();
	void UpdateAvailableBooksFile();
	void DeleteBookFromAll();
	void DeleteBookFromAvailable();
	void ChangeBookName();
	void ChangeBookAuthor();
	void ChangeBookYear();
	void ChangeBookLocation();
	void AddBook();

}
#endif