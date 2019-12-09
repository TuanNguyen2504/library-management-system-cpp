#pragma once
#ifndef _LIBRARYSYSTEM_
#define _LIBRARYSYSTEM_

#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <cmath>
#include <cfloat>
#include <fstream>
#include <iomanip>

#define BOOKS_DATA_PATH "book.txt"
#define READERS_DATA_PATH "readers.txt"
#define BORROWEDSLIP_DATA_PATH "borrowed-slip.txt"
#define NOT_FOUND -1
#define EAN_13 "978"
#define _EAN_13 "979"
#define ISBN_VN "604"
#define  OVERDUE_MONEY_VN_BOOK  10000
#define  OVERDUE_MONEY_FOREIGN_BOOK 20000
using namespace std;

//Ham ho tro
bool IsEmpty(const string& data);
string ToLower(const string& str);

class LibrarySystem
{
protected:
public:
	LibrarySystem() {};
	virtual void Input() = 0;
	virtual void Output() = 0;
	virtual void InputFile(ifstream& input) = 0;
	virtual void OutputFile(ofstream& path) = 0;
	~LibrarySystem() {};	
};

#endif
