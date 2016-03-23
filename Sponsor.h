#include "Company.h"

struct Sponsor: public Company
{
	unsigned short numberOfContracts;
	Contract *contract[MAX_TEAMS];

	// Member functions
	void new_contract();

	// Constructors
	Sponsor(string a, Country *b, unsigned short c) {
		name = a;
		base = b;
		resources = c;
	}
};

