#include "Date.h"
Date::Date() {
	this->d = 1;
	this->m = 1;
	this->y = 1900;
}

Date::Date(int day, int month, int year) {
	this->d = day;
	this->m = month;
	this->y = year;
	this->validityCheck_Fix();
}

Date::Date(const Date& date) {
	this->d = date.d;
	this->m = date.m;
	this->y = date.y;
}

bool Date::isLeapYear() {
	if (this->y % 4 == 0) {
		if (this->y % 100 == 0) {
			if (this->y % 400 != 0)
				return false;
			else
				return true;
		}
		return true;
	}
	return false;
}

bool Date::validityCheck_Fix() {
	bool check = true;

	if (this->y < 1900) {
		this->y = 1900;
		check = false;
	}

	if (this->m < 1 || this->m  >12) {
		this->m = 1;
		check = false;
	}
		
	if (this->d < 1 || this->d > 31) {
		this->d = 1;
		check = false;
	}
	else {
		switch (this->m)
		{
		case 2:
		{
			if (this->isLeapYear()) {
				if (this->d > 29) {
					this->d = 29;
					check = false;
				}
			}
			else {
				if (this->d > 28) {
					this->d = 28;
					check = false;
				}
			}	
			break;
		}
		case 4: case 6: case 9: case 11:
		{
			if (this->d > 30) {
				this->d = 30;
				check = false;
			}	
			break;
		}
		default:
			break;
		}
	}

	return check;
}

istream& operator >> (istream& is, Date& date) {
	char remove = NULL;
	is >> date.d;
	if (is.fail())
		throw "du lieu vua nhap khong phai 1 so";
	is >> remove;
	is >> date.m;
	if (is.fail())
		throw "du lieu vua nhap khong phai 1 so";
	is >> remove;
	is >> date.y;
	if (is.fail())
		throw "du lieu vua nhap khong phai 1 so";
	return is;
}

ostream& operator << (ostream& os, const Date& date) {
	os << date.d << "/" << date.m << "/" << date.y;
	return os;
}

Date& Date::operator ++ () {
	this->d++;
	switch (this->m)
	{
	case 2:
	{
		if (this->isLeapYear()) {
			if (this->d > 29) {
				this->d = 1;
				++this->m;
			}
		}
		else
		{
			if (this->d > 28) {
				this->d = 1;
				++this->m;
			}
		}
		break;
	}
	case 4: case 6: case 9: case 11:
	{
		if (this->d > 30){
			this->d = 1;
			++this->m;
		}
		break;
	}
	default:
		if (this->d > 31) {
			this->d = 1;
			++this->m;
		}
		break;
	}
	if (this->m > 12) {
		this->m = 1;
		++this->y;
	}
	return *this;
}

Date& Date::operator -- () {
	this->d--;
	if (this->d == 0) {
		--this->m;
		switch (this->m)
		{
		case 2:
		{
			if (this->isLeapYear())
				this->d = 29;
			else
				this->d = 28;
			break;
		}
		case 4: case 6: case 9: case 11:
		{
			this->d = 30;
			break;
		}
		default:
			this->d = 31;
			break;
		}
	}
	
	if (this->m == 0) {
		this->m = 12;
		--this->y;
	}
	return *this;
}

Date& Date::operator += (int n) {
	for (int i = 0; i < n; ++i)
		++(*this);
	return *this;
}

Date& Date::operator -= (int n) {
	for (int i = 0; i < n; ++i)
		--(*this);

	return *this;
}

bool Date::operator > (const Date& date) {
	if (this->y > date.y)
		return true;
	else if (this->y == date.y) {
		if (this->m > date.m)
			return true;
		else if (this->m == date.m) {
			if (this->d > date.d)
				return true;
		}
	}

	return false;
}

bool Date::operator >= (const Date& date) {
	if (this->y > date.y)
		return true;
	else if (this->y == date.y) {
		if (this->m > date.m)
			return true;
		else if (this->m == date.m) {
			if (this->d >= date.d)
				return true;
		}
	}

	return false;
}

bool Date::operator < (const Date& date) {
	if ((*this) >= date)
		return false;

	return true;
}

bool Date::operator <= (const Date& date) {
	if ((*this) > date)
		return false;

	return true;
}

bool operator== (const Date& d1, const Date& d2) {
	return d1.d == d2.d && d1.m == d2.m && d1.y == d2.y;
}

int operator- (Date d1, Date d2) {
	if (d1 == d2)
		return 0;
	if (d1.operator>(d2)) {
		int res = 1;
		while (1) {
			--d1;
			if (d1 == d2)
				return res;
			++res;
		}
	}
	else {
		int res = 1;
		while (1) {
			--d2;
			if (d1 == d2)
				return res;
			++res;
		}
	}
}
