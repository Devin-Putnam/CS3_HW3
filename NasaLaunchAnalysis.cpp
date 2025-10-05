#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "TimeCode.h"

using namespace std;

//Parse a line and return true for success and false for failure
bool parse_line(const string& line, TimeCode& tc) {

    //https://www.geeksforgeeks.org/cpp/stringnpos-in-c-with-examples/
    size_t start = line.find('"');
    if (start == string::npos){
        return false;
    }

    size_t end = line.find('"', start + 1);

    if (end == string::npos){
        return false;
    } 

    //https://cplusplus.com/reference/string/string/substr/
    string dateStr = line.substr(start + 1, end - start - 1);

    //Find the time by finding the colon
    size_t colon = dateStr.find(':');
    if (colon == string::npos || colon < 1){
        return false;
    } 

    //Get the hours as a string
    string hoursStr;
    if (colon >= 2){
        hoursStr = dateStr.substr(colon - 2, 2);
    } 
    else {
        hoursStr = dateStr.substr(colon - 1, 1);
    }

    //Find the minutes as a stirng
    string minutesStr = dateStr.substr(colon + 1, 2);

    //Get seconds as a string
    string secondsStr = "0";
    size_t secondColon = dateStr.find(':', colon + 1);
    if (secondColon != string::npos && secondColon + 2 < dateStr.size()) {
        secondsStr = dateStr.substr(secondColon + 1, 2);
    }

    string hourDigits;
    string minDigits; 
    string secondsDigits;

    for (char c : hoursStr){
         if (isdigit((unsigned char)c)){
            hourDigits.push_back(c);
         }
    }
    for (char c : minutesStr){
         if (isdigit((unsigned char)c)) {
            minDigits.push_back(c);
         }
    }
    for (char c : secondsStr){
        if (isdigit((unsigned char)c)) {
            secondsDigits.push_back(c);
        }
    }


    if (hourDigits.empty() || minDigits.empty()) {
        return false;
    }


    unsigned int hour = stoi(hourDigits);
    unsigned int min = stoi(minDigits);
    
    unsigned int sec;
    if (secondsDigits.empty()) {
        sec = 0;
    } else {
        sec = stoi(secondsDigits);
    }

    //Validate the time components
    if (hour > 23 || min > 59 || sec > 59){
        return false;
    }

    //If all checks pass, create the TimeCode object and return true
    tc = TimeCode(hour, min, sec);
    return true;
}

int main() {
    ifstream inFS("Space_Corrected.csv");
    if (!inFS.is_open()) {
        cout << "Could not open file." << endl;
        return 1;
    }

    string line;
    vector<TimeCode> times;

    // Skips the first line
    getline(inFS, line);

    //Read and Parse
    while (getline(inFS, line)) {
        TimeCode temp_tc;
        if (parse_line(line, temp_tc)) {
            times.push_back(temp_tc);
        }
    }

    inFS.close();

    cout << times.size() << " data points." << endl;

    //Sums the times
    if (!times.empty()) {
        TimeCode total(0,0,0);
        for (const TimeCode& tc : times) {
            total = total + tc;
        }

        //Gets the average
        TimeCode average = total / times.size();
        cout << "AVERAGE: " << average.ToString() << endl;
    } else {
        cout << "No valid time data found." << endl;
    }

    return 0;
}