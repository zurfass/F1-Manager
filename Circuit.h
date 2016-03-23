#include "Country.h"

// Describes circuit's features and race status (weather, track conditions)
struct Circuit
{
	string name;
	Country *country;

	// Characteristics
	short totalLaps,countryID;
	unsigned short lapLength;

	// Attributes (out of 5)
	short speed, overtaking;

	// Status
	short grip;	// (out of 5)
	Weather weather;
	TrackCondition cond; // {dry,damp,wet,flood}

	// Member functions
	void init(string,short,unsigned short,short,short,short);
	unsigned int total_distance();
	void display_spaces(short);
	void display_name(short);
	void display_info(short round);
	void display_status();
	short track_weather(short climate);
	void track_conditions(short activity);
	bool overtake(int);

	// Constructors
	Circuit () {};
	Circuit (string a, unsigned short c, short att[4])
	{
		init(a,att[0],c,att[1],att[2],att[3]);
	}
	Circuit (string a,short b,unsigned short c,short d,short e,short f)
	{
		init(a,b,c,d,e,f);
	}
};

