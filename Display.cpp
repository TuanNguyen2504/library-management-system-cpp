#include "Display.h"

void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void TextColor(int color)
{
	HANDLE Color;

	Color = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(Color, color);
}

void Display::SayGoodBye() {
	system("cls");
	cout << "\n\n!========= GOOD BYE ========!" << endl;
	system("pause");
	exit(0);
}

void Display::DisplayCursor(int pre_move, int move) {
	gotoxy(PIVOT_X - 3, 2 * TITLE_Y + pre_move * STEP_Y);
	TextColor(7);
	cout << "  ";

	gotoxy(PIVOT_X - 3, 2 * TITLE_Y + move * STEP_Y);
	TextColor(CURSOR_COLOR);
	cout << ">>";
}

// ======== SHOW OPTION ========= //
void Display::ShowOptionMenu() {
	gotoxy(TITLE_X - 2, TITLE_Y);
	TextColor(TITLE_COLOR);
	cout << "======== He Thong Quan Ly Thu Vien - Hien Thi ========";

	gotoxy(PIVOT_X + 1, TITLE_Y + STEP_Y);
	TextColor(OPTION_COLOR);
	cout << "    Sach    ";

	gotoxy(PIVOT_X + 1, TITLE_Y + 2 * STEP_Y);
	cout << "   Doc Gia  ";

	gotoxy(PIVOT_X + 1, TITLE_Y + 3 * STEP_Y);
	cout << " Phieu Muon ";

	gotoxy(PIVOT_X - 13, TITLE_Y + 4 * STEP_Y);
	TextColor(4);
	cout << "<= Nhan ESC de thoat - BackSpace de quay lai =>";
}
void Display::ControlShowOption() {
	int move = 0;
	int pre_move = 0;
	int option = 0;
	ShowConsoleCursor(false);
	system("cls");
	ShowOptionMenu();
	DisplayCursor(pre_move, move);
	while (1) {
		if (_kbhit()) {
			char key = _getch();
			if (key == -32)
				key = _getch();
			switch (key)
			{
			case 'w': case 'W': case 72: {
				if (move > 0) {
					pre_move = move;
					--move;
				}
				break;
			}
			case 's': case 'S': case 80: {
				if (move < SHOW_OPTION - 1) {
					pre_move = move;
					++move;
				}
				break;
			}
			case 13: {
				TextColor(SHOW_COLOR);
				option = move;
				system("cls");
				TextColor(9);
				if (option == 0)
					cout << "\n======= DANH SACH SACH TRONG THU VIEN =======";
				else if (option == 1)
					cout << "\n======= DANH SACH DOC GIA TRONG THU VIEN =======";
				else
					cout << "\n======= DANH SACH PHIEU MUON TRONG THU VIEN =======";
				Library lib;
				lib.Show(option);
				TextColor(12);
				cout << "\n\n<== Nhan phim bat ky de tiep tuc ==>" << endl;
				_getch();
				ControlShowOption();
				return;
			}
			case 8: 
				return;
			case 27: 
				SayGoodBye();
			}
		}
		DisplayCursor(pre_move, move);
	}
}

// ======== UPDATE OPTION ========= //
int ReduceUpdateCode(const char* functionName) {
	system("cls");
	ShowConsoleCursor(true);
	TextColor(UPDATE_COLOR);
	cout << "========== " <<functionName<< " ==========" << endl;
	TextColor(10);
	cout << "0 - Sach, 1 - Doc Gia, 2 - Phieu Muon/Tra >> ";
	TextColor(7);
	int type;
	cin >> type;
	if (type != 0 && type != 1)
		cin.ignore();
	if (cin.fail())
		throw "Du lieu nhap khong phai so";
	return type;
}
void Display::UpdateOptionMenu() {
	gotoxy(TITLE_X - 2, TITLE_Y);
	TextColor(TITLE_COLOR);
	cout << "======== He Thong Quan Ly Thu Vien - Cap Nhat ========";

	gotoxy(PIVOT_X + 1, TITLE_Y + STEP_Y);
	TextColor(OPTION_COLOR);
	cout << "   Them   ";

	gotoxy(PIVOT_X + 1, TITLE_Y + 2 * STEP_Y);
	cout << "   Xoa    ";

	gotoxy(PIVOT_X + 1, TITLE_Y + 3 * STEP_Y);
	cout << " Sua chua ";

	gotoxy(PIVOT_X - 13, TITLE_Y + 4 * STEP_Y);
	TextColor(4);
	cout << "<= Nhan ESC de thoat - BackSpace de quay lai =>";

}
void Display::ControlUpdateOption() {
	int move = 0;
	int pre_move = 0;
	int option = 0;
	ShowConsoleCursor(false);
	system("cls");
	UpdateOptionMenu();
	DisplayCursor(pre_move, move);
	while (1) {
		if (_kbhit()) {
			char key = _getch();
			if (key == -32)
				key = _getch();
			switch (key)
			{
			case 'w': case 'W': case 72: {
				if (move > 0) {
					pre_move = move;
					--move;
				}
				break;
			}
			case 's': case 'S': case 80: {
				if (move < SHOW_OPTION - 1) {
					pre_move = move;
					++move;
				}
				break;
			}
			case 13: {
				option = move;
				switch (option)
				{
				case 0: {
					int type = ReduceUpdateCode("THEM");
					Library lib;
					lib.Add(type);
					break;
				}
				case 1: {
					int type = ReduceUpdateCode("XOA");
					Library lib;
					lib.Delete(type);
					break;
				}
				default: {
					int type = ReduceUpdateCode("SUA CHUA");
					Library lib;
					lib.Edit(type);
					break;
				}
					break;
				}

				TextColor(12);
				cout << "\n<== Nhan phim bat ky de tiep tuc ==>" << endl;
				_getch();
				ControlUpdateOption();
				return;
			}
			case 8:
				return;
			case 27:
				SayGoodBye();
			}
		}
		DisplayCursor(pre_move, move);
	}
}

// ======== SEARCH OPTION ========= //
void Display::SearchOptionMenu() {
	gotoxy(TITLE_X - 2, TITLE_Y);
	TextColor(TITLE_COLOR);
	cout << "======== He Thong Quan Ly Thu Vien - Tim Kiem ========";

	gotoxy(PIVOT_X + 1, TITLE_Y + STEP_Y);
	TextColor(OPTION_COLOR);
	cout << "      Sach      ";

	gotoxy(PIVOT_X + 1, TITLE_Y + 2 * STEP_Y);
	cout << "     Doc Gia    ";

	gotoxy(PIVOT_X + 1, TITLE_Y + 3 * STEP_Y);
	cout << " Phieu Muon/Tra ";

	gotoxy(PIVOT_X - 13, TITLE_Y + 4 * STEP_Y);
	TextColor(4);
	cout << "<= Nhan ESC de thoat - BackSpace de quay lai =>";
}
void Display::ControlSearchOption() {
	int move = 0;
	int pre_move = 0;
	int option = 0;
	ShowConsoleCursor(false);
	system("cls");
	SearchOptionMenu();
	DisplayCursor(pre_move, move);
	while (1) {
		if (_kbhit()) {
			char key = _getch();
			if (key == -32)
				key = _getch();
			switch (key)
			{
			case 'w': case 'W': case 72: {
				if (move > 0) {
					pre_move = move;
					--move;
				}
				break;
			}
			case 's': case 'S': case 80: {
				if (move < SHOW_OPTION - 1) {
					pre_move = move;
					++move;
				}
				break;
			}
			case 13: {
				option = move;
				switch (option)
				{
				case 0: {
					system("cls");
					ShowConsoleCursor(true);
					TextColor(UPDATE_COLOR);
					cout << "========== TIM KIEM SACH ==========" << endl;
					TextColor(10);
					cout << "Tim kiem bang (0 - Ten sach, 1 - ma sach, 2 - ISBN) >> ";
					TextColor(7);
					int type;
					cin >> type;
					if (cin.fail())
						throw "Du lieu nhap khong phai so";
					TextColor(11);
					Library lib;
					int found = lib.Search(option, type);
					if (found != NOT_FOUND) {
						TextColor(13);
						cout << "\n========== TIM THAY ==========";
						lib.GetLibSystem(found)->Output();
					}
					else {
						TextColor(13);
						cout << "\n========== KHONG TIM THAY ==========" << endl;
					}
					break;
				}
				case 1: {
					system("cls");
					ShowConsoleCursor(true);
					TextColor(UPDATE_COLOR);
					cout << "========== TIM KIEM DOC GIA ==========" << endl;
					TextColor(10);
					cout << "Tim kiem bang (0 - Ten, 1 - ID) >> ";
					TextColor(7);
					int type;
					cin >> type;
					if (cin.fail()) 
						throw "Du lieu nhap khong phai so";
					TextColor(11);
					Library lib;
					int found = lib.Search(option, type);
					if (found != NOT_FOUND) {
						TextColor(13);
						cout << "\n========== TIM THAY ==========";
						lib.GetLibSystem(found)->Output();
					}
					else {
						TextColor(13);
						cout << "\n========== KHONG TIM THAY ==========" << endl;
					}
					break;
				}
				default: {
					system("cls");
					ShowConsoleCursor(true);
					TextColor(UPDATE_COLOR);
					cout << "========== TIM KIEM PHIEU MUON/TRA ==========" << endl;
					TextColor(11);
					Library lib;
					int found = lib.Search(option, 0);
					if (found != NOT_FOUND) {
						TextColor(13);
						cout << "\n========== TIM THAY ==========";
						lib.GetLibSystem(found)->Output();
					}
					else {
						TextColor(13);
						cout << "\n========== KHONG TIM THAY ==========" << endl;
					}
					break;
				}
				}

				TextColor(12);
				cout << "\n<== Nhan phim bat ky de tiep tuc ==>" << endl;
				_getch();
				ControlSearchOption();
				return;
			}
			case 8:
				return;
			case 27:
				SayGoodBye();
			}
		}
		DisplayCursor(pre_move, move);
	}
}

