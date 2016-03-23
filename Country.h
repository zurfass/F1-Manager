#include "Components/defines.cpp"

struct Country
{
	string name;
	string nationality;
	unsigned short size;
	short a_length,b_length;

	// Member functions
	void display_spaces(short);
	void display_name(short);

	// Constructors
	Country () {};
	Country (string a,string b,short c)
	{
		name = a;
		nationality = b;
		size = c;
	}
};

// Prints extra spaces after the name to maintain alignment
void Country::display_spaces(short maxSpaces)
{
	short a = maxSpaces-name.length();
	printSpaces(a);
}

// Prints name in specified number of spaces
void Country::display_name(short maxSpaces)
{
	if (name.length() > maxSpaces) cout << name.substr(int_zero,maxSpaces);
	else {
		cout << name;
		display_spaces(maxSpaces);
	}
}

