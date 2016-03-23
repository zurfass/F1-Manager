#include "Tyre.h"

// Describes the chassi's quality, condition and race status
struct Chassi
{
	// Parts
	Bodywork bodywork;
	Drivetrain drivetrain;
	GearBox gearbox;
	Suspension suspension;

	// Chassi attributes (out of 10)
	short speed, reliability;

	// Member functions
	void setAttributes(short[2]);
	bool assembled();
	void new_condition();
	void display_condition();

	// Mechanical reliability update
	void update_condition(unsigned short,TrackCondition);

	// Constructors
	Chassi (short att[2]) : bodywork(att,9,9), drivetrain(att), gearbox(att), suspension(att)
	{
		setAttributes(att);
	}
};

// Assemble new chassi from new components
void Chassi::new_condition()
{
	bodywork.new_condition();
	drivetrain.new_condition();
	gearbox.new_condition();
	suspension.new_condition();
}

// For DEBUGGING
void Chassi::display_condition()
{
	drivetrain.display_condition();
	gearbox.display_condition();
	suspension.display_condition();
}

