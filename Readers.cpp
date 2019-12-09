#include "Readers.h"

Readers::Readers() {
	_name = "";
	_ID = "";
	_age = 0;
	_address = "";
}
Readers::Readers(const Readers& readers) {
	_name = readers._name;
	_ID = readers._ID;
	_age = readers._age;
	_address = readers._address;
}
Readers::Readers(string name, string ID, int age, string address) {
	_name = name;
	_ID = ID;
	_age = age;
	_address = address;
}
Readers::~Readers() {

}

string Readers::GetName() const {
	return _name;
}
string Readers::GetAddress() const {
	return _address;
}
string Readers::GetID() const {
	return _ID;
}
int Readers::GetAge() const {
	return _age;
}

void Readers::SetName(const string& name) {
	if(!IsEmpty(name))
		_name = name;
}
void Readers::SetID(const string& ID) {
	if (CheckID(ID))
		_ID = ID;
}
void Readers::SetAddress(const string& address) {
	if (!IsEmpty(address))
		_address = address;
}
void Readers::SetAge(int age) {
	if (age > 0)
		_age = age;
}

bool Readers::CheckID(const string& ID) {
	for(int i = 0; i < ID.length(); ++i)
		if (ID[i] < '0' || ID[i]>'9') {
			cerr << "\nID phai la so tu 0-9 !" << endl;
			return false;
		}
	return true;
}
void Readers::Input() {
	while (1) {
		cout << "\nNhap ho ten: ";
		getline(cin, _name);
		if (!IsEmpty(_name))
			break;
	}
	while (1) {
		cout << "\nNhap ID: ";
		getline(cin, _ID);
		if (!IsEmpty(_ID) && CheckID(_ID))
			break;
	}
	while (1) {
		cout << "\nNhap dia chi: ";
		getline(cin, _address);
		if (!IsEmpty(_address))
			break;
	}	
	while (1) {
		cout << "\nNhap tuoi: ";
		cin >> _age;
		if (cin.fail())
			throw "NaN - du lieu nhap phai la 1 so" ;
		if (_age > 0)
			break;
		cerr << "\nTuoi phai lon > 0 !";
	}
}
void Readers::Output() {
	cout << "\nHo Ten: " << _name;
	cout << "\nID: " << _ID;
	cout << "\nDia chi: " << _address;
	cout << "\nTuoi: " << _age;
}

void Readers::InputFile(ifstream& input) {
	getline(input, _name);
	getline(input, _ID);
	getline(input, _address);
	input >> _age;
}
void Readers::OutputFile(ofstream& out) {
	out << _name << endl;
	out << _ID << endl;
	out << _address << endl;
	out << _age << endl;
}

Readers& Readers::operator=(const Readers& readers) {
	_name = readers._name;
	_ID = readers._ID;
	_age = readers._age;
	_address = readers._address;
	return *this;
}

ostream& operator<< (ostream& os, const Readers& readers) {
	os << readers._name << endl;
	os << readers._ID << endl;
	os << readers._address << endl;
	os << readers._age << endl;
	return os;
}

bool operator== (const Readers& r1, const Readers& r2) {
	return ToLower(r1._name) == ToLower(r2._name) && ToLower(r1._address) == ToLower(r2._address) && r1._ID == r2._ID && r1._age == r2._age;
}
