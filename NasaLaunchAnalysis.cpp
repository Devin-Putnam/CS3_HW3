#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "TimeCode.h"

using namespace std;

//I have read all the notes for this assignment

// Helper function: split a string into fields
vector<string> split(const string& s, char delim);

// Helper function: parse a line of CSV and return a TimeCode
// If no time is found, handle appropriately
TimeCode parse_line(const string& line);

void parseStringWithStream(const string& line, char delim) {
    stringstream ss(line);
    string item;
    while (getline(ss, item, delim)) {
        cout << item << " , ";  
    }
    cout << endl;
}

//Referenced the Zybook to look at the format 
int main() {
    ifstream inFS("Space_Corrected.csv");
    if (!inFS.is_open()) {
        cout << "Could not open file." << endl;
        return 1;
    }

    string datum;
    while (getline(inFS, datum)) {  // loop reads line by line
        cout << datum << endl;       // print the line
        parseStringWithStream(datum, ','); // parse each line
    }

    if (!inFS.eof()) {
        cout << "Input failure before reaching end of file." << endl;
    }

    inFS.close();
    return 0;
}

