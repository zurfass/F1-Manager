#include "TyreSupplier.h"

// Constructor (manufacturer) is a team.
// This object defines the team, its status and reputation.
struct Constructor : public Company
{
	// Assets
	Car *car[max_cars];
	Tyre *tyre[MAX_TYRES];
	long money;

	// Contracts
	EngineSupplier *engineSupplier;
	TyreSupplier *tyreSupplier;

	// Attributes (out of 10)

	// Championship
	unsigned short engineID,points,rank;

	// Member functions
	void init(string,short[2],EngineSupplier*,TyreSupplier*);
	void update_rank(short);

	// Constructors
	Constructor () {};
	Constructor (string a, short att[2], EngineSupplier *engSupplier, TyreSupplier *tyrSupplier)
	{
		init(a,att,engSupplier,tyrSupplier);
	};
	Constructor (string a, short att0,short att1, EngineSupplier *engSupplier, TyreSupplier *tyrSupplier)
	{
		short att[] = {att0,att1};
		init(a,att,engSupplier,tyrSupplier);
	};
};

