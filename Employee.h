#include "Components/defines.h"

struct Employee {
	string name;
	unsigned short age;
	Country *nationality;
	unsigned long salary;

	// Member functions
	void display_spaces(short);
	void display_name(short);
};

// Prints extra spaces after the name to maintain alignment
void Employee::display_spaces(short maxSpaces)
{
	short a = maxSpaces-name.length();
	printSpaces(a);
}

// Prints name in specified number of spaces
void Employee::display_name(short maxSpaces)
{
	if (name.length() > maxSpaces) cout << name.substr(int_zero,maxSpaces);
	else {
		cout << name;
		display_spaces(maxSpaces);
	}
}

