//Fe Jackson
//CS 261
//Program 1

//"productiondb.cpp"

/*
	A production database that stores the data of how much of each resource 
	that each station produced, each year using a vector of year_data objects.
*/

#include "productiondb.h"





//the class constructor when no argument is passed to this function
productiondb::productiondb ()
{

}





//the class constructor that copies the info from another productiondb object into
//this one
productiondb::productiondb (productiondb & copy_from)
{
	//if the years vector in copy_from isn't empty, copy its data into the 
	//years vector that's in this productiondb that is being constructed
	if (!copy_from.years.empty())
	{
		//make a year_data object to push onto the year vector of the
		//database that's being constructed
		year_data to_add;

		//make iterators to travel the years vector in copy_from with
		vector<year_data>::iterator from_cur = copy_from.years.begin ();
		vector<year_data>::iterator from_end = copy_from.years.end ();
	
		//push copies of every year_data object in the years vector in 
		//copy_from until all have been copied and pushed
		while (from_cur != from_end)
		{
			to_add.year = from_cur->year;

			to_add.stations.clear ();
			copy_stations_vector (to_add.stations, from_cur->stations);
			
			years.push_back (to_add);

			++from_cur;
		}
	}
}



//this function adds the data from the entry object passed to this function into
//the year_data vector in the private par of the class
int productiondb::addData (entry & to_add)
{
	//makes variables to hold  to_add's data members
	int year = 0;
	int month = 0;
	string station;
	string resource;
	int amount = 0;
	
	to_add.get_data(year, month, station, resource, amount);

	//if the month isn't an int between 1 and 12 (inclusive), then this 
	//function returns 0
	if (month < 1 || month > 12)
	{
		return 0;
	}

	//makes vector iterators that will be keep track of the current index 
	//as it searches the vectors
	vector<year_data>::iterator cur_year;
	vector<station_data>::iterator cur_station;
	vector<resource_data>::iterator cur_resource;

	//these iterators will point to the end of each vector to save runtime
	vector<year_data>::iterator years_end;
	vector<station_data>::iterator stations_end;
	vector<resource_data>::iterator resources_end;
	
	//these objects will be ititialized and pushed onto the appropriate vectors
	//if no match is found in one of the vectors
	year_data cur_y;
	station_data cur_s;
	resource_data cur_r;

	//end_or_found is "1" if an iterator reaches the end of a vector without
	//finding a match
	//it's "2" if a match IS found. 
	//If it's 0, a match hasn't been found yet and the iterator hasn't reached 
	//the end of the vector yet
	int end_or_found = 0;

	//if the stations vector is empty, make end_or_found equal 1
	if (years.empty())	
	{
		end_or_found = 1;
	}
	else
	{	
		//make a vector iterator for the stations vector used to search it
		//for a name match
		cur_year = years.begin ();
		years_end = years.end ();
	}
		
	//searches the stations vector for a station_data object that
	//has a name that matches the station string argument passed
	//to this function
	while (end_or_found == 0)
	{
		//if the whole list has been searched, make end_or_found = 1
		if (cur_year == years_end)
		{
			end_or_found = 1;
		}
		//if a match has been found, make end_or_found = 2
		else if (cur_year->year == year)
		{
			end_or_found = 2;
		}
		//if cur_year's index's year is less than the year arguments,
		//make end_or_found 1 so the program will know to insert at the
		//cur_year's current index
		else if (cur_year->year < year)
		{
			end_or_found = 1;
		}
		//if no match has been found and there's still more objects in
		//the vector to be searched, make cur_year point to the next
		//object in the vector
		else
		{
			++cur_year;
		}
	}

	//if no match is found, add a new year_data object with the appropriate
	//data in it the the years vector 
	if (end_or_found == 1)
	{
		//fill the cur_r object
		cur_r.name.append (resource);
		cur_r.total_this_year = amount;

		for (int cur_month = 0; cur_month < 12; ++cur_month)
		{
			cur_r.amount_each_month [cur_month] = 0;
		}

		cur_r.amount_each_month[month - 1] = amount;

		//fill the cur_s object and push cur_r onto the resources vector of
		//cur_s
		cur_s.resources.push_back (cur_r);

		cur_s.name.append (station);		
		
		cur_s.total_resources = amount;

		//fill the cur_y obejct and push cur_s onto the stations vector of 
		//cur_y
		cur_y.year = year;
		cur_y.stations.push_back(cur_s);

		//push cur_y onto the years vector		
		years.insert(cur_year, cur_y);	
	}


	
	//if a match IS found, this searches the stations vector for a 
	//station_data object that has a name that matches the station
	//string argument passed to this function
	else
	{
		//reset end_or_found to reuse it
		end_or_found = 0;
		
		//if the stations vector is empty, make end_or_found equal 1
		if (cur_year->stations.empty())	
		{
			end_or_found = 1;
		}
		//else, intialize the iterators for the search
		else
		{
			cur_station = cur_year->stations.begin();
			stations_end = cur_year->stations.end();
		}

		//searches the stations vector for a station_data object that
		//has a name that matches the station string argument passed
		//to this function
		while (!end_or_found)
		{
			//if the whole list has been searched, make end_or_found
			//equal 1
			if (cur_station == stations_end)
			{
				end_or_found = 1;
			}
			//if a match has been found, make end_or_found = 2
			else if (cur_station->name.compare (station) == 0)
			{
				end_or_found = 2;
			}
			//if cur_station's index's name is alphabetically before
			//the station string, make end_or_found equal one so the
			//function will know to insert at cur_station's current
			//index
			else if (cur_station->name.compare (station) > 0)
			{
				end_or_found = 1;
			}
			//if no match has been found and there's still more objects
			//in the vector to be searched, make cur_station point to 
			//the next object in the vector
			else
			{
				++cur_station;
			}
		} 

		//if no match was found, add a new station_data object with a new 
		//resource_data object in its vector to the end of the resources 
		//vector
		if (end_or_found == 1)
		{

			//fill the cur_r object
			cur_r.name.append (resource);
			cur_r.total_this_year = amount;

			for (int cur_month = 0; cur_month < 12; ++cur_month)
			{
				cur_r.amount_each_month [cur_month] = 0;
			}

			cur_r.amount_each_month[month - 1] = amount;
	
			//fill the cur_s object and push cur_r onto the resources 
			//vector of cur_s
			cur_s.resources.push_back (cur_r);
			cur_s.name.append (station);		
	
			cur_s.total_resources = amount;
	
			//push cur_s onto the stations vector of the cur_year
			//iterator
			cur_year->stations.insert(cur_station, cur_s);
		}
	
		//if a match IS found, this searches the resources vector for a 
		//resource_data object that has a name that matches the resource
		//string argument passed to this function
		else
		{
			//reset end_or_found to use it again
			end_or_found = 0;
			
			//if the resources vector is empty, make end_or_found 
			//equal 1
			if (cur_station->resources.empty())	
			{
				end_or_found = 1;
			}
			else
			{
				cur_resource = cur_station->resources.begin();
				resources_end = cur_station->resources.end();
			}
		
			//search the resources vector for a resource_data object 
			//that has a name that matches the resource string argument
			//passed to this function
			while (!end_or_found)
			{
				//if the whole list has been searched, make 
				//end_or_found equal 1
				if (cur_resource == resources_end)
				{
					end_or_found = 1;
				}
				//if a match has been found, make end_or_found = 2
				else if (cur_resource->name.compare(resource) == 0)
				{
					end_or_found = 2;
				}
				//if cur_resource's index's name is alphabetically 
				//before the resource string, make end_or_found 
				//equal one so the function will know to insert at 
				//cur_resource's current index
				else if (cur_resource->name.compare(resource) > 0)
				{
					end_or_found = 1;
				}
				//if no match has been found and there's still more
				//objects in the vector to be searched, make 
				//cur_resource point to the next object in the 
				//vector
				else
				{
					++cur_resource;
				}
			}
	
			//if no match is found, add a new resource_data object to 
			//the end of the vector
			if (end_or_found == 1)
			{
				//fill the cur_r object
				cur_r.name.append (resource);
				cur_r.total_this_year = amount;
			
				for (int cur_month = 0; cur_month < 12; ++cur_month)
				{
					cur_r.amount_each_month [cur_month] = 0;
				}

				cur_r.amount_each_month[month - 1] = amount;
			 
				//push cur_r onto the resources vector of the
				//cur_station iterator
				cur_station->resources.insert(cur_resource, cur_r);
				cur_station->total_resources += amount;
			}

			//if a match IS found, add amount to the current 
			//resource_data's total_this_year int and the appropriate 
			//month in amount_each_month
			else
			{
				cur_resource->total_this_year += amount;
				cur_resource->amount_each_month[month-1] += amount;
				cur_station->total_resources += amount;
			}
		}	
	}

	//return 1 to let the function that called this function know that 
	//theadd was a success
	return 1;
}





//clears any data from year_obj's stations vector and copies 
//data into it from the year_data object in the database that 
//corresponds with the year int argument.
//Returns 0 is the year is not found in the database. 
//Returns 1 if the copy was a success
int productiondb::getYear (year_data & year_obj, int year)
{
	//if there's data in year_obj's stations vector, clear it
	if (!year_obj.stations.empty())
	{
		year_obj.stations.clear();
	}

	//make the year int in year_obj equal the year argument passed to this 
	//function.
	year_obj.year = year;

	//found is 1 if a match is found in the vector
	int found = 0;

	//turns to 1 once either a match is found or the whole years vector has
	//been searched
	int end = 0;
	
	//this iterator is used to search years for a match
	vector <year_data>::iterator cur_year;
	
	//this iterator will point to years.end() if the years vector isn't empty
	//this variable is used to save runtime
	vector <year_data>::iterator years_end;

	//if the years vector is empty, make no_match equal "1"
	if (years.empty())
	{
		end = 1;
	}

	else
	{
		cur_year = years.begin ();
		years_end = years.end ();
	}

	//search the vector for a match until a match is found or until the whole
	//vector has been searched
	while (!end)
	{
		//if the whole vector has been searched, make "end" equal "1"
		if (cur_year == years_end)
		{
			end = 1;	
		}
		//if a match has been found, make "end" and "found" both equal "1"
		else if (cur_year->year == year)
		{
			found = 1;
			end = 1;
		}
		//if no match has been found and the whole vector hasn't been 
		//searched, increment cur_year to continue searching
		else
		{
			++cur_year;
		}
	}

	//if a match was found and the match's stations vector is not empty,
	//copy the match's stations vector into the stations vector in year_obj
	if (found && !cur_year->stations.empty ())
	{
			copy_stations_vector (year_obj.stations, 
				cur_year->stations);
	}

	//return found	
	return found;
}





