/*  Object-oriented Programming in C++, Professor Doug Ferguson
 *  JHU EP, Summer 2014 *
 *  20140716, Mike Ricci
 *  HW6: Elevator Simulation
 *	 main.cpp *
 *  SUMMARY:  This program uses the classes Passenger, Car, Floor, and Building to
 *  conduct a discrete simulation of elevators in a building.
 *
 *  INPUT: A CSV file is provided which defines passengers by the time they arrive
 *  at their origin floor, their origin floor, and their destination floor.
 *
 *  OUTPUT: The program collects wait times and travel times from the passengers as
 *  they are dropped off at their destination floors.  After completion of the simulation,
 *  the wait times and travel times are averaged.  The simulation is ran a second time,
 *  using an interfloor speed of the cars of 5 seconds (half of the original 10).
 *  new average wait and travel times are calculated and the percent reduction
 *  achieved by the improved speed is displayed.
 *
 *  LIMITATIONS: Floor 0 is the start floor but that floor is never used by passengers;
 *  There were some problems that I was unable to resolve and I resorted to "band
 *  aid" fixes to prevent fatal errors; 
 */

#include <iostream>
#include "Building.h"

int main()
{
	//Construct Building singleton
	// filepath: /home/reechee/Documents/Cpp/HW6/HW6-Elevators.csv
	Building *BuildingPtr;
	BuildingPtr = Building::Instance("/home/reechee/Documents/Cpp/HW6/HW6-Elevators.csv",
	    						            4,    // number of cars
	     						            5,   // inter-floor speed of cars
	       						         100); // number of floors (floor 1 = ground)
	
	//run simulation: loop for each second of simulation
	while(BuildingPtr->getTime() < BuildingPtr->getFinalPassengerTime() + 20000) // FIND A BETTER WAY TO EXTEND SIMULATION TO COMPLETION
	{
		//create new passenger(s) (if any)
		BuildingPtr->makePassenger(BuildingPtr->getTime());

		//update car states
		BuildingPtr->updateCarStates();

		//load and/or unload passengers
		BuildingPtr->transactPassengers();

		//increment clock
		BuildingPtr->incrementClock();
	}

	//print average wait and travel times
	BuildingPtr->calcWaitTime();
	BuildingPtr->calcTravelTime();
	int firstTravel = BuildingPtr->getAvgTravel();
	int firstWait = BuildingPtr->getAvgWait();
	std::cout << "Average Wait Time: " << firstWait << std::endl;
	std::cout << "Average Travel Time: " << firstTravel << std::endl; 

	//rerun simulation with a 5 second speed
	BuildingPtr = Building::Instance("/home/reechee/Documents/Cpp/HW6/HW6-Elevators.csv",
    						               4,    // number of cars
     						               5,   // inter-floor speed of cars (improved)
       						            100); // number of floors (floor 1 = ground)

	//rerun simulation: loop for each second of simulation
   // BETTER WAY TO EXTEND SIMULATION TO COMPLETION?
	while(BuildingPtr->getTime() < BuildingPtr->getFinalPassengerTime() + 20000)
	{
		//create new passenger(s) (if any)
		BuildingPtr->makePassenger(BuildingPtr->getTime());

		//update car states
		BuildingPtr->updateCarStates();
		
		//load and/or unload passengers
		BuildingPtr->transactPassengers();

		//increment clock
		BuildingPtr->incrementClock();
	}

	//print new average wait and travel times, with percent changes from first simulation
	BuildingPtr->calcWaitTime();
	BuildingPtr->calcTravelTime();
	int newTravel = BuildingPtr->getAvgTravel();
	int newWait = BuildingPtr->getAvgWait();
	std::cout << "New Average Wait Time: " << newWait << std::endl;
	std::cout << "(" << ((firstWait - newWait)/firstWait)*100 << "% reduction)" << std::endl;
	std::cout << "New Average Travel Time: " << newTravel << std::endl;
	std::cout << "(" << ((firstTravel - newTravel)/firstTravel)*100 << "% reduction)" << std::endl;
	
	return 0;
}

