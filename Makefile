all:
	g++ -std=c++17 -Wall TimeCode.cpp TimeCodeTests.cpp -o tct


run:
	./tct

try: all run