#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "TimeCode.h"

//intakes a line from the file
//returns the TimeCode Object for time at that line
void parse_line(string){
    ifstream inFS;
    int fileNum;
    string datum;

    inFS.open("Space_Corrected.csv");

    if (!inFS.is_open()) {
        cout << "Could not open file." << endl;
        return 1;
   }

    getline(inFS, datum);
    cout << endl << datum << endl;

    parseStringWithStream(inFS, ','); 
    return 0;

    if (!inFS.eof()) {
        cout << "Input failure before reaching end of file." << endl;
    }

    inFS.close();

}

vector<string> split(string, delim){
    //returns a vector containing the sub-string
}

