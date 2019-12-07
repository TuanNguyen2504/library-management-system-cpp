#pragma once
#ifndef _BORROWEDSLIP_
#define _BORROWEDSLIP_

#include "LibrarySystem.h"
#include "Book.h"
#include "Readers.h"
#include "Date.h"
class BorrowedSlip :public LibrarySystem
{
private:
	Readers _readers;
	vector<Book> _book_list;
	Date _borrow_date;
	vector<Date> _book_return_date;
	vector<int> _returned;
public:
	BorrowedSlip();
	BorrowedSlip(const BorrowedSlip& bs);
	~BorrowedSlip();

	Readers GetReaders() const;
	Date GetBorrowDate() const;
	vector<Date> GetBookReturnDate() const;
	int GetReturned(int pos) const;
	vector<int> GetReturned() const;
	vector<Book> GetBookList() const;


	void SetReaders(const Readers& r);
	void SetBorrowDate(Date date);
	void SetBookReturnDate(int pos, Date date);
	void SetReturned(int pos, int returned);

	void Input();
	void Output();

	void InputFile(ifstream& input);
	void OutputFile(ofstream& path);

};
#endif
