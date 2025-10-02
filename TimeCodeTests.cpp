#include <iostream>
#include <assert.h>
#include <stdexcept>
using namespace std;
#include "TimeCode.h"

//Has to be able to convert time to t in seconds
void TestComponentsToSeconds(){
	cout << "Testing ComponentsToSeconds" << endl;
	
	// Random but "safe" inputs
	long long unsigned int t = TimeCode::ComponentsToSeconds(3, 17, 42);
	assert(t == 11862);
	
	// More tests go here!

	assert(TimeCode::ComponentsToSeconds(0, 0, 0) == 0);
	assert(TimeCode::ComponentsToSeconds(0, 2, 5) == 125);
	assert(TimeCode::ComponentsToSeconds(1, 5, 10) == 3910);
	assert(TimeCode::ComponentsToSeconds(0, 59, 59) == 3599);
	assert(TimeCode::ComponentsToSeconds(0, 0, 5827589378593791234) == 5827589378593791234);
	assert(TimeCode::ComponentsToSeconds(2, 62, 34) == 10954);
	assert(TimeCode::ComponentsToSeconds(10, 24, 2) == 37442);

	cout << "PASSED!" << endl << endl;
}

//Default constructor must work
void TestDefaultConstructor(){
	cout << "Testing Default Constructor" << endl;
	TimeCode tc;
	
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	cout << "PASSED!" << endl << endl;

}

//Constructor has to output the correct values int the right places
void TestComponentConstructor(){
	cout << "Testing Component Constructor" << endl;
	TimeCode tc = TimeCode(0, 0, 0);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");

	// more tests go here!

	TimeCode tc1 = TimeCode(1, 54, 24);
	TimeCode tc2 = TimeCode(94, 59, 32);

	assert(tc1.ToString() == "1:54:24");
	assert(tc2.ToString() == "94:59:32");
		
	
	// Roll-over inputs
	TimeCode tc3 = TimeCode(3, 71, 3801);
	//cout << "tc3: " << tc3.ToString() << endl;
	assert(tc3.ToString() == "5:14:21");
	
	// More tests go here!
	TimeCode tc4 = TimeCode(0, 0, 3600);
	TimeCode tc5 = TimeCode(2, 80, 15);
	TimeCode tc6 = TimeCode(60, 60, 60);
	TimeCode tc7 = TimeCode(12, 40, 100);

	assert(tc4.ToString() == "1:0:0");
	assert(tc5.ToString() == "3:20:15");
	assert(tc6.ToString() == "61:1:0");
	assert(tc7.ToString() == "12:41:40");

	
	cout << "PASSED!" << endl << endl;
}

//hours, minutes, and seconds must be called correctly
void TestGetComponents(){
	cout << "Testing GetComponents" << endl;
	
	unsigned int h;
	unsigned int m;
	unsigned int s;
	
	// Regular values
	TimeCode tc = TimeCode(5, 2, 18);
	tc.GetComponents(h, m, s);
	assert(h == 5 && m == 2 && s == 18);
	
	// More tests go here!
	TimeCode tc1 = TimeCode(0, 0, 0);
	TimeCode tc2 = TimeCode(12, 53, 26);
	TimeCode tc3 = TimeCode(32, 3, 43);
	TimeCode tc4 = TimeCode(3, 70, 32);
	TimeCode tc5 = TimeCode(4, 56, 99);

	tc1.GetComponents(h, m, s);
	assert(h == 0 && m == 0 && s == 0);
	tc2.GetComponents(h, m, s);
	assert(h == 12 && m == 53 && s == 26);
	tc3.GetComponents(h, m, s);
	assert(h == 32 && m == 3 && s == 43);
	tc4.GetComponents(h, m, s);
	assert(h == 4 && m == 10 && s == 32);
	tc5.GetComponents(h, m, s);
	assert(h == 4 && m == 57 && s == 39);
	

	
	cout << "PASSED!" << endl << endl;
}

