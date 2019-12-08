#pragma once
#ifndef _LIBRARY_
#define _LIBRARY_
#include "Date.h"
#include "LibrarySystem.h"
#include "Book.h"
#include "BorrowedSlip.h"
#include "Readers.h"
#include "Display.h"

class Library
{	
private:
	vector<LibrarySystem*> _ls;
public:

	Library();
	Library(const Library& lib);
	~Library();

	LibrarySystem* GetLibSystem(int pos) const;

	bool IsExist(int option, LibrarySystem* ls) const;
	void LoadDataFromFile(int option);		//0- book, 1-readers, 2-borrowed slip
	void OutputDataToFile(int option);
	void Add(int option);
	void Delete(int option);
	void Show(int option);
	int Search(int option, int type);
	void Edit(int option);
	void BorrowBook();
	void ReturnBook();
	void OverdueList();
};

#endif