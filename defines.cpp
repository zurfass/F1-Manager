#pragma once

#include "defines.h"

// TODO: reference any additional headers you need in defines.h
// and not in this file

// ----------------------------- GLOBAL FUNCTIONS ---------------------------------

short cha2sho(char c)
{
	short s;
	if ((c >= 48) && (c <=57)) s=c-48;
	else s = -1;
	return s;
}

short str2sho(string s)
{
	short i;
	char number[4];
	char s_length = s.size();
	s.copy(number,s_length,0);
	i = cha2sho(number[3]);
	i += 10*cha2sho(number[2]);
	i += 100*cha2sho(number[1]);
	i += 1000*cha2sho(number[0]);
	return i;
}

char second_byte(short both_bytes)
{
	char c = both_bytes % 256;
	return c;
}

// Converts distance in meters to miles
int metersToMiles(int meters) {
	int km = meters/1000;
	return (km*5/8);
}

// Calculate value raised to a power
int power(int value, int raised) {
	if (raised <= int_zero) return 1;
	else {
		int returnValue = value*power(value,(raised-1));
		return returnValue;
	}
}

// Return random number from 0 to (maximum-1)
int randNumber(int maximum) {
	int number = rand() % maximum;
	return number;
}

// Return random number in given range
int randNumber(int bottom, int top) {
	int number = rand() % (top-bottom+1);
	number += bottom;
	return number;
}

// Print spaces to align data
void printSpaces(int spaces) {
	for (int i=int_zero; i<spaces; i++) cout<<" ";
}

void display_array(char c[],char total)
{
	for (char j=0;j<total;j++) {cout << c[j];}
}

// Receives the time in hundredths of a second and displays in
// min:sec.hsec format
void display_time(int time)
{
	int seconds = time/100;
	int hundredths = time%100;
	if (seconds >= 60) {
		cout << (seconds/60) << ":";
		seconds = seconds%60;
	}
	else printSpaces(2);
	if (seconds < 10) cout << "0";
	cout << seconds << ".";
	if (hundredths < 10) cout << "0";
	cout << hundredths;
}

// Receives time in seconds and displays in hrs:min:sec format
void display_clock(int time)
{
	int minutes = time/60;
	int seconds = time%60;
	if (minutes >= 60) {
		cout << (minutes/60) << ":";
		minutes = minutes%60;
	}
	else printSpaces(2);
	if (minutes < 10) cout << "0";
	cout << minutes << ":";
	if (seconds < 10) cout << "0";
	cout << seconds;
}

void display_rank(short rank)
{
	if (rank < 10) printSpaces(1);
	cout << rank << ". ";
}

