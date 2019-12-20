#include "Library.h"
Library::Library() {

}

Library::Library(const Library& lib) {
	_ls = lib._ls;
}

Library::~Library() {

}

LibrarySystem* Library::GetLibSystem(int pos) const {
	if (pos < 0 || pos >= _ls.size())
		throw "Vi tri truy cap khong hop le";
	return _ls[pos];
}

bool Library::IsExist(int option, LibrarySystem* ls) const {
	switch (option) {
	case 0: {
		for (int i = 0; i < _ls.size(); ++i)
			if (((Book*)ls)->GetISBN() == ((Book*)_ls[i])->GetISBN())
				return true;
	}
	case 1: {
		for (int i = 0; i < _ls.size(); ++i)
			if (((Readers*)ls)->GetID() == ((Readers*)_ls[i])->GetID())
				return true;
	}
	default: {
		break;
	}
	}
	return false;
}

void Library::LoadDataFromFile(int option) {
	ifstream input;
	switch (option) {
	case 0: {
		input.open(BOOKS_DATA_PATH);
		if (input.fail())
			throw "loi doc file";
		while (1) {
			LibrarySystem* ls = NULL;
			ls = new Book;
			if (!ls)
				throw "Loi cap phat";
			ls->InputFile(input);
			if (input.eof())
				break;
			_ls.push_back(ls);
			input.ignore();
		}
		break;
	}
	case 1: {
		input.open(READERS_DATA_PATH);
		if (input.fail())
			throw "loi doc file";
		while (1) {
			LibrarySystem* ls = NULL;
			ls = new Readers;
			if (!ls)
				throw "Loi cap phat";
			ls->InputFile(input);
			if (input.eof())
				break;
			_ls.push_back(ls);
			input.ignore();
		}
		break;
	}
	default: {
		input.open(BORROWEDSLIP_DATA_PATH);
		if (input.fail())
			throw "loi doc file";
		while (1) {
			LibrarySystem* ls = NULL;
			ls = new BorrowedSlip;
			if (!ls)
				throw "Loi cap phat";
			ls->InputFile(input);
			if (input.eof())
				break;
			_ls.push_back(ls);
			input.ignore();
		}
		break;
	}
	}
	input.close();
}

void Library::OutputDataToFile(int option) {
	ofstream out;
	switch (option) {
	case 0: {
		out.open(BOOKS_DATA_PATH, ios::trunc);
		break;
	}
	case 1: {
		out.open(READERS_DATA_PATH, ios::trunc);
		break;
	}
	default: {
		out.open(BORROWEDSLIP_DATA_PATH, ios::trunc);
		break;
	}
	}
	if (out.fail())
		throw "Loi doc file";
	for (int i = 0; i < _ls.size(); ++i)
		_ls[i]->OutputFile(out);
	out.close();
}

void Library::Show(int option) {
	LoadDataFromFile(option);
	for (int i = 0; i < _ls.size(); ++i) {
		TextColor(SHOW_COLOR);
		cout << "\n========== STT " << i + 1 << " ==========";
		TextColor(7);
		_ls[i]->Output();
	}
}

