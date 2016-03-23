#include "Company.h"
//#include "Components/Engine.h"

struct EngineSupplier: public Company {
	Contract *contract[MAX_TEAMS];
	Engine *engine;

	// Member functions
	void init(string,short[4]);
	void display_attributes(short ID);

	// Constructors
	EngineSupplier(string a, short att[4])
	{
		init(a,att);
	}
	EngineSupplier(string a, short b, short c, short d, short e)
	{
		short att[] = {b,c,d,e};
		init(a,att);
	}
};

// Initialize member attributes during object creation
void EngineSupplier::init(string a, short att[4])
{
	name = a;
	engine = new Engine(att);
}

void EngineSupplier::display_attributes(short ID)
{
	display_rank(ID);
	display_name(MAX_CHARS);
	cout << " " << engine->power << "," << engine->reliability << endl;
}

