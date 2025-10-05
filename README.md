# CS3_HW3

Homework 3 Part 2

NasaLaunchAnalysis 

Goal: Output the average launch time of all the NASA Launch times.

How The Program works:
The file intakes the the csv file given to us with a list of all the NASA space launch dates along with some other information.
The file then gets read line by line and parsed to specifically extract just the time. After we have all of the times we can 
simply just find the average. 


PaintDryTimer

Goal: Keep track of the time it takes for paint to dry on random things.

How the Program works:

Using our previously built TimeCode.h file, we can subtract the end time - the start time, by using the time(0) to keep track.
So given a TimeCode we are able to find the total time needed to dry.