void Library::Add(int option) {
	LoadDataFromFile(option);
	ofstream output;
	switch (option)
	{
	case 0: {
		output.open(BOOKS_DATA_PATH, ios::app);
		if (output.fail())
			throw "Loi doc file";
		LibrarySystem * book = new Book;
		if (book == NULL)
			throw "Khong the cap phat bo nho";
		cin.ignore();
		book->Input();
		if (!IsExist(option, book))
			book->OutputFile(output);
		else
			cout << "\nSach da ton tai trong thu vien !";
		break;
	}
	case 1: {
		output.open(READERS_DATA_PATH, ios::app);
		if (output.fail())
			throw "Loi doc file";
		Readers* readers = new Readers;
		if (readers == NULL)
			throw "Khong the cap phat bo nho";
		cin.ignore();
		readers->Input();
		if(!IsExist(option, readers))
			readers->OutputFile(output);
		else
			cout << "\nDoc gia da ton tai trong thu vien !";
		break;
	}
	default: {
		output.open(BORROWEDSLIP_DATA_PATH, ios::app);
		if (output.fail())
			throw "Loi doc file";
		BorrowedSlip* bs = new BorrowedSlip;
		if (bs == NULL)
			throw "Khong the cap phat bo nho";
		fflush(stdin);
		bs->Input();
		for (int i = 0; i < _ls.size(); ++i)
			if (((BorrowedSlip*)bs)->GetReaders().GetID() == ((BorrowedSlip*)_ls[i])->GetReaders().GetID()) {
				if (((BorrowedSlip*)bs)->GetReaders() == ((BorrowedSlip*)_ls[i])->GetReaders())
					bs->OutputFile(output);
				else
					cerr << "\n=== ERROR: Trung ID nhung khac thong tin ===" << endl;
				output.close();
				return;
			}
		bs->OutputFile(output);
		break;
	}
	}
	output.close();
}

void Library::Delete(int option) {
	int found;
	if (option == 0)
		found = Search(option, 3);
	else if (option == 1)
		found = Search(option, 1);
	else
		found = Search(option, 0);
	if (found == NOT_FOUND) {
		cout << "\n========= KHONG TIM THAY TRONG DANH SACH THU VIEN ==========" << endl;
		return;
	}
	cout << "\n========= XOA THANH CONG ==========" << endl;
	_ls.erase(_ls.begin() + found);
	OutputDataToFile(option);
}

int Library::Search(int option, int type) {
	//option 0-book, 1-readers, default - borrowed slip
	LoadDataFromFile(option);
	switch (option) {
	case 0: {
		switch (type) {
		case 0: {
			//search by title
			cout << "\nNhap ten sach: ";
			string title;
			cin.ignore();
			getline(cin, title);
			for (int i = 0; i < _ls.size(); ++i)
				if (ToLower(((Book*)_ls[i])->GetTitle()) == ToLower(title))
					return i;
			return NOT_FOUND;
		}
		case 1: {
			//search by book code
			string code;
			while (1) {
				cout << "\nNhap ma sach: ";
				cin.ignore();
				getline(cin, code);
				if (Book::CheckBookCode(code))
					break;
			}
			for (int i = 0; i < _ls.size(); ++i)
				if (ToLower(((Book*)_ls[i])->GetCode()) == ToLower(code))
					return i;
			return NOT_FOUND;
		}
		default: {
			//search by ISBN
			string ISBN;
			cin.ignore();
			while (1) {
				cout << "\nNhap ma ISBN-13: ";
				getline(cin, ISBN);
				if (Book::CheckISBN(ISBN))
					break;
			}
			for (int i = 0; i < _ls.size(); ++i)
				if (ToLower(((Book*)_ls[i])->GetISBN()) == ToLower(ISBN))
					return i;
			return NOT_FOUND;
		}
		}
	}
	case 1: {
		switch (type) {
		case 0: {
			//search by name
			cout << "\nNhap ten doc gia: ";
			string name;
			cin.ignore();
			getline(cin, name);
			for (int i = 0; i < _ls.size(); ++i)
				if (ToLower(((Readers*)_ls[i])->GetName()) == ToLower(name))
					return i;
			return NOT_FOUND;
		}
		default: {
			//search by ID
			cout << "\nNhap ID doc gia: ";
			string ID;
			cin.ignore();
			getline(cin, ID);
			for (int i = 0; i < _ls.size(); ++i)
				if (ToLower(((Readers*)_ls[i])->GetID()) == ToLower(ID))
					return i;
			return NOT_FOUND;
		}
		}
	}
	default: {
		cout << "\nNhap ten (ID) nguoi muon: ";
		string name_ID;
		getline(cin, name_ID);
		for (int i = 0; i < _ls.size(); ++i) {
			string r_name = ((BorrowedSlip*)_ls[i])->GetReaders().GetName();
			string r_ID = ((BorrowedSlip*)_ls[i])->GetReaders().GetID();
			if (ToLower(r_name) == ToLower(name_ID) || r_ID == name_ID)
				return i;
		}
		return NOT_FOUND;
	}
	}
}

