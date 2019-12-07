#include "LibrarySystem.h"
bool IsEmpty(const string& data) {
	if (data.empty()) {
		cerr << "\nKhong duoc bo trong";
		return true;
	}
	for (int i = 0; i < data.length(); ++i)
		if (data[i] != ' ')
			return false;
	return false;
}

string ToLower(const string& str) {
	string temp = "";
	for (int i = 0; i < str.length(); ++i)
		temp.push_back(tolower(str[i]));
	return temp;
}
