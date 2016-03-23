#include "Circuit.cpp"

struct World
{
	Country nation[MAX_COUNTRIES];
	Circuit track[MAX_CIRCUITS];
	short countries, circuits;

	// Member functions
	void load_data();
	void edit_world();
	void load_world (char[]);
	void save_world(char[]);
	Country create_country();
	Circuit create_circuit();
	void init_countries(Country countries[], short total);
	void init_circuits(Circuit circuits[], short total);
	void add_countries(Country countries[], short total);
	void add_circuits(Circuit circuits[], short total);
	void display_world();

	// Constructors
	World() {
		load_data();
	}
	World(char file_name[]) {
		load_world(file_name);
	}
	World(Country country[], short total)
	{
		countries = total;
        	for (int i=0;i<total;i++) nation[i]=country[i];
	}
};

