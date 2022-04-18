//Fe Jackson
//CS 261
//Program 1

//"reporter.h"

/*
	This class has two functions that output a report of the data in the 
	productiondb object passed to this class in the constructor. It also has
	multiple private functions that are used to help the public functions work
*/

#pragma once

#include "productiondb.h"
#include "year_data_2.h"
#include <iostream>





class reporter
{
	public:
		//constructor
		reporter (productiondb database);
	
		//prints the monthly totals of each resource at each station in 
		//the database for the corresponding year
		void printFullReport (int year);

		//prints a log of the yearly totals of each resource at each station
		//in the database for the corresponding year
		void printStationReport (int year);

	private:
		productiondb db;

		//a vector of year_data objects for the full reports	
		vector <year_data> years;
	
		//a vector of year_data object for the station reports
		vector <year_data_2> years2;

		//gets a pointer from the years year_data vector to the year that 
		//corresponds with the year int argument. If none is found, it 
		//makes one
		void get_year_pointer (int year, vector<year_data>::iterator & cur);

		//prints one station's info. This is called in printFullReport
		void print_one_station (vector<station_data>::iterator & cur);

		//gets a pointer from the years2 year_data_2 vector to the year that
		//corresponds with the year int argument passed to this function.
		//If none is found, it makes one
		void get_years2_pointer (int year, 
			vector<year_data>::iterator & cur,
			vector<year_data_2>::iterator & cur2);

		//adds a resource name, station name, and the yearly amount to a 
		//the year_data_2 object in years2 at the index of cur_y
		void add_entry2 (year_data_2 & cur_y, string resource, 
			string station, int amount);

};	