void Library::Edit(int option) {
	int found = Search(option, 0);
	if (found == NOT_FOUND) {
		cout << "\n========= KHONG TIM THAY TRONG DANH SACH THU VIEN ==========" << endl;
		return;
	}
	int type;
	switch (option) {
	case 0: {
		TextColor(3);
		cout << "\n0-Sua Tat Ca, 1-Ten sach, 2-Tac Gia, 3-NXB, 4-Ma Sach, 5-ISBN, 6-Gia Sach >> ";
		cin >> type;
		if (cin.fail())
			throw "Du lieu nhap khong la so";
		cin.ignore();
		TextColor(11);
		switch (type) {
		case 0: {
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			_ls[found]->Input();
			break;
		}
		case 1: {
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			cout << "Nhap ten sach: ";
			string title;
			getline(cin, title);
			((Book*)_ls[found])->SetTitle(title);
			break;
		}
		case 2: {
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			cout << "Nhap ten tac gia: ";
			string author;
			getline(cin, author);
			((Book*)_ls[found])->SetAuthor(author);
			break;
		}
		case 3: {
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			cout << "Nhap NXB: ";
			string pub;
			getline(cin, pub);
			((Book*)_ls[found])->SetPublisher(pub);
			break;
		}
		case 4: {
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			string code;
			while (1) {
				cout << "Nhap ma sach: ";
				getline(cin, code);
				if (Book::CheckBookCode(code))
					break;
			}
			((Book*)_ls[found])->SetCode(code);
			break;
		}
		case 5: {
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			string ISBN;
			while (1) {
				cout << "Nhap ISBN: ";
				getline(cin, ISBN);
				if (Book::CheckISBN(ISBN))
					break;
			}
			((Book*)_ls[found])->SetAuthor(ISBN);
			break;
		}
		default: {
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			double price = 0;
			while (1) {
				cout << "Nhap gia sach: ";
				cin >> price;
				if (price > 0)
					break;
			}
			((Book*)_ls[found])->SetPrice(price);
			break;
		}
		}
		break;
	}
	case 1: {
		TextColor(3);
		cout << "\n0-Sua Tat Ca, 1-Ten Doc Gia, 2-ID, 3-Dia chi, 4-tuoi >> ";
		cin >> type;
		if (cin.fail())
			throw "Du lieu nhap khong la so";
		cin.ignore();
		TextColor(11);
		switch (type) {
		case 0: {
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			_ls[found]->Input();
			break;
		}
		case 1: {
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			cout << "Nhap ten doc gia: ";
			string name;
			getline(cin, name);
			((Readers*)_ls[found])->SetName(name);
			break;
		}
		case 2: {
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			string ID;
			while (1) {
				cout << "Nhap ID doc gia: ";
				getline(cin, ID);
				if (Readers::CheckID(ID))
					break;
			}
			((Readers*)_ls[found])->SetID(ID);
			break;
		}
		case 3: {
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			cout << "Nhap Dia Chi Doc Gia: ";
			string address;
			getline(cin, address);
			((Readers*)_ls[found])->SetAddress(address);
			break;
		}
		default: {
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			int age = 0;
			while (1) {
				cout << "Nhap tuoi doc gia: ";
				cin >> age;
				if (age > 0)
					break;
			}
			((Readers*)_ls[found])->SetAge(age);
			break;
		}
		}
		break;
	}
	default: {
		TextColor(3);
		cout << "\n0-Sua Tat Ca, 1-Nguoi Muon, 2-Ngay Muon >> ";
		cin >> type;
		if (cin.fail())
			throw "Du lieu nhap khong la so";
		cin.ignore();
		TextColor(11);
		switch (type) {
		case 0: {
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			_ls[found]->Input();
			break;
		}
		case 1: {
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			Readers r;
			r.Input();
			((BorrowedSlip*)_ls[found])->SetReaders(r);
			break;
		}
		default: {
			cout << "\n\t===== Nhap thong tin can chinh sua =====" << endl;
			Date date;
			while (1) {
				cout << "Nhap ngay muon: ";
				cin >> date;
				if (date.validityCheck_Fix())
					break;
				cerr << "\nNgay nhap khong hop le !" << endl;
			}
			((BorrowedSlip*)_ls[found])->SetBorrowDate(date);
			break;
		}
		}
		break;
	}	
	}
	OutputDataToFile(option);
}

