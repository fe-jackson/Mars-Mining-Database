//Fe Jackson
//CS 261

//"station_data.h"

/*
	The station_data vector has a string containing the station name
	and a vector of resource_data objects
*/

#pragma once

#include "resource_data.h"
#include <vector>





struct station_data
{
	string name;
	int total_resources;
	vector <resource_data> resources;
};





