all:
	g++ -std=c++17 -Wall TimeCode.cpp TimeCodeTests.cpp -o tct
	g++ -std=c++17 -Wall TimeCode.cpp NasaLaunchAnalysis.cpp -o nasa

run:
	./tct

try: all run
