#include "Display.h"

//khoi tao 3 file data neu chua ton tai
void createDataFile() {
	ofstream dataFile;
	dataFile.open(BOOKS_DATA_PATH, ios::app);
	dataFile.close();
	dataFile.open(READERS_DATA_PATH, ios::app);
	dataFile.close();
	dataFile.open(BORROWEDSLIP_DATA_PATH, ios::app);
	dataFile.close();
}

int main() {
	try {
		createDataFile();
		Display display;
		display.DisplayMain();
		/*Date date;
		cin >> date;
		date += 7;
		cout << date;
		Date date2;
		cin >> date2;
		cout << date2 - date;*/
		TextColor(7);
		system("pause");
		return 0;
	}
	catch (const char* error) {
		TextColor(4);
		cerr << "\n\t!== ERROR: " << error << " ==!" << endl;
		TextColor(7);
		system("pause");
		return -1;
	}
}