//Times can be subtracted given the assignment details
void TestSubtract(){
	cout << "Testing Subtract" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 - tc2;
	assert(tc3.ToString() == "0:10:0");
	
	
	TimeCode tc4 = TimeCode(1, 15, 45);
	try{
		TimeCode tc5 = tc1 - tc4;
		cout << "tc5: " << tc5.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just leave this empty
		// and keep doing more tests
	}

    TimeCode a(2, 0, 0), b(1, 59, 59);
    TimeCode c = a - b;                 
    assert(c.ToString() == "0:0:1");

    TimeCode d(3, 20, 15), e(3, 20, 15);
    TimeCode z = d - e;
    assert(z.ToString() == "0:0:0");

    try {
        (TimeCode(0,10,0) - TimeCode(0,10,1));
        assert(false);
    } catch (const invalid_argument&) {}
	
	cout << "PASSED!" << endl << endl;
}

//Tests minutes being set
void TestSetMinutes(){

	cout << "Testing SetMinutes" << endl;
	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetMinutes(15); 
	assert(tc.ToString() == "8:15:9");

	try
	{
		tc.SetMinutes(80); 
		assert(false);
	}
	catch (const invalid_argument &e)
	{

	}

	assert(tc.ToString() == "8:15:9");

	cout << "PASSED!" << endl << endl;
}

//Tests hours being set
void TestSetHours() {
    cout << "Testing SetHours" << endl;

    TimeCode tc(1, 2, 3);
    tc.SetHours(10);
    assert(tc.GetHours() == 10);
    assert(tc.GetMinutes() == 2);
    assert(tc.GetSeconds() == 3);

    //Large Hour
    tc.SetHours(123);
    assert(tc.GetHours() == 123);
    assert(tc.GetMinutes() == 2);
    assert(tc.GetSeconds() == 3);

    cout << "PASSED!" << endl << endl;
}