void Library::BorrowBook() {
	this->Add(3);
}

void Library::ReturnBook() {
	LoadDataFromFile(3);

	//Tim nguoi can tra
	string ID;
	while (1) {
		cout << "\nNhap ID nguoi muon: ";
		getline(cin, ID);
		if (Readers::CheckID(ID))
			break;
	}
	vector<int> founds;
	for (int i = 0; i < _ls.size(); ++i)
		if (((BorrowedSlip*)_ls[i])->GetReaders().GetID() == ID)
			founds.push_back(i);
	if (founds.size() == 0) {
		cerr << "\n========== KHONG TIM THAY NGUOI MUON CO ID TREN =========" << endl;
		return;
	}

	//Lua chon tinh nang tra
	cout << "\n0 - Tra Het, 1 - Tra Tung Quyen: ";
	int option = 0;
	cin >> option;
	if (cin.fail())
		throw "NaN - Du lieu nhap khong la so";

	if (!option) {
		Date date;
		while (1) {
			cout << "\nNhap ngay tra: ";
			cin >> date;
			bool check = true;
			if (date.validityCheck_Fix() == true) {
				for (int i = 0; i < founds.size(); ++i) {
					if (((BorrowedSlip*)_ls[founds[i]])->GetBorrowDate() > date) {
						cerr << "\nNgay nhap khong hop le (Ngay tra >= ngay muon) !";
						check = false;
						break;
					}		
				}
			}
			else {
				cerr << "\nNgay nhap khong hop le !";
				check = false;
			}
			if (check)
				break;			
		}
		for (int i = 0; i < founds.size(); ++i) {
			int n = ((BorrowedSlip*)_ls[founds[i]])->GetBookList().size();
			for (int j = 0; j < n; ++j) {
				if (((BorrowedSlip*)_ls[founds[i]])->GetReturned(j) == 0) {
					((BorrowedSlip*)_ls[founds[i]])->SetReturned(j, 1);
					((BorrowedSlip*)_ls[founds[i]])->SetBookReturnDate(j, date);
				}		
			}
		}

	}
	else {
		cin.ignore();
		string bookName;
		cout << "\nNhap ten sach can tra: ";
		getline(cin, bookName);

		vector<vector<Book>> bookList;
		for (int i = 0; i < founds.size(); ++i)
			bookList.push_back(((BorrowedSlip*)_ls[founds[i]])->GetBookList());
		int pos_1 = -1;
		int pos_2 = -1;
		for (int i = 0; i < founds.size(); ++i) {
			for (int j = 0; j < bookList[i].size(); ++j) {
				if (ToLower(bookList[i][j].GetTitle()) == ToLower(bookName)) {
					pos_1 = i;
					pos_2 = j;
					break;
				}
			}
		}
		if (pos_1 == -1 && pos_2 == -1) {
			cerr << "\n========== KHONG TIM THAY SACH CAN TRA =========" << endl;
			return;
		}
		Date date;
		while (1) {
			cout << "\nNhap ngay tra: ";
			cin >> date;
			if (date.validityCheck_Fix() == true && date >= ((BorrowedSlip*)_ls[founds[pos_1]])->GetBorrowDate())
				break;
			cerr << "\nNgay nhap khong hop le (Ngay tra >= ngay muon) !";
		}
		((BorrowedSlip*)_ls[founds[pos_1]])->SetReturned(pos_2, 1);
		((BorrowedSlip*)_ls[founds[pos_1]])->SetBookReturnDate(pos_2, date);
	}
	cout << "\n========== TRA THANH CONG ==========" << endl;
	//Luu lai file
	OutputDataToFile(3);
}

