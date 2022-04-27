#pragma once
#ifndef TICKET_H
#define TICKET_H

namespace Model {
	struct Ticket {
		int idReader;
		int idBook;
		std::chrono::system_clock::time_point issueDate;
		std::chrono::day duration;
		std::chrono::system_clock::time_point returnDate;
	};

	void AddTicket();
	void GetTickets();
	void OverdueCheck();
	void ChangeTicketBook();
	void ChangeTicketReader();
	void DeleteTicket();
}
#endif 