//Fe Jackson
//CS 261

//"entry.h"

/*
	This file contains a class called entry. It has a constructor, 4 ints,
	and two strings. This class stores an entry of a date, a station, a 
	resource, and the amount of that resource produced on that date at that
	station. It also has a get_data function that passes the data from the entry
	object to the function that calls the get_data function.
*/




#pragma once

#include <string>

using namespace std;





class entry 
{
	public:
		//constructor
		entry (int cur_year, int cur_month, int cur_day, string cur_station,
			string cur_resource, int cur_amount);

		//passes data members to the function that calls this function
		void get_data (int & get_year, int & get_month, 
			string & get_station, string & get_resource, 
			int & get_amount);
			
	private:	
		int year;
		int month;
		int day;
		string station;
		string resource;
		int amount;
};
