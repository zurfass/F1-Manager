#include "GearBox.h"

struct Suspension: public Component
{
	// Member functions

	// Constructors
	Suspension(short att[2])
	{
		setAttributes(att);
	}
};

