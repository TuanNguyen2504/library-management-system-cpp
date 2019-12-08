#pragma once
#ifndef _DATE_
#define _DATE_

#include <iostream>
#include <cmath>

using namespace std;
class Date
{
	int d; //day
	int m; //month
	int y; //year
public:
	Date();
	Date(int, int, int);
	Date(const Date&);
	bool isLeapYear();
	bool validityCheck_Fix();
	friend istream& operator >>(istream&, Date&);
	friend ostream& operator <<(ostream&, const Date&);
	Date& operator += (int n);
	Date& operator -= (int n);
	Date& operator ++ ();
	Date& operator -- ();
	bool operator > (const Date&);
	bool operator < (const Date&);
	bool operator >= (const Date&);
	bool operator <= (const Date&);
	friend int operator-(Date d1, Date d2);
	friend bool operator==(const Date& d1, const Date& d2);
};

#endif