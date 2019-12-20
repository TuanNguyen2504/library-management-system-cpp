#include "Book.h"
Book::Book() {
	_title = "";
	_author = "";
	_publisher = "";
	_ISBN = "";
	_price = 0;
}
Book::Book(const Book& book) {
	_title = book._title;
	_author = book._author;
	_publisher = book._publisher;
	_code = book._code;
	_ISBN = book._ISBN;
	_price = book._price;
}
Book::Book(const string& name, const string& author, const string& publisher, const string& code, const string& ISBN, double price) {
	_title = name;
	_author = author;
	_publisher = publisher;
	_code = code;
	_ISBN = ISBN;
	if (price < 0)
		_price = 0;
	else
		_price = price;
}
Book::~Book() {

}

string Book::GetAuthor() const {
	return _author;
}
string Book::GetCode() const {
	return _code;
}
string Book::GetISBN() const {
	return _ISBN;
}
string Book::GetPublisher() const {
	return _publisher;
}
string Book::GetTitle() const {
	return _title;
}
double Book::GetPrice() const {
	return _price;
}

void Book::SetTitle(const string& title) {
	if (!IsEmpty(title))
		_title = title;
}
void Book::SetAuthor(const string& author) {
	if (!IsEmpty(author))
		_author = author;
}
void Book::SetPublisher(const string& pub) {
	if (!IsEmpty(pub)) 
		_publisher = pub;
}
void Book::SetCode(const string& code) {
	if (CheckBookCode(code))
		_code = code;
}
void Book::SetISBN(const string& ISBN) {
	if (CheckISBN(ISBN))
		_ISBN = ISBN;
}
void Book::SetPrice(double price) {
	if (price > 0)
		_price = price;
}

bool Book::CheckISBN(const string& ISBN) {
	if (IsEmpty(ISBN))
		return false;

	if (ISBN.length() != 13) {
		cerr << "\nMa ISBN gom 13 chu so !";
		return false;
	}
	string check;
	check = check + ISBN[0] + ISBN[1] + ISBN[2];
	if (check != _EAN_13 && check != EAN_13) {
		cerr << "\nMa ISBN-13 bat dau bang 978 hoac 979 !";
		return false;
	}
	for (int i = 0; i < ISBN.length(); ++i)
		if (ISBN[i] > '9' || ISBN[i] < '0') {
			cerr << "\nMa ISBN phai la nhung chu so 0-9 !";
			return false;
		}
	return true;
}
bool Book::CheckBookCode(const string& code) {
	for (int i = 0; i < code.length(); ++i)
		if (code[i] > '9' || code[i] < '0') {
			cerr << "\nMa Sach phai la nhung chu so 0-9 !";
			return false;
		}
	return true;
}
bool Book::IsVNBook(const string& ISBN) {
	if (CheckISBN(ISBN)) 	
		if (ISBN.substr(3, 3) == ISBN_VN)
			return true;
	return false;
}

string Book::FormatISBN() const {
	string res = _ISBN;
	res.insert(3, "-");
	return res;
}
void Book::Input() {
	while (1) {
		cout << "\nNhap ten sach: ";
		getline(cin, _title);
		if (!IsEmpty(_title))
			break;
	}
	while (1) {
		cout << "\nNhap ten tac gia: ";
		getline(cin, _author);
		if (!IsEmpty(_author))
			break;
	}
	while (1) {
		cout << "\nNhap NXB: ";
		getline(cin, _publisher);
		if (!IsEmpty(_publisher))
			break;
	}
	while (1) {
		cout << "\nNhap ma sach: ";
		getline(cin, _code);
		if (!IsEmpty(_code))
			break;
		if (CheckBookCode(_code))
			break;
	}
	while (1) {
		cout << "\nNhap ISBN-13: ";
		getline(cin, _ISBN);
		if (CheckISBN(_ISBN))
			break;
	}
	while(1){
		cout << "\nNhap gia sach: ";
		cin >> _price;
		if (cin.fail()) {
			cerr << "NaN - du lieu nhap phai la 1 so !";
			exit(0);
		}	
		if (_price > 0)
			break;
		cerr << "\nGia sach phai lon hon 0 !";		
	} 
}
void Book::Output() {
	cout << "\nTen sach: " << _title;
	cout << "\nTac gia: " << _author;
	cout << "\nNXB: " << _publisher;
	cout << "\nMa sach: " << _code;
	cout << "\nISBN: " << FormatISBN();
	cout << "\nGia sach: " << setprecision(10) << _price;
}

void Book::InputFile(ifstream& input) {
	getline(input, _title);
	getline(input, _author);
	getline(input, _publisher);
	getline(input, _code);
	getline(input, _ISBN);
	input >> _price;
}
void Book::OutputFile(ofstream& out){
	out << _title << endl;
	out << _author << endl;
	out << _publisher << endl;
	out << _code << endl;
	out << _ISBN << endl;
	out << _price << endl;
}

Book& Book::operator= (const Book& book) {
	_title = book._title;
	_author = book._author;
	_publisher = book._publisher;
	_code = book._code;
	_ISBN = book._ISBN;
	_price = book._price;
	return *this;
}

ostream& operator<< (ostream& os, const Book& book) {
	os << book._title << endl;
	os << book._author << endl;
	os << book._publisher << endl;
	os << book._code << endl;
	os << book._ISBN << endl;
	os << book._price << endl;
	return os;
}
