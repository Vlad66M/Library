#pragma once
//#include "../stdafx.h"
#include "Human.h"
#include "Author.h"
#ifndef READER_H
#define READER_H

namespace Model {
	struct Address {
		std::string city;
		std::string street;
		int building;
		int apartment;
	};
	struct Reader
	{
		Human who;
		int documentNumber;
		Address address;
		int idReader;
	};
	void AddReader();
	void GetReaders();
	void UpdateReadersFile();
	void DeleteReader();
	void ChangeReaderName();
	void ChangeReaderDocument();
}

#endif 