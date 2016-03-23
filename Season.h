#include "Driver.cpp"

// Defines a season (a single year-long championship)
struct Season
{
	short year;
	short totalEngines, totalTeams, totalEntries, totalGPs;

	// Calendar of races
	short GP[MAX_RACES];

	// Drivers Championship
	Driver entry[MAX_ENTRIES];

	// Race weekend pointers to drivers
	Driver *Act[MAX_ENTRIES], *Ret[MAX_ENTRIES];

	// Constructors Championship
	Constructor *team[MAX_TEAMS];
	EngineSupplier *engineSupplier[MAX_TEAMS];
	TyreSupplier *tyreSupplier[5];

	// Member functions
	Driver create_driver();			// User inputs driver attributes
	Constructor* create_constructor();	// User inputs team attributes
	void edit_season();
	void load_season(char file_name[]);
	void save_season(char file_name[]);
	void load_data();			// Data built into code
	void assign_cars();
	void new_season();
	void display_season();
	void display_driver_position_and_status(Driver*,short,short,int);
	void display_driver_championship(short);
	void display_constr_championship(short);
	void display_driver_results(short);
	void display_grid_positions(short);
	void qualifying(short, Circuit*);
	void sort_drivers_by_qualifying(short);
	void sort_drivers_by_distance(short,Circuit*);
	void pit_stops(short,short,TrackCondition);
	void alignment(short);
	void race_results(short);
	void rank_drivers();
	void rank_constr();
	void post_race(short);
	void grand_prix(Circuit*, short);

	// Constructors
	Season()
	{
		short att[] = {9,9,9};	// {grip, durability, upToTemp}
		tyreSupplier[int_zero] = new TyreSupplier("Bridgestone",att);
		load_data();
	}
	Season(char file_name[]) {
		short att[] = {9,9,9};	// {grip, durability, upToTemp}
		tyreSupplier[int_zero] = new TyreSupplier("Bridgestone",att);
		load_season(file_name);
	}
};

