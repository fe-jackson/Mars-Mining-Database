#include <iostream>
#include <fstream>
#include <string>
#include "productiondb.h"
#include "entry.h"
#include "reporter.h"

using namespace std;

int main()
{
    //Get the file name
    char datafile [30];

    cout << "\nPlease type in the name of the datafile.\n";

    cin.get(datafile, 30, '\n');
    cin.ignore(100, '\n');

    //Read the data
    productiondb db;
    ifstream infile;

    infile.open (datafile);

    if (!infile)
    {
        cout << "\nError: File not found.\n";
    }
    else
    {
        int year;
        int month;
        int day;
        string station;
        string resource;
        int amount;

        while (!infile.eof())
        {
            infile >> year;
            infile >> month;
            infile >> day;
            infile >> station;
            infile >> resource;
            infile >> amount;

            if (!infile.eof())
            {
                entry oneEntry(year, month, day, station, resource, amount);
                db.addData(oneEntry);
            }
        }

        //Print the report
        reporter reporter(db);

        for (int year = 2045; year <= 2047; year++)
        {
            reporter.printFullReport(year);
        }
        for (int year = 2045; year <= 2047; year++)
        {
            reporter.printStationReport(year);
        }
    }

    return 0;
}

