#include <ctime> // for time(0)
#include <iostream> // for cin and cout
#include <cmath> // for M_PI and others
#include <vector> // for vectors (duh)
#include <cstdlib> // for random
#include <cassert> // for assert in the tests() function
#include "TimeCode.h" // for timecode's (duh)

using namespace std;

struct DryingSnapShot {
	// This is a struct, it's like an object
	// that doesn't have any methods.
	// You can read more about them in the ZyBook
	// just search for "struct"
	string name;
	time_t startTime;
	TimeCode *timeToDry;
};

//Calls the timecome in seconds to be used throughout the code
static unsigned long long timecode_to_seconds(const TimeCode &tc) {
    return tc.GetTimeCodeAsSeconds();
}

//finds the time to dry
long long int get_time_remaining(DryingSnapShot dss){
    if (dss.timeToDry == nullptr) return 0;
    unsigned long long end = timecode_to_seconds(*dss.timeToDry);
    time_t now = time(0);
    long long int start = static_cast<long long int>(now - dss.startTime);
    return static_cast<long long int>(end) - start;
}

//Returns a readable string for the user
string drying_snap_shot_to_string(DryingSnapShot dss){
    long long int remainingTime = get_time_remaining(dss);
    if (remainingTime <= 0) {
        return dss.name + ": done";
    } else {
        TimeCode tmp(0, 0, remainingTime); 
        return dss.name + ": " + tmp.ToString() + " remaining";
    }
}

//needs to compute the surface area
double get_sphere_sa(double rad){
	return 4.0 * M_PI * (rad * rad);
}

//Connects the surface area to time
TimeCode* compute_time_code(double surfaceArea) {
    long long secs = static_cast<long long>(floor(surfaceArea));
    if (secs < 0) secs = 0;
    return new TimeCode(0, 0, secs); 
}



void tests(){
	// get_time_remaining
	DryingSnapShot dss;
	dss.startTime = time(0);
	TimeCode tc = TimeCode(0, 0, 7);
	dss.timeToDry = &tc;
	long long int ans = get_time_remaining(dss);
	assert(ans > 6 && ans < 8);
	// add more tests here


	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);


	//Brackets allow me to not have to worry about variable conflict
    {
        DryingSnapShot dss3;
        dss3.startTime = time(0);
        TimeCode tc3 = TimeCode(1, 0, 0);
        dss3.timeToDry = &tc3;
        long long int ans3 = get_time_remaining(dss3);
        assert(ans3 > 3597 && ans3 < 3601);
    }

    {
        DryingSnapShot dss4;
        dss4.startTime = time(0) - 10;   
        TimeCode tc4 = TimeCode(0, 0, 5);
        dss4.timeToDry = &tc4;
        long long int ans4 = get_time_remaining(dss4);
        assert(ans4 <= 0);
        string s4 = drying_snap_shot_to_string(dss4);
        assert(s4.find("done") != string::npos);
    }


    {
        DryingSnapShot dss5;
        dss5.startTime = time(0);
        TimeCode tc5 = TimeCode(0, 0, 1); 
        dss5.timeToDry = &tc5;
        long long int ans5 = get_time_remaining(dss5);
        assert(ans5 > 0 && ans5 < 2);
    }

    {
        double sa0 = get_sphere_sa(0.0);
        assert(sa0 == 0.0);
    }

    {
        double sa1 = get_sphere_sa(1.0);
        const double expected1 = 4.0 * M_PI * 1.0 * 1.0;
        assert(expected1 - 1e-9 < sa1 && sa1 < expected1 + 1e-9);
    }

    {
        double sa2 = get_sphere_sa(2.0);
        assert(50.2654 < sa2 && sa2 < 50.2655);
    }

    {
        double sa05 = get_sphere_sa(0.5);
        const double expected05 = 4.0 * M_PI * 0.5 * 0.5;
        assert(expected05 - 1e-9 < sa05 && sa05 < expected05 + 1e-9);
    }


	cout << "ALL TESTS PASSED!" << endl;

}


int main(){
	// replace with your code
	tests(); // run unit tests
   

}