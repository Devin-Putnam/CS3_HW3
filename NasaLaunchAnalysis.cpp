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
TimeCode parse_line(const string& line) {
    size_t pos = line.find(':');   // find the colon
    if (pos == string::npos || pos < 2 || pos + 2 >= line.size()) {
        return TimeCode(0,0,0);    // no valid time
    }

    // Take 2 characters before colon
    string hhStr = line.substr(pos - 2, 2);
    // Take 2 characters after colon
    string mmStr = line.substr(pos + 1, 2);

    // Strip non-digits (just in case)
    string hhDigits, mmDigits;
    for (char c : hhStr) if (isdigit((unsigned char)c)) hhDigits.push_back(c);
    for (char c : mmStr) if (isdigit((unsigned char)c)) mmDigits.push_back(c);

    if (hhDigits.size() != 2 || mmDigits.size() != 2) {
        return TimeCode(0,0,0);  // fallback
    }

    unsigned int hh = stoi(hhDigits);
    unsigned int mm = stoi(mmDigits);

    // Validate ranges
    if (hh > 23 || mm > 59) {
        return TimeCode(0,0,0);
    }

    return TimeCode(hh, mm, 0);  // seconds = 0
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

