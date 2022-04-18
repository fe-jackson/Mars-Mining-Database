//Fe Jackson
//CS 261
//Program 1

//"resource_data_2.h"

/*
	The resource_data_2 struct contains a string called name and a vector of
	station_data_2 objects. This struct is used for the printStationData 
	function in the reporter class. There's a vector of resource_data_2 objects
	in the year_data_2 struct
*/

#pragma once

#include <vector>
#include "station_data_2.h"





struct resource_data_2
{
	string name;
	vector <station_data_2> stations;
};

