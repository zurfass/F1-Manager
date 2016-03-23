#include "EngineSupplier.h"

struct TyreSupplier: public Company {
	Contract *contract[MAX_TEAMS];
	Tyre *tyre[4];

	// Constructors
	TyreSupplier(string a, short att[3])
	{
		name = a;
		tyre[SOFT]	= new Tyre(att,soft);
		tyre[HARD]	= new Tyre(att,hard);
		tyre[INTERS]	= new Tyre(att,inter);
		tyre[WETS]	= new Tyre(att,wets);
	}
};

