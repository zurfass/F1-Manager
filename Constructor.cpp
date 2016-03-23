#include "Constructor.h"

// Initialize members during object creation
void Constructor::init(string a, short att[2], EngineSupplier *engSupplier, TyreSupplier *tyrSupplier)
{
	name = a;
	engineSupplier = engSupplier;
	tyreSupplier = tyrSupplier;
	points = 0;

	// New sets of tyres for first driver
	tyre[0] = new Tyre(*tyreSupplier->tyre[SOFT]);
	tyre[1] = new Tyre(*tyreSupplier->tyre[HARD]);
	tyre[2] = new Tyre(*tyreSupplier->tyre[INTERS]);
	tyre[3] = new Tyre(*tyreSupplier->tyre[WETS]);

	// New sets of tyres for 2nd driver
	tyre[4] = new Tyre(*tyreSupplier->tyre[SOFT]);
	tyre[5] = new Tyre(*tyreSupplier->tyre[HARD]);
	tyre[6] = new Tyre(*tyreSupplier->tyre[INTERS]);
	tyre[7] = new Tyre(*tyreSupplier->tyre[WETS]);

	// 2 new cars for race drivers
	car[0] = new Car(att, engSupplier->engine, tyre[0]);
	car[1] = new Car(att, engSupplier->engine, tyre[1]);
}

// Assign championship ranking
void Constructor::update_rank(short ID)
{
	rank = ID+1;
}

