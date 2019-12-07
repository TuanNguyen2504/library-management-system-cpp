#include "Display.h"

int main() {
	try {
		Display display;
		display.DisplayMain();
		TextColor(7);
		return 0;
	}
	catch (const char* error) {
		TextColor(4);
		cerr << "\n\t!== ERROR: " << error << " ==!" << endl;
		TextColor(7);
		return -1;
	}
}