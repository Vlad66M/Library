#pragma once
//#include "../stdafx.h"
#ifndef BOOKRECORD_H
#define BOOKRECORD_H

namespace Model {
	struct BookRecord {
		int idBook;
		int count;
	};

	void AddBookRecord();
	void GetBookRecords();
	void UpdateBookRecord();
	void DeleteBookRecord();
	void ChangeRecordBook();
	void ChangeRecordCount();
}

#endif 