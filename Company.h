#include "Components/Car.cpp"
#include "Contract.h"

struct Company {
	string name;
	Country *base;

	// Attributes (out of 10)
	short resources;

	// Member functions
	void display_spaces(short);
	void display_name(short);
};

void Company::display_spaces(short maxSpaces)
{
	short a = maxSpaces-name.length();
	printSpaces(a);
}

void Company::display_name(short maxSpaces)
{
	if (name.length() > maxSpaces) cout << name.substr(int_zero,maxSpaces);
	else {
		cout << name;
		display_spaces(maxSpaces);
	}
}

