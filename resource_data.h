//Fe Jackson
//CS 261

//"resource_data.h"

/*

	The resource_data struct contains a string of the name of the resource, an
	int containing the total number of resources for that year, and an array of
	12 ints called amount_each_month. In amount_each_month, each index number 
	represents a month, and the int in each index is the amount of this 
	resource that's produced that month.

*/

#pragma once

#include <string>
using namespace std;





struct resource_data
{
	string name;
	int total_this_year;	
	int amount_each_month [12];	
};






