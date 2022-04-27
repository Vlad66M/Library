#include "stdafx.h"
#include "Ticket.h"

namespace Model {
	static std::vector<Ticket> g_tickets;
	std::ofstream ticketsFile;
	std::ifstream getTickets;

	void AddTicket() {
		Ticket tmp;
		std::cout << "\nAdding a new ticket\nEnter reader Id\n";
		int idReader;
		std::cin >> idReader;
		tmp.idReader = idReader;
		std::cout << "\nEnter book Id\n";
		int idBook;
		std::cin >> idBook;
		tmp.idBook = idBook;
		tmp.issueDate = std::chrono::system_clock::now();
		std::cout << "\nEnter number of days for the reader to return the book\n";
		int days;
		std::cin >> days;
		tmp.returnDate = std::chrono::system_clock::now() + std::chrono::days(days);
		g_tickets.push_back(tmp);
		ticketsFile.open("data/tickets.txt", std::ofstream::app);
		ticketsFile << "\nBook Id\n" << tmp.idBook << "\nReader Id\n" << tmp.idReader <<
			"\nIssue Date\n" << std::chrono::duration_cast<std::chrono::seconds>(tmp.issueDate.time_since_epoch()).count() <<
			"\nReturn Date\n" << std::chrono::duration_cast<std::chrono::seconds>(tmp.returnDate.time_since_epoch()).count();
		ticketsFile.close();
	}

	void GetTickets() {
		getTickets.open("data/tickets.txt");
		if (getTickets.is_open()) {
			std::string tmp;
			std::string previous{ "" };
			Ticket empty;
			while (!getTickets.eof()) {
				std::getline(getTickets, tmp);
				if (tmp == "Book Id") {
					g_tickets.push_back(empty);
				}
				if (previous == "Book Id") {
					g_tickets.back().idBook = std::stoi(tmp);
				}
				if (previous == "Reader Id") {
					g_tickets.back().idReader = std::stoi(tmp);
				}
				if (previous == "Issue Date") {
					auto secondsSinceEpoch = std::stoi(tmp);
					std::chrono::system_clock::time_point tp{ std::chrono::seconds{secondsSinceEpoch} };
					g_tickets.back().issueDate = tp;
				}
				if (previous == "Return Date") {
					auto secondsSinceEpoch = std::stoi(tmp);
					std::chrono::system_clock::time_point tp{ std::chrono::seconds{secondsSinceEpoch} };
					g_tickets.back().returnDate = tp;
				}
				previous = tmp;
			}
			getTickets.close();
		}
		else {
			std::cout << "\nThere are no tickets! You need to add a ticket first";
		}
	}

	void UpdateTickets() {
		ticketsFile.open("data/tickets.txt");
		if (ticketsFile.is_open()) {
			for (int i = 0; i < g_tickets.size(); i++) {
				ticketsFile << "\nBook Id\n" << g_tickets[i].idBook << "\nReader Id\n" << g_tickets[i].idReader <<
					"\nIssue Date\n" << std::chrono::duration_cast<std::chrono::seconds>(g_tickets[i].issueDate.time_since_epoch()).count() <<
					"\nReturn Date\n" << std::chrono::duration_cast<std::chrono::seconds>(g_tickets[i].returnDate.time_since_epoch()).count();
			}
			ticketsFile.close();
		}
		else {
			std::cout << "\nThere are no tickets! You need to add a ticket first";
		}
	}

	void OverdueCheck() {
		auto tp = std::chrono::system_clock::now();
		bool isFound{ false };
		std::cout << "\nChecking overdue status of the ticket\nEnter the reader Id\n";
		int readerId;
		std::cin >> readerId;
		std::cout << "\nEnter the book Id\n";
		int bookId;
		std::cin >> bookId;
		for (int i = 0; i < g_tickets.size(); i++) {
			if ((readerId == g_tickets[i].idReader) && (bookId == g_tickets[i].idBook)) {
				if (tp > g_tickets[i].returnDate) {
					std::cout << "\nThe ticket is overdue";
				}
				else {
					std::cout << "\nThe ticket is not overdue yet";
				}
				isFound = true;
				break;
			}
		}
		if (!isFound) {
			std::cout << "\nThe ticket wasn't found";
		}
	}

	void ChangeTicketBook() {
		std::cout << "\nCnanging book info in the ticket";
		std::cout << "\nEnter the book's old Id\n";
		int oldBookId;
		std::cin >> oldBookId;
		std::cout << "\nEnter reader's Id\n";
		int readerId;
		std::cin >> readerId;
		bool isFound{ false };
		for (int i = 0; i < g_tickets.size(); i++) {
			if ((readerId == g_tickets[i].idReader) && (oldBookId == g_tickets[i].idBook)) {
				std::cout << "\nEnter the correct book Id\n";
				int tmp;
				std::cin >> tmp;
				g_tickets[i].idBook = tmp;
				isFound = true;
				UpdateTickets();
				break;
			}
		}
		if (!isFound) {
			std::cout << "\nThe ticket wasn't found";
		}
	}

	void ChangeTicketReader() {
		std::cout << "\nCnanging reader info in the ticket";
		std::cout << "\nEnter the reader's old Id\n";
		int oldReaderId;
		std::cin >> oldReaderId;
		std::cout << "\nEnter book's Id\n";
		int bookId;
		std::cin >> bookId;
		bool isFound{ false };
		for (int i = 0; i < g_tickets.size(); i++) {
			if ((bookId == g_tickets[i].idBook) && (oldReaderId == g_tickets[i].idReader)) {
				std::cout << "\nEnter the correct reader Id\n";
				int tmp;
				std::cin >> tmp;
				g_tickets[i].idReader = tmp;
				isFound = true;
				UpdateTickets();
				break;
			}
		}
		if (!isFound) {
			std::cout << "\nThe ticket wasn't found";
		}
	}

	void DeleteTicket() {
		std::cout << "\nDeleting the ticket\nEnter the book Id\n";
		int bookId;
		std::cin >> bookId;
		std::cout << "\nEnter the reader Id\n";
		int readrId;
		std::cin >> readrId;
		bool isDeleted{ false };
		for (int i = 0; i < g_tickets.size(); i++) {
			if ((bookId == g_tickets[i].idBook) && (readrId == g_tickets[i].idReader)) {
				g_tickets.erase(g_tickets.begin() + i);
				UpdateTickets();
				std::cout << "The ticket has been deleted";
				isDeleted = true;
				break;
			}
		}
		if (!isDeleted) {
			std::cout << "\nThe ticket wasn't found";
		}
	}
}