void Library::OverdueList() {
	LoadDataFromFile(3);
	Date now;
	while (1) {
		cout << "\nNhap ngay can thong ke: ";
		cin >> now;
		if (now.validityCheck_Fix())
			break;
		cerr << "\nNgay nhap khog hop le !";
	}
	vector<Readers> overdueReaders;
	vector<int> money;
	
	//liet ke nhung doc gia muon sach qua han
	for (int i = 0; i < _ls.size(); ++i) {
		int money_t = 0;
		vector<int> returned = ((BorrowedSlip*)_ls[i])->GetReturned();
		vector<Date> returnDate = ((BorrowedSlip*)_ls[i])->GetBookReturnDate();
		Date borrowDate = ((BorrowedSlip*)_ls[i])->GetBorrowDate();
		vector<Book> bookList = ((BorrowedSlip*)_ls[i])->GetBookList();
		//ngay muon toi da
		borrowDate += 7;
		bool overdue = false;
	
		for (int j = 0; j < returned.size(); ++j) {
			//sach da tra
			int nOver = 0;
			if (returned[j] != 0) {
				if (borrowDate < returnDate[j]) {
					overdue = true;
					nOver = returnDate[j] - borrowDate;
					if(Book::IsVNBook(bookList[j].GetISBN()))
						money_t += OVERDUE_MONEY_VN_BOOK * nOver;
					else
						money_t += OVERDUE_MONEY_FOREIGN_BOOK * nOver;
				}
			}
			//sach chua tra
			else {
				if (borrowDate < now) {
					overdue = true;
					nOver = now - borrowDate;
					if (Book::IsVNBook(bookList[j].GetISBN()))
						money_t += (OVERDUE_MONEY_VN_BOOK * nOver);
					else
						money_t += (OVERDUE_MONEY_FOREIGN_BOOK * nOver);
				}
			}
		}
		if (overdue == true) {
			overdueReaders.push_back(((BorrowedSlip*)_ls[i])->GetReaders());
			money.push_back(money_t);
		}
		
	}
	
	if (overdueReaders.size() == 0) {
		TextColor(3);
		cout << "\n========== KHONG CO DOC GIA NAO MUON SACH QUA HAN ==========\n";
		return;
	}

	//Merge doc gia bi trung
	vector<Readers> RE_result;
	vector<int> MO_result;
	RE_result.push_back(overdueReaders[0]);
	MO_result.push_back(money[0]);

	for (int i = 1; i < overdueReaders.size(); ++i) {
		bool check = true;
		for (int j = 0; j < RE_result.size(); ++j) {
			if (overdueReaders[i].GetID() == RE_result[j].GetID()) {
				MO_result[j] += money[i];
				check = false;
				break;
			}		
		}
		if (check) {
			RE_result.push_back(overdueReaders[i]);
			MO_result.push_back(money[i]);
		}
	}

	TextColor(6);
	cout << "\n=============== DANH SACH MUON SACH QUA HAN ================" << endl;
	TextColor(3);
	cout << "====> Co " << RE_result.size() << " doc gia muon sach qua han" << endl;
	for (int i = 0; i < RE_result.size(); ++i) {
		TextColor(10);
		cout << "========= STT " << i + 1 << " =========" << endl;
		TextColor(7);
		RE_result[i].Output();
		cout << "\n==> So tien phat: " << MO_result[i] << endl;
	}
}