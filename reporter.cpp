//Fe Jackson
//CS 261
//Program 1

//"reporter.cpp

/*
	This class has two functions that output a report of the data in the 
	productiondb object passed to this class in the constructor. It also has
	multiple private functions that are used to help the public functions work
*/

#include "reporter.h"





//constructor
reporter::reporter (productiondb database) : db (database)
{	

}





//prints the monthly totals of each resource at each station in 
//the database for the corresponding year
void reporter::printFullReport (int year)
{
	//iterators to travel year_data and station_data vectors
	vector<year_data>::iterator cur_y;
	
	vector<station_data>::iterator cur_s;
	vector<station_data>::iterator s_end;

	//makes cur_y point to a year_data object with a year that matches the
	//year int argument passed to this function
	get_year_pointer (year, cur_y);

	cout << "\n\n*******" << cur_y->year << "*******\n";

	//if the stations vector in cur_y is empty, print nothing but two lines
	if (cur_y->stations.empty())
	{
		cout << "\n\n";
	}
	
	//if the stations vector in cur_y is NOT empty, print all the data in it
	else
	{
		cur_s = cur_y->stations.begin();
		s_end = cur_y->stations.end ();

		//print all the station_data objects' info until every station's
		//info in the stations vector in cur_y is printed	
		while (cur_s != s_end)
		{
			print_one_station (cur_s);
			++cur_s;
			cout << endl;
		}
	}	
}





//prints a log of the yearly totals of each resource at each station
//in the database for the corresponding year
void reporter::printStationReport (int year)
{
	//iterators that point to the objects in the years and years2 vectors
	//that correspond with the int year argument passed to this function
	vector<year_data>::iterator cur;
	vector<year_data_2>::iterator cur2;

	//iterators used to travel vectors
	vector<resource_data_2>::iterator cur_r;
	vector<resource_data_2>::iterator r_end;

	vector<station_data_2>::iterator cur_s;
	vector<station_data_2>::iterator s_end;
	
	vector<station_data>::iterator cur_s1;
	vector<station_data>::iterator s1_end;

	//gets a pointer from the years year_data vector to the year that 
	//corresponds with the year int argument. If none is found, it 
	//makes one.
	get_year_pointer (year, cur);

	//variables that are used to properly align yearly resource amounts
	//produced by each station when they are printed
	int count = 0;
	int count2 = 0;
	int amount = 0;

	cout << "*******" << year << "*******\n\n";

	//if there are stations in cur, print the info
	if (!cur->stations.empty())
	{
		//gets a pointer from the years2 year_data_2 vector to the year 
		//that corresponds with the year int argument passed to this 
		//function. If none is found, it makes one
		get_years2_pointer (year, cur, cur2);

		cur_s1 = cur->stations.begin();
		s1_end = cur->stations.end();

		cout << "\t";

		//output all the stations in order
		while (cur_s1 != s1_end)
		{
			cur_s1->name.shrink_to_fit ();
			cout << "\t" << cur_s1->name;
			++cur_s1;
		}
	
		cout << endl;

		//set the resource_data_2 iterators
		cur_r = cur2->resources.begin();
		r_end = cur2->resources.end();

		//output the resources and the amounts of them produced by each
		//station
		while (cur_r != r_end)
		{
			//set the station_data iterator
			cur_s1 = cur->stations.begin ();

			//set the station_data_2 iterators
			cur_s = cur_r->stations.begin ();
			s_end = cur_r->stations.end ();
	
			
			cur_r->name.shrink_to_fit ();
		
			//print the resource name	
			cout << cur_r->name;
			
			if (cur_r->name.size () < 8)
			{
				cout << "\t";
			}
		
			//print the station amounts
			while (cur_s1 != s1_end)
			{
				cout << "\t";

				count = cur_s1->name.size();			
	
				//if there's no station_data_2 object in this
				//vector that matches the name in cur_s1,
				//output 0
				if (cur_s == s_end)
				{
					for (count = count; count > 1; --count)
					{
						cout << " ";
					}
					cout << "0";
				}
				//if a name match is found, output the resource
				//amount produced, preceded by spaces 
				//that will allign the amount to the right, in 
				//line with the station name
				else if (cur_s->name.compare (cur_s1->name) == 0)
				{
					amount = cur_s->amount;

					for (count2 = 1; count > 1; --count)
					{
						count2 *= 10;
					}
					
					while (count2 > 10)
					{
						if (count2 > amount)
						{
							cout << " ";
						}
						else
						{
							count2 = 10;
						}
						count2 /= 10;
					}

					cout << amount;
					++cur_s;
				}
				//if there's no station_data_2 object in this
				//vector that matches the name in cur_s1,
				//output 0
				else
				{
					for (count = count; count > 1; --count)
					{
						cout << " ";
					}
					cout << "0";
				}
				
				++cur_s1;
			}
			
			cout << endl;
		
			//
			++cur_r;
		}

		cur_s1 = cur->stations.begin ();
	
		cout << "\tTotal";
		//output the totals, preceded by spaces that will allign the amount
		// to the right, in line with the station name
		while (cur_s1 != s1_end)
		{
			cout << "\t";
			cur_s1->name.shrink_to_fit();
			count = cur_s1->name.size();
			amount = cur_s1->total_resources;		
	
			for (count2 = 1; count > 1; --count)
			{
				count2 *= 10;
			}
					
			while (count2 > 10)
			{
				if (count2 > amount)
				{
					cout << " ";
				}
				else
				{
					count2 = 10;
				}
				count2 /= 10;
			}
			cout << amount;
			++cur_s1;
		}
	}

	cout << endl << endl;
}





