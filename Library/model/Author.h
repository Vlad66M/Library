#pragma once
//#include "../stdafx.h"
#include "Human.h"
#ifndef AUTHOR_H
#define AUTHOR_H

namespace Model {
	struct Author {
		int id;
		Human who;
	};

	void AddAuthor();
	void GetAuthors();
	void UpdateAuthorsFile();
	void DeleteAuthor();
	void ChangeAuthorName();
}
#endif 