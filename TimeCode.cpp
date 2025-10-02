// Author: Devin Putnam

/* 9/26/2025
HW 3: Create a type TimeCode that displays the time in an hour:minuite:second format to the user.
The real time value is stored as an instance variable t that is only seen by the user through abstraction. 
*/

#include <iostream>
#include <assert.h>
#include <stdexcept>
#include <sstream>
#include "TimeCode.h"

using namespace std;

TimeCode::TimeCode(const TimeCode& other) {
    t = other.t;  
}


//The code must use the time as t
long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec){
   return static_cast<unsigned long long>(hr)  * 3600
   + static_cast<unsigned long long>(min) * 60
   + sec;

}

//Calls the helper function to convert to seconds
TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec){
    t = ComponentsToSeconds(hr, min, sec);
}

//Needed to display number of hours
void TimeCode::SetHours(unsigned int hours) {
    unsigned int m = GetMinutes();
    unsigned int s = GetSeconds();
    t = ComponentsToSeconds(hours, m, s);
}

//Needed to display number of minutes
void TimeCode::SetMinutes(unsigned int minutes) {
    if (minutes >= 60) {
        throw invalid_argument("minutes must be in 0..59");
    }
    unsigned int h = GetHours();
    unsigned int s = GetSeconds();
    t = ComponentsToSeconds(h, minutes, s);
}

//Needed to display number of seconds
void TimeCode::SetSeconds(unsigned int seconds) {
    if (seconds >= 60) {
        throw invalid_argument("seconds must be in 0..59");
    }
    unsigned int h = GetHours();
    unsigned int m = GetMinutes();
    t = ComponentsToSeconds(h, m, seconds);
}

//If the time needs to be reset to 0
void TimeCode::reset(){
    t = 0;
}

//Needs to derive the number of hours from t (how the program sees the time)
unsigned int TimeCode::GetHours() const {
    return static_cast<unsigned int>(t / 3600);
}

//Needs to derive the number of minutes from t (how the program sees the time)
unsigned int TimeCode::GetMinutes() const {
    return static_cast<unsigned int>((t % 3600) / 60);
}

//Needs to derive the number of seconds from t (how the program sees the time)
unsigned int TimeCode::GetSeconds() const {
    return static_cast<unsigned int>(t % 60);
}

//Calls the componets to be used
void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) {
    hr  = GetHours();
    min = GetMinutes();
    sec = GetSeconds();
}

//Formats the output for the user
string TimeCode::ToString() const {
    ostringstream oss;
    oss << GetHours() << ':' << GetMinutes() << ':' << GetSeconds();
    return oss.str();
}

//Checks for addition as per the assignment 
TimeCode TimeCode::operator+(const TimeCode& other) const {
    TimeCode out;       
    out.t = this->t + other.t;
    return out;
}

//checks for subtraction as per the assigment
TimeCode TimeCode::operator-(const TimeCode& other) const {
    if (this->t < other.t) {
        throw invalid_argument("Negatives not allowed");
    }
    TimeCode out;
    out.t = this->t - other.t;
    return out;
}

TimeCode TimeCode::operator*(double a) const {
    if (a < 0.0) {
        throw invalid_argument("Must be non-negative");
    }
    long double product = static_cast<long double>(t) * static_cast<long double>(a);
    unsigned long long sec = static_cast<unsigned long long>(product);
    TimeCode out;
    out.t = sec;
    return out;
}

TimeCode TimeCode::operator/(double a) const {
    if (a <= 0) {
        throw invalid_argument("Divisor must be > 0");
    }
    long double divisor = static_cast<long double>(t) / static_cast<long double>(a);
    unsigned long long sec = static_cast<unsigned long long>(divisor);
    TimeCode out;
    out.t = sec;
    return out;
}


bool TimeCode::operator==(const TimeCode& other) const { return t == other.t; }
bool TimeCode::operator!=(const TimeCode& other) const { return t != other.t; }
bool TimeCode::operator< (const TimeCode& other) const { return t <  other.t; }
bool TimeCode::operator<=(const TimeCode& other) const { return t <= other.t; }
bool TimeCode::operator> (const TimeCode& other) const { return t >  other.t; }
bool TimeCode::operator>=(const TimeCode& other) const { return t >= other.t; }