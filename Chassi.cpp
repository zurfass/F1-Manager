#include "Chassi.h"

// Set the main attributes
void Chassi::setAttributes(short att[])
{
	speed = att[0];
	reliability = att[1];
}

// Returns whether all the parts are fully assembled
bool Chassi::assembled()
{
	return (gearbox.installed && drivetrain.installed && bodywork.installed && suspension.installed);
}

// Updates the condition of every assembled component in the chassi
void Chassi::update_condition(unsigned short distance, TrackCondition cond)
{
	// Update component wear
	drivetrain.update_condition(distance,cond);
	gearbox.update_condition(distance,cond);
	suspension.update_condition(distance,cond);
}

