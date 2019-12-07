#include "BorrowedSlip.h"

BorrowedSlip::BorrowedSlip() {
	_book_list.resize(0);
	_returned.resize(0);
}
BorrowedSlip::BorrowedSlip(const BorrowedSlip& bs) {
	_readers = bs._readers;
	_book_list = bs._book_list;
	_borrow_date = bs._borrow_date;
	_book_return_date = bs._book_return_date;
	_returned = bs._returned;
}
BorrowedSlip::~BorrowedSlip() {

}

Readers BorrowedSlip::GetReaders() const {
	return _readers;
}
Date BorrowedSlip::GetBorrowDate() const {
	return _borrow_date;
}
vector<Date> BorrowedSlip::GetBookReturnDate() const {
	return _book_return_date;
}
vector<int> BorrowedSlip::GetReturned() const {
	return _returned;
}
vector<Book> BorrowedSlip::GetBookList() const {
	return _book_list;
}
int BorrowedSlip::GetReturned(int pos) const {
	if(pos >=0 && pos < _returned.size())
		return _returned[pos];
	else {
		throw "Loi truy cap";
		return -1;
	}
}

void BorrowedSlip::SetReaders(const Readers& r) {
	_readers = r;
}
void BorrowedSlip::SetBorrowDate(Date date) {
	if(date.validityCheck_Fix())
		_borrow_date = date;
}
void BorrowedSlip::SetBookReturnDate(int pos, Date date) {
	if(date.validityCheck_Fix() && date >= _borrow_date && pos >=0 && pos < _book_return_date.size())
		_book_return_date[pos] = date;
}
void BorrowedSlip::SetReturned(int pos, int returned) {
	if (pos >= 0 && pos < _returned.size())
		_returned[pos] = returned;
}

void BorrowedSlip::Input() {
	cout << "\n===== Nhap thong tin nguoi muon =====";
	_readers.Input();
	cout << "\n===== Nhap thong tin cac loai sach muon =====";
	int n;
	while (1) {
		cout << "\nNhap so luong sach muon: ";
		cin >> n;
		if (cin.fail())
			throw "NaN - du lieu nhap phai la 1 so";
		if (n > 0)
			break;
		cerr << "\nSo sach muon > 0";
	}
	cin.ignore();
	_book_list.resize(n);
	for (int i = 0; i < n; ++i) {
		cout << "\n==== Nhap thong tin sach thu " << i + 1 << " ====";
		_book_list[i].Input();
		cin.ignore();
	}	
	while (1) {
		cout << "\nNgay muon sach (dd/mm/yyyy): ";
		cin >> _borrow_date;
		if (_borrow_date.validityCheck_Fix())
			break;
		cout << "\nNgay nhap khong hop le !";
	}
	for (int i = 0; i < n; ++i)
		_returned.push_back(0);
}
void BorrowedSlip::Output() {
	cout << "\n===== Thong tin nguoi muon =====";
	_readers.Output();
	cout << "\n\n===== Thong tin cac sach da muon =====";
	for (int i = 0; i < _book_list.size(); ++i) {
		cout << "\n========== Quyen " << i + 1 << " ==========";
		_book_list[i].Output();
	}
	cout << "\n\n========== Thong tin Muon/Tra ==========" << endl;
	cout << "Ngay muon sach: " << _borrow_date;
	cout << "\nNgay tra sach: " << endl;
	for (int i = 0; i < _returned.size(); ++i) {
		cout << "-->Quyen " << i + 1 << ": ";
		if (!_returned[i])
			cout << "... (chua tra)" << endl;
		else
			cout << _book_return_date[i] << endl;
	}	
}

void BorrowedSlip::InputFile(ifstream& input) {
	_readers.InputFile(input);
	if (input.eof())
		return;
	int n;
	input >> n;
	if (input.fail())
		throw "Khong the doc file";
	_book_list.resize(n);
	for (int i = 0; i < n; ++i) {
		input.ignore();
		_book_list[i].InputFile(input);
	}
	input >> _borrow_date;

	_returned.resize(n);
	_book_return_date.resize(n);
	for (int i = 0; i < n; ++i) {
		input >> _returned[i];
		if (_returned[i] != 0)
			input >> _book_return_date[i];
	}
}
void BorrowedSlip::OutputFile(ofstream& out) {
	out << _readers;
	out << _book_list.size() << endl;
	for (int i = 0; i < _book_list.size(); ++i)
		out << _book_list[i];
	out << _borrow_date << endl;
	for (int i = 0; i < _returned.size(); ++i) {
		if (_returned[i] != 0) {
			out << _returned[i] << " ";
			if (i != _returned.size() - 1)
				out << _book_return_date[i] << " ";
			else
				out << _book_return_date[i];
		}
		else {
			if (i != _returned.size() - 1)
				out << _returned[i] << " ";
			else
				out << _returned[i];
		}
	}
	out << endl;
}
