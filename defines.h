// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>	// printf, scanf, puts, NULL
#include <iostream>
#include <fstream>
#include <string>
#include <valarray>	// rand
#include <stdlib.h>	// srand, rand
#include <time.h>	// time

// Constants
#define MAX_CHARS	15
#define MAX_ENTRIES	24
#define MAX_TEAMS	12
#define MAX_COUNTRIES	100
#define MAX_CIRCUITS	100
#define MAX_RACES	20

// Grand Prix weekend
#define MAX_Q_LAPS	3
#define WEATHER_RANGE	35
#define REFUEL_RATE	12000
#define MAX_TYRES	12

// Retirement types
#define NO_FAIL		0
#define DRIVETRAIN_FAIL	1
#define GEARBOX_FAIL	2
#define SUSPENSION_FAIL	3
#define ENGINE_FAIL	4
#define TYRE_FAIL	5
#define SPUN_OFF	6
#define ACCIDENT	7

#define SOFT		0
#define HARD		1
#define INTERS		2
#define	WETS		3

using namespace std;

const int int_zero = 0;

// ----------------------------- OBJECT TYPES ---------------------------------

// Components
struct Component;
struct Bodywork;
struct Drivetrain;
struct Engine;
struct Fuel;
struct GearBox;
struct Suspension;
struct Tyre;

// Personell
struct Contract;
struct Driver;
struct Engineer;

// World
struct Circuit;
struct Company;
struct Constructor;
struct Country;
struct EngineSupplier;
struct Season;
struct Sponsor;
struct World;

// --------------------------- GLOBAL CONSTANTS -------------------------------

const char max_cars = 3;
const int fuel_unit = 15000;
const char max_chars = MAX_CHARS;
const char max_chars2 = max_chars + 2;
const string retirement_reason[] = {"Still active","Transmission","Gear Box","Suspension",
					"Engine","Tyre Burst","Spun Off","Collision"};

enum Weather {sunny,cloudy,drizzle,rain,pouring};
enum Temperature {cold,moderate,hot};
enum TrackCondition {dry,moist,damp,wet,flood};
enum TyreType {soft,hard,inter,wets};

// ------------------------ GLOBAL FUNC PROTOTYPES ----------------------------

bool overtake (short speed1,short speed2,float gap);
int randNumber(int max);
int randNumber(int bottom, int top);
void display_array(char c[],char total);
void display_status(Weather a, TrackCondition b);
void display_time(int hundredths);
void display_clock(int seconds);
void display_rank(short rank);