//Tests the seconds
void TestSetSeconds() {
    cout << "Testing SetSeconds" << endl;

    TimeCode tc(4, 5, 6);

    //Valid
    tc.SetSeconds(0);
    assert(tc.GetHours() == 4);
    assert(tc.GetMinutes() == 5);
    assert(tc.GetSeconds() == 0);

    tc.SetSeconds(59);
    assert(tc.GetHours() == 4);
    assert(tc.GetMinutes() == 5);
    assert(tc.GetSeconds() == 59);

    //Invalid 
    bool threw = false;
    try {
        tc.SetSeconds(60);
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    assert(threw && "SetSeconds(60) should throw invalid_argument");

    threw = false;

    cout << "PASSED: SetSeconds" << endl << endl;
}

// Many More Tests...

//Ensures time rolls over in a realistic manner
void TestAddRollover() {
    cout << "Testing Add (Rollover)" << endl;

    //Rollover seconds + minutes
    TimeCode d(1, 15, 55), e(0, 1, 25);
    TimeCode f = d + e;                
    assert(f.ToString() == "1:17:20");

    //Boundary
    TimeCode g(0, 59, 59), h(0, 0, 1);
    TimeCode i = g + h;                 
    assert(i.ToString() == "1:0:0");

    //Lare Hours Int
    TimeCode j(1000, 0, 0), k(24, 0, 0);
    TimeCode m = j + k;
    assert(m.ToString() == "1024:0:0");

    cout << "PASSED!" << endl << endl;
}

//Ensures that boundary inputs work correctly
void TestSettersBoundaries() {
    cout << "Testing Setters" << endl;

    TimeCode tc(1, 2, 3);
    tc.SetMinutes(59);                 
    assert(tc.ToString() == "1:59:3");

    tc.SetSeconds(59);                
    assert(tc.ToString() == "1:59:59");

    //Minutes Range Tests
    try { tc.SetMinutes(60); assert(false); }
    catch (const invalid_argument&) {}

    //Seconds Range Tests
    try { tc.SetSeconds(60); assert(false); }
    catch (const invalid_argument&) {}

    //Large Hours int
    tc.SetHours(123456);
    assert(tc.GetHours() == 123456);

    cout << "PASSED!" << endl << endl;
}

//Checks the multiplication and division
void TestScaleMultiplyDivide() {
    cout << "Testing Multiply/Divide" << endl;

    TimeCode a(1,0,0);                 
    TimeCode b = a * 1.5;              
    assert(b.ToString() == "1:30:0");

    TimeCode c = a * 2.6;              
    assert(c.ToString() == "2:36:0");

    TimeCode d = TimeCode(2,0,0) / 3;   
    assert(d.ToString() == "0:40:0");

    TimeCode e = TimeCode(1,0,0) / 4;  
    assert(e.ToString() == "0:15:0");

	//Invalid Cases
    try { (a * -0.1); assert(false); }
    catch (const invalid_argument&)  {}

    try { (a / 0.0); assert(false); }
    catch (const invalid_argument&) {}

    try { (a / -2.0); assert(false); }
    catch (const invalid_argument&) {}

    cout << "PASSED!" << endl << endl;
}

//Ensure all boolean logic is up to standard
void TestComparisons() {
    cout << "Testing Comparisons" << endl;

    TimeCode a(1,0,0), b(0,60,0);    
    assert(a == b);
    assert(!(a != b));
    assert(!(a < b));
    assert(a <= b);
    assert(!(a > b));
    assert(a >= b);

    TimeCode c(1,0,1);
    assert(a < c);
    assert(c > a);

    cout << "PASSED!" << endl << endl;
}

//Need to check that the reset and GetTimeCodeAsSeconds work accordingly
void TestResetAndSeconds() {
    cout << "Testing reset and GetTimeCodeAsSeconds" << endl;

    //Checks that t is getting the correct number of seconds
    TimeCode a(1,2,3);
    auto secs = TimeCode::ComponentsToSeconds(1,2,3);
    assert(a.GetTimeCodeAsSeconds() == secs);

    //Checks that t value can be reset
    a.reset();
    assert(a.ToString() == "0:0:0");
    assert(a.GetTimeCodeAsSeconds() == 0ULL);

    cout << "PASSED!" << endl << endl;
}


void TestCopyConstructor(){
	cout << "Testing Copy Constructor" << endl;
	
	// test 1
	TimeCode tc = TimeCode(3, 17, 42);
	TimeCode tc2 = TimeCode(tc);
	assert(tc2.ToString() == "3:17:42");
	
	// test 2
	TimeCode tc3 = TimeCode(3, 71, 3801);
	TimeCode tc4 = TimeCode(tc3);
	assert(tc3.ToString() == "5:14:21");
	assert(tc4.ToString() == "5:14:21");
	
	// test 3
	tc3.SetHours(8);
	assert(tc3.ToString() == "8:14:21");
	assert(tc4.ToString() == "5:14:21");
	
	
	cout << "PASSED!" << endl << endl;
}


void TestMultiply(){
	cout << "Testing Multiply" << endl;
	
	// test 1
	TimeCode tc1 = TimeCode(0, 1, 0);
	TimeCode tc2 = tc1 * 2;
	assert(tc2.ToString() == "0:2:0");
	
	// test 2
	TimeCode tc3 = TimeCode(3, 5, 17);
	TimeCode tc4 = tc3 * 5.5;
	//cout << "tc4: " << tc4.ToString() << endl;
	assert(tc4.ToString() == "16:59:3");
	
	// test 3
	TimeCode tc5 = TimeCode(0, 5, 0);
	TimeCode tc6 = tc5 * 2.5;
	assert(tc6.ToString() == "0:12:30");

	// test 4
	tc6 = tc5 * 2.74;
	assert(tc6.ToString() == "0:13:42");
	
	// test 5
	TimeCode tc7 = TimeCode(0, 5, 0);
	TimeCode tc8 = tc7 * 0.5;
	assert(tc8.ToString() == "0:2:30");

	// test 6, negative number test
	try{
		TimeCode tc10 = tc7 * -2;
		cout << "tc10:" << tc10.ToString() << endl;
		assert(false);
	} catch (const invalid_argument& e){
		
	}
	
	
	// test 7, multiply by 0
	TimeCode tc12 = tc7 * 0;
	assert(tc12.ToString() == "0:0:0");
	
	cout << "PASSED!" << endl << endl;
}
	
int main(){
	
	TestComponentsToSeconds();
	TestDefaultConstructor();
	TestComponentConstructor();
	TestGetComponents();
	TestAddRollover();
	TestSettersBoundaries();
	TestScaleMultiplyDivide();
	TestComparisons();
	TestResetAndSeconds();
	TestSetMinutes();
	TestSetHours();
	TestSetSeconds();
	TestMultiply();
	TestCopyConstructor();


	// Many othere test functions...
	
	cout << "PASSED ALL TESTS!!!" << endl;
	return 0;
}