//gets a pointer from the years year_data vector to the year that 
//corresponds with the year int argument. If none is found, it 
//makes one
void reporter::get_year_pointer (int year, vector<year_data>::iterator & cur)
{
	vector<year_data>::iterator end;
	
	int found = 0;
	int finished = 0;
	
	//object to add data to and insert if no match is foubnd	
	year_data to_add;

	if (years.empty ())
	{
		finished = 1;
	}

	else
	{
		cur = years.begin ();
		end = years.end ();
	}

	//search the years vector until you reach the end, find a match, or reach
	//a year that is chronilogically after the year int argument
	while (!finished)
	{
		if (cur == end)
		{
			finished = 1;
		}
		
		else if (cur->year == year)
		{
			finished = 1;
			found = 1;
		}
	
		else if (cur->year < year)
		{
			finished = 1;
		}	

		else
		{
			++cur;
		}
	}	

	if (!found)
	{
		db.getYear (to_add, year);
	
		cur = years.insert (cur, to_add);

	}
}





//prints one station's info. This is called in printFullReport
void reporter::print_one_station (vector<station_data>::iterator & cur)
{
	vector<resource_data>::iterator cur_r;
	vector<resource_data>::iterator r_end;
	int month_num;
	int * cur_month;
	cout << "\nStation: " << cur->name << "\n\n\t\tJan\tFeb\tMar\tApr\tMay\t"
		<< "Jun\tJul\tAug\tSep\tOct\tNov\tDec\t Tot\n";
	if (!cur->resources.empty ())
	{
		cur_r = cur->resources.begin ();
		r_end = cur->resources.end ();

		while (cur_r != r_end)
		{
			cur_r->name.shrink_to_fit ();
			
			cout << cur_r->name << "\t";
			
			if (cur_r->name.size () < 8)
			{
				cout << "\t";
			}
			
			cur_month = cur_r->amount_each_month;
			
			for (month_num = 1; month_num <= 12; ++month_num)
			{
				if (*cur_month < 100)
				{
					cout << " ";
				}
				
				if (*cur_month < 10)
				{
					cout << " ";
				}
			
				cout << *cur_month << "\t";
				++cur_month;
			}
			
			if (cur_r->total_this_year < 1000)
			{
				cout << " ";
			}

			if (cur_r->total_this_year < 100)
			{
				cout << " ";
			}
		
			if (cur_r->total_this_year < 10)
			{
				cout << " ";
			}

			cout << cur_r->total_this_year << endl;		

			++cur_r;
		}
	}
}




//gets a pointer from the years2 year_data_2 vector to the year that
//corresponds with the year int argument passed to this function.
//If none is found, it makes one
void reporter::get_years2_pointer (int year, vector<year_data>::iterator & cur,
	vector <year_data_2>::iterator & cur2)
{
	//0 if the end hasn't been reached and no match has been found
	//1 if a the end HAS been reached and no match is found
	//2 if a match has been found
	int end_or_found = 0;

	//set cur2 tot he beginnign of years2
	cur2 = years2.begin ();

	//an iterator that points to the end of the yearsPt2 vector
	vector<year_data_2>::iterator end_of_years2 = years2.end();
	
	//the year object to put data into if no match is found
	year_data_2 year_obj;

	//station_data vector iterators
	vector<station_data>::iterator cur_s1 = cur->stations.begin ();
	vector<station_data>::iterator s1_end = cur->stations.end ();

	//resource_data vector iterators
	vector<resource_data>::iterator cur_r1;
	vector<resource_data>::iterator r1_end;

	//search the years2 vector for a year that matches year
	while (!end_or_found)
	{
		//if the end is reached, make end_or_found equal 1
		if (cur2 == end_of_years2)
		{
			end_or_found = 1;
		}
		//if a match is found, end_or_found equal 2
		else if (cur2->year == year)
		{
			end_or_found = 2;
		}
		//if cur2 reaches an object that should be after cur2 in the 
		//vector, make end_or_found equal 1
		else if (cur2->year < year)
		{
			end_or_found = 1;
		}
		//otherwise, keep searching the vector for a match
		else
		{
			++cur2;
		}
	}

	//if no match is found, insert a new year_data_2 object into the years2
	//vector
	if (end_or_found == 1)
	{
		year_obj.year = year;
		
		while (cur_s1 != s1_end)
		{
			cur_r1 = cur_s1->resources.begin();
			r1_end = cur_s1->resources.end ();
	
			//copy the info from the stations vector of cur into the
			//resources vector of cur2
			while (cur_r1 != r1_end)
			{
				add_entry2 (year_obj, cur_r1->name, cur_s1->name,
					cur_r1->total_this_year);
				++cur_r1;
			}
			++cur_s1;
		}
		
		cur2 = years2.insert (cur2, year_obj);
	}
}





//adds a resource name, station name, and the yearly amount to a 
//the year_data_2 object in years2 at the index of cur_y
void reporter::add_entry2 (year_data_2 & cur_y, string resource, string station, 
	int amount)
{
	//make iterators to travel the resources_data_2 vector with
	vector<resource_data_2>::iterator cur_r = cur_y.resources.begin();
	vector<resource_data_2>::iterator r_end = cur_y.resources.end();

	//make iterators to travel the station_data_2 vector with
	vector<station_data_2>::iterator cur_s;
	vector<station_data_2>::iterator s_end;

	//make objects to put data in so you can push the objects onto the vectors
	station_data_2 s_obj;
	resource_data_2 r_obj;

	//is 1 if the end of the vector is reached or if the current iterator's
	//name should be after the object you need to find or insert
	//
	//is 2 if the name string of the iterator is a match
	//
	//otherwise, it's 0
	int end_or_found = 0;

	//travels the vector until a match is found or until it finds out that
	//it needs to insert a new object into the vector
	while (!end_or_found)
	{
		if (cur_r == r_end)
		{
			end_or_found = 1;
		}
		else if (cur_r->name.compare (resource) > 0)
		{
			end_or_found = 1;
		}
		else if (cur_r->name.compare (resource) == 0)
		{
			end_or_found = 2;
		}
		else
		{
			++cur_r;
		}
	}

	//if no match is found, make new objects and insert them into the vectors
	if (end_or_found == 1)
	{
		s_obj.name.append (station);
		s_obj.amount = amount;

		r_obj.stations.push_back (s_obj);
		r_obj.name.append (resource);

		cur_r = cur_y.resources.insert (cur_r, r_obj);
	}

	else
	{
		//set the station_data_2 vector iterators
		cur_s = cur_r->stations.begin();
		s_end = cur_r->stations.end();

		end_or_found = 0;

		//search the stations vector of cur_r for a match
		while (!end_or_found)
		{
			if (cur_s == s_end)
			{
				end_or_found = 1;
			}
			else if (cur_s->name.compare (station) > 0)
			{
				end_or_found = 1;
			}
			else if (cur_s->name.compare (station) == 0)
			{
				end_or_found = 2;
			}	
			else
			{
				++cur_s;
			}
		}

		//if no match is found, make a new station_data_2 object and 
		//insert it into the stations vector in cur_r
		if (end_or_found == 1)
		{
			s_obj.name.append (station);
			s_obj.amount = amount;

			cur_s = cur_r->stations.insert (cur_s, s_obj);
		}
		
		//if a station match IS found, do nothing
	}
}








