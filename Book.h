#pragma once
#ifndef _BOOK_
#define _BOOK_
#include "LibrarySystem.h"

class Book : public LibrarySystem
{
private:
	string _title;
	string _author;
	string _publisher;
	string _code;
	string _ISBN;
	double _price;
public:

	Book();
	Book(const Book& book);
	Book(const string& name, const string& author, const string& publisher, const string& code, const string& ISBN, double price);
	~Book();

	string GetTitle() const;
	string GetAuthor() const;
	string GetPublisher() const;
	string GetCode() const;
	string GetISBN() const;
	double GetPrice() const;

	void SetTitle(const string& title);
	void SetAuthor(const string& author);
	void SetPublisher(const string& pub);
	void SetCode(const string& code);
	void SetISBN(const string& ISBN);
	void SetPrice(double price);


	static bool CheckISBN(const string& ISBN);
	static bool CheckBookCode(const string& code);
	static bool IsVNBook(const string& ISBN);

	void Input();
	void Output();
	string FormatISBN() const;

	void InputFile(ifstream& input);
	void OutputFile(ofstream& path);

	Book& operator= (const Book& book);
	friend ostream& operator<< (ostream& os, const Book& book);
};
#endif

