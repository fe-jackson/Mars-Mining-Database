//Fe Jackson
//CS 261
//Program 1

//"productiondb."

/*
	A production database that stores the data of how much of each resource that
	each station produced, each year using a vector of year_data objects.
*/

#pragma once

#include "year_data.h"
#include "entry.h"





class productiondb 
{
	public:
		//constructor for an empty database
		productiondb();
		
		//constructor to copy a different database into this new database
		productiondb (productiondb & copy_from);

		//adds the data from to_add to the database
		int addData (entry & to_add);

		//clears any data from year_obj's stations vector and copies 
		//data into it from the year_data object in the database that 
		//corresponds with the year int argument.
		//Returns 0 is the year is not found in the database. 
		//Returns 1 if the copy was a success
		int getYear (year_data & year_obj, int year);
		
	
	private:
		vector <year_data> years;

		//copies a station_data vector from "from_cur" to "from_end", not
		//including "from_end", into "to"
		void copy_stations_vector (vector<station_data> & to,
			vector<station_data> from);

		//copies a resource_data vector from "from_cur" to "from_end", not
		//including "from_end", into "to"
		void copy_resources_vector (vector<resource_data> & to,
			vector<resource_data> from);
};	





