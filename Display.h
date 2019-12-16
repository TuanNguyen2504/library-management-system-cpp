#pragma once
#ifndef _DISPLAY_
#define _DISPLAY_

#include "Library.h"
#include <Windows.h>
#include <conio.h>

#define TITLE_X 5
#define TITLE_Y 2
#define PIVOT_X 20
#define OPTION_COLOR 113
#define STEP_Y 2
#define TITLE_COLOR 3
#define CURSOR_COLOR 13
#define MAX_OPTION 6
#define SHOW_OPTION 3
#define SHOW_COLOR 6
#define UPDATE_COLOR 14

void TextColor(int color);
void gotoxy(int x, int y);
void ShowConsoleCursor(bool flag);

class Display {
public:
	void DisplayCursor(int pre_move, int move);
	void SayGoodBye();

	void ShowOptionMenu();
	void ControlShowOption();

	void UpdateOptionMenu();
	void ControlUpdateOption();

	void SearchOptionMenu();
	void ControlSearchOption();

	void ControlBorrowBookOption();
	void ControlReturnBookOption();

	void ControlOverdueListOption();

	void MainMenu();
	void DisplayMain();
};

#endif
