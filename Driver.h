#include "Employee.h"
#include "Constructor.cpp"

// Defines a driver's ability and status
struct Driver: public Employee
{
	// Driver's team and car
	short teamID, teamCar;
	Constructor *team;

	// Attributes (out of 10)
	short speed, reliability, wetWeather;

	// Race status
	unsigned int distance;
	int timeGap;
	unsigned short lapDista, retReason, stop;
	float lapSpeed;
	unsigned int lap[90], qLap, fastestLap;
	bool ranOff, spun, lapped, pitting;

	// Season status
	unsigned short grid[MAX_RACES], finish[MAX_RACES];
	unsigned short points, wins, poles;

	// Member functions
	void init(string,short,short,short,short);
	void set_values(string,short);

	// Print to console
	void display_driver(short rank);
	void display_results(short a);
	void display_grids(short a);
	void display_qual(short i);
	void display_driver_position_and_status(short,short,int);

	// Current speed in m/s (for non-leaders)
	void current_speed(unsigned short,unsigned short,short,TrackCondition);

	// Current speed in m/s (qualifying and race leader)
	void current_speed(float,unsigned short,unsigned short,short,TrackCondition);

	// Current reliability (true=mistake, false=fine)
	bool collision_update(short,TrackCondition);
	bool spin_update(short,TrackCondition);

	// Distance lost due to driver error in m
	void error_update(short,TrackCondition);
	void get_ready_for_GP();
	void get_ready_for_race(short,short,unsigned int,Tyre*[4],TrackCondition);
	int position(int lap_length)
		{return(distance%lap_length);}
	int laps(int lap_length)
		{return(distance/lap_length);}
	void fastest_lap(unsigned short);
	double total_time(short laps);
	void save_driver(string,short,short,short);

	// Constructors
	Driver () {};
	Driver (string a,short b,short c,short d,short e,short f)
    	{
		init(a,b,c,d,e);
		teamID = f;
	};
	Driver (string a,short b,short c,short d,short e,Constructor *f)
	{
		init(a,b,c,d,e);
		team = f;
	}
};

