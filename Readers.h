#pragma once
#ifndef _READERS_
#define _READERS_

#include "LibrarySystem.h"
class Readers :public LibrarySystem
{
private:
	string _name;
	string _ID;						//ID library card
	string _address;
	int _age;
public:
	Readers();
	Readers(const Readers& readers);
	Readers(string name, string ID, int age, string address);
	~Readers();

	string GetName() const;
	string GetID() const;
	string GetAddress() const;
	int GetAge() const;

	void SetName(const string& name);
	void SetID(const string& ID);
	void SetAddress(const string& address);
	void SetAge(int age);

	static bool CheckID(const string& ID);
	void Input();
	void Output();

	void InputFile(ifstream& input);
	void OutputFile(ofstream& path);
	
	Readers& operator=(const Readers& r);
	friend ostream& operator<< (ostream& os, const Readers& readers);
	friend bool operator== (const Readers& r1, const Readers& r2);
};

#endif
