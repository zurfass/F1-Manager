#include "Chassi.cpp"

struct Car
{
	// Components
	Chassi chassi;
	Engine *engine;
	Tyre *tyre;

	// Fuel tank status
	int tankCapacity, tankLevel;
	int refuel[7];

	// Setup and strategy
	unsigned short plannedStops, stops;
	bool unscheduled;
	TrackCondition setup;

	// Member functions
	bool assembled();
	unsigned short speed(short,TrackCondition);

	// Race functions
	void get_ready_for_GP(bool,bool);
	void get_ready_for_race(unsigned int,Tyre*[4],TrackCondition);
	void display_strategy();
	void update_condition(unsigned short,TrackCondition);
	bool part_failure(short,TrackCondition);
	short any_failure(unsigned short,TrackCondition);
	bool next_lap(unsigned short,TrackCondition);
	void display_status();
	short pit_stop(Tyre*[4],TrackCondition);

	// Constructors
	Car(short att[2], Engine *eng, Tyre *tyr) : chassi(att)
	{
		engine = eng;
		tyre = new Tyre(*tyr);

		// Set fuel tank status
		tankCapacity = 200000;
		tankLevel = 0;
		unscheduled = false;
	}
};

