//Fe Jackson
//CS 261

//"entry.cpp"

/*
	This file contains a class called entry. It has a constructor, 4 ints,
	and two strings. This class stores an entry of a date, a station, a 
	resource, and the amount of that resource produced on that date at that
	station. It also has a get_data function that passes the data from the entry
	object to the function that calls the get_data function.
*/





#include "entry.h"





entry::entry(int cur_year, int cur_month, int cur_day, string cur_station,
	string cur_resource, int cur_amount)
{
	year = cur_year;
	month = cur_month;
	day = cur_day;
	station.append (cur_station);
	resource.append (cur_resource);
	amount = cur_amount;
}





//passes all data members except day to the function that calls this function
void entry::get_data (int & get_year, int & get_month, string & get_station, 
	string & get_resource, int & get_amount)
{
	if (!get_station.empty())
	{
		get_station.clear ();
	}

	if (!get_resource.empty())
	{
		get_resource.clear();
	}

	get_year = year;
	get_month = month;
	get_station.append (station);
	get_resource.append (resource);
	get_amount = amount;
}