// ======== BORROW BOOKS OPTION ========= //
void Display::ControlBorrowBookOption() {
	system("cls");
	gotoxy(TITLE_X - 2, TITLE_Y);
	TextColor(TITLE_COLOR);
	ShowConsoleCursor(true);
	cout << "======== He Thong Quan Ly Thu Vien - Muon Sach ========";
	TextColor(7);
	Library lib;
	lib.BorrowBook();
	TextColor(12);
	cout << "\n<== Nhan phim bat ky de tiep tuc ==>" << endl;
	_getch();
}

// ======== RETURN BOOKS OPTION ========= //
void Display::ControlReturnBookOption() {
	system("cls");
	gotoxy(TITLE_X - 2, TITLE_Y);
	TextColor(TITLE_COLOR);
	ShowConsoleCursor(true);
	cout << "======== He Thong Quan Ly Thu Vien - Tra Sach ========";
	TextColor(7);
	Library lib;
	lib.ReturnBook();
	TextColor(12);
	cout << "\n<== Nhan phim bat ky de tiep tuc ==>" << endl;
	_getch();
}

// ======== OVERDUE LIST OPTION ========= //
void Display::ControlOverdueListOption() {
	system("cls");
	gotoxy(TITLE_X - 2, TITLE_Y);
	TextColor(TITLE_COLOR);
	ShowConsoleCursor(true);
	cout << "======== He Thong Quan Ly Thu Vien - Danh sach qua han muon sach ========";
	TextColor(7);
	Library lib;
	lib.OverdueList();
	TextColor(12);
	cout << "\n<== Nhan phim bat ky de tiep tuc ==>" << endl;
	_getch();
}

// ======== MAIN DISPLAY ======== //
void Display::MainMenu() {
	gotoxy(TITLE_X, TITLE_Y);
	TextColor(TITLE_COLOR);
	cout << "======== He Thong Quan Ly Thu Vien ========";

	gotoxy(PIVOT_X, TITLE_Y + STEP_Y);
	TextColor(OPTION_COLOR);
	cout << "  Hien Thi  ";

	gotoxy(PIVOT_X, TITLE_Y + 2 * STEP_Y);
	cout << "  Cap Nhat  ";

	gotoxy(PIVOT_X , TITLE_Y + 3 * STEP_Y);
	cout << "  Tim Kiem  ";

	gotoxy(PIVOT_X , TITLE_Y + 4 * STEP_Y);
	cout << "  Muon Sach ";

	gotoxy(PIVOT_X , TITLE_Y + 5 * STEP_Y);
	cout << "  Tra  Sach ";

	gotoxy(PIVOT_X , TITLE_Y + 6 * STEP_Y);
	cout << " DS Qua Han ";

	gotoxy(PIVOT_X - 7 , TITLE_Y + 7 * STEP_Y);
	TextColor(4);
	cout << "<== Nhan ESC de thoat ==>";
}
void Display::DisplayMain() {
	system("cls");
	int move = 0;
	int pre_move = 0;
	int option = 0;
	ShowConsoleCursor(false);
	MainMenu();
	DisplayCursor(pre_move, move);
	while (1) {
		if (_kbhit()) {
			char key = _getch();
			if (key == -32)
				key = _getch();
			switch (key)
			{
			case 'w': case 'W': case 72: {
				if (move > 0) {
					pre_move = move;
					--move;
				}
				break;
			}
			case 's': case 'S': case 80: {
				if (move < MAX_OPTION - 1) {
					pre_move = move;
					++move;
				}
				break;
			}
			case 13: {
				option = move;
				switch (option)
				{
				case 0: {
					ControlShowOption();
					DisplayMain();
					return;
				}
				case 1: {
					ControlUpdateOption();
					DisplayMain();
					return;
				}
				case 2: {
					ControlSearchOption();
					DisplayMain();
					return;
				}
				case 3: {
					ControlBorrowBookOption();
					DisplayMain();
					return;
				}
				case 4: {
					ControlReturnBookOption();
					DisplayMain();
					return;
				}
				default: {
					ControlOverdueListOption();
					DisplayMain();
					return;
				}
				}
				break;
			}
			case 27: 
				SayGoodBye();
			}
		}
		DisplayCursor(pre_move, move);
	}
}
