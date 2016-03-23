#include "Drivetrain.h"

struct Engine: public Component
{
	// Attributes (out of 10)
	short power, fuelEfficiency;

	// Constructors
	Engine(short att[4])
	{
		short component_att[] = {att[0],att[1]};
		setAttributes(component_att);
		power = att[2];
		fuelEfficiency = att[3];
	}
};