//copies the "from" station_data vector into "to"
void productiondb::copy_stations_vector (vector<station_data> & to,
	vector<station_data> from)
{
	//the object that will be pushed onto "to"
	station_data obj;

	//iterators that point to the current and last indices in "from"
	vector<station_data>::iterator from_cur = from.begin ();
	vector<station_data>::iterator from_end = from.end ();

	//copy the info in "from_cur" into "obj" and push it onto "to" until
	//the whole vector is copied
	while (from_cur != from_end)
	{
		//clear the name in obj and copy the name in from_cur into it
		obj.name.clear ();
		obj.name.append (from_cur->name);
	
		//copy total_resources from "from_cur" to obj	
		obj.total_resources = from_cur->total_resources;
	
		//clear the resources vector in obj and copy the resources in
		//from_cur into it
		obj.resources.clear ();
		copy_resources_vector (obj.resources, from_cur->resources);

		//push "obj" onto "to"
		to.push_back (obj);
	
		//go the the next index in "from"	
		++from_cur;
	}
}





//copies the "from" resource_data vector into "to"
void productiondb::copy_resources_vector (vector<resource_data> & to,
	vector<resource_data> from)
{
	//the object that will be pushed onto "to"
	resource_data obj;

	//iterators that point to the current and last indices in "from"
	vector<resource_data>::iterator from_cur = from.begin ();
	vector<resource_data>::iterator from_end = from.end ();
		
	//pointers to amount_each_month indices
	int * to_month_ptr = obj.amount_each_month;
	int * from_month_ptr = from_cur->amount_each_month;

	//int that keeps track of the current index in amount_each_month
	int cur_index = 0;
	
	//copy the info from "cur_from" into "obj" and push "obj" onto "to"
	while (from_cur != from_end)
	{	
		//reset pointers to amount_each_month indices
		to_month_ptr = obj.amount_each_month;
		from_month_ptr = from_cur->amount_each_month;
		
		//clear the name in obj
		obj.name.clear ();

		//copy the name string and the total_this year int in from_cur into
		//obj
		obj.name.append (from_cur->name);
		obj.total_this_year = from_cur->total_this_year;
	

		//copy the amount_each_month array in from_cur into the 
		//amount_each_month array in obj
		for (cur_index = 0; cur_index < 12; ++cur_index)
		{
			*to_month_ptr = *from_month_ptr;
			++to_month_ptr;
			++from_month_ptr;
		}
	
		//push "obj" onto "to"
		to.push_back (obj);

		//go to the next index in "from"
		++from_cur;
	}
}





