#pragma once
//#include "../stdafx.h"
#ifndef HUMAN_H
#define HUMAN_H

namespace Model {
	struct Human
	{
		std::string name;
		std::string  patrinomic;
		std::string surname;
	};

	Human AddHuman();
}

#endif // 