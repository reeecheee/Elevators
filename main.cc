/*  Object-oriented Programming in C++, Professor Doug Ferguson
 *  JHU EP, Summer 2014 *
 *  20140716, Mike Ricci
 *  HW6: Elevator Simulation
 *	 main.cpp *
 *  SUMMARY: 
 *
 *  INPUT: 
 *
 *  OUTPUT: 
 *
 *  LIMITATIONS: Floor numbering scheme
 */

#include <iostream>
#include "Building.h"

int main()
{
	//Construct Building singleton
	// filepath: /home/reechee/Documents/Cpp/HW6/HW6-Elevators.csv
	Building *BuildingPtr;
	BuildingPtr = Building::Instance("/home/reechee/Documents/Cpp/HW6/test.csv",
	    						            4,    // number of cars
	     						            10,   // inter-floor speed of cars
	       						         100); // number of floors (floor 1 = ground)

	//loop for each second of simulation
	while(BuildingPtr->getTime() < BuildingPtr->getFinalPassengerTime() + 200) // FIND A BETTER WAY TO EXTEND SIMULATION TO COMPLETION
	{
		//create new passenger(s) (if any)
		BuildingPtr->makePassenger(BuildingPtr->getTime());
		
		//update car states
		//BuildingPtr->updateCarStates();

		//load and/or unload passengers
		//BuildingPtr->transactPassengers();

		//increment clock
		BuildingPtr->incrementClock();

		std::cout << "Time: " << BuildingPtr->getTime() << std::endl;
	}

	//print average wait and travel times
/*	BuildingPtr->calcWaitTime();
	BuildingPtr->calcTravelTime();
	int firstTravel = BuildingPtr->getAvgTravel();
	int firstWait = BuildingPtr->getAvgWait();
	std::cout << "Average Wait Time: " << firstWait << std::endl;
	std::cout << "Average Travel Time: " << firstTravel << std::endl;*/

	//rerun simulation with a 5 second speed
/*	BuildingPtr = Building::Instance("/home/reechee/Documents/Cpp/HW6/HW6-Elevators.csv",
    						               4,    // number of cars
     						               5,   // inter-floor speed of cars (improved)
       						            100); // number of floors (floor 1 = ground)*/

	//print new average wait and travel times, with percent changes from first simulation
/*	BuildingPtr->calcWaitTime();
	BuildingPtr->calcTravelTime();
	int newTravel = BuildingPtr->getAvgTravel();
	int newWait = BuildingPtr->getAvgWait();
	std::cout << "New Average Wait Time: " << firstWait << std::endl;
	std::cout << "(" << ((firstWait - newWait)/firstWait)*100 << "% reduction)" << std::endl;
	std::cout << "New Average Travel Time: " << firstTravel << std::endl;
	std::cout << "(" << ((firstTravel - newTravel)/firstTravel)*100 << "% reduction)" << std::endl;*/
	
	return 0;
}

