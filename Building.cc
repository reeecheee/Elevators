/*
 *	 Building.cc
 * 
 *  Building class source file: 
 * 
 *  Author: Mike Ricci
 *  Date: 20140716
 */

#include <queue>
#include <string>
#include <vector>
#include "Passenger.h"
#include "Floor.h"
#include "Car.h"
#include "Building.h"

//CONSTRUCTOR: SINGLETON DESIGN PATTERN

// Global static pointer used to ensure a single instance of the class.
Building* Building::instance = nullptr;

//The function Instance() is called to create an instance of the Building class.
//The constructor below is private and can only be called through this function.
Building* Building::Instance(std::string filepath, int numCars, int speed, int numFloors)
{
	if(!instance)
	{
		instance = new Building(filepath, numCars, speed, numFloors);
	}
	return instance;
}

Building::Building(std::string filepath, int numCars, int speed, int numFloors)
{
	//parse CSV
	std::string line;
	std::ifstream CSV (filepath);
	if (CSV.is_open())
	{
		getline(CSV,line); //skip first line (headings)
		
		while ( getline (CSV,line) )
		{
			//tokenize line
			std::array<int,3> toks;
			std::stringstream ss;
			int tokIndex = 0;
			
			for(char& c : line) // iterate through line, char by char
			{
				if(c != ',')
				{
					ss << c;
				}
				else
				{
					if(tokIndex < 3) // don't run off end of toks array
					{
						// convert stream to int assign to tok[tokIndex]
						toks[tokIndex] = atoi(ss.str().c_str()); 
						//std::cout << "toks[" << tokIndex << "]: " << toks[tokIndex] << std::endl; //REMOVE AFTER TESTING
						++tokIndex; // increment token index						
						ss.str(std::string()); // clear the stream
					}				
				}
			}

			if(tokIndex < 3)
			{
				// convert stream to int assign to tok[tokIndex]
				toks[tokIndex] = atoi(ss.str().c_str()); 
				//std::cout << "toks[" << tokIndex << "]: " << toks[tokIndex] << std::endl; //REMOVE AFTER TESTING
				++tokIndex; // increment token index						
				ss.str(std::string()); // clear the stream
			}
			//std::cout << line << std::endl; //REMOVE AFTER TESTING
			
			//add tokens to parsed vector of arrays
			this->parsed.push_back(toks);
		}
		CSV.close();
	}
	else 
	{
		std::cout << "Unable to open file";
	}

	//populate cars vector
	for(int i = 0; i < numCars; ++i)
	{
		this->cars.push_back(Car(speed));
	}

	//populate floors vector
	for(int i = 0; i < numFloors; ++i)
	{
		this->floors.push_back(Floor());
	}
}

//VIRTUAL DESCTRUCTOR
Building::~Building()
{

}

//MEMBER FUNCTIONS

//The function addTravelTime() adds a passenger's travel time to the Building's
//travelTimes vector.  Travel time = (drop off time) - (pick up time)
void Building::addTravelTime(int travelTime)
{
	this->travelTimes.push_back(travelTime);
}

//The function addWaitTime() adds a passenger's wait time to the Building's
//waitTimes vector.  Wait time = (pick up time) - (start time)
void Building::addWaitTime(int waitTime)
{
	this->waitTimes.push_back(waitTime);
}

//The function calcTravelTime() calculates the average of the times stored in the
//Building's travelTimes vector and stores it in avgTravelTime.
void Building::calcTravelTime()
{
	int sum = 0;
	int count = 0;
	int avg;

	for(int i : travelTimes)
	{
		sum += i;
		++count;
	}

	avg = sum / count;
	this->avgTravelTime = avg;
}

//The function calcWaitTime() calculates the average of the times stored in the
//Building's waitTimes vector and stores it in avgWaitTime.
void Building::calcWaitTime()
{
	int sum = 0;
	int count = 0;
	int avg;

	for(int i : waitTimes)
	{
		sum += i;
		++count;
	}

	avg = sum / count;
	this->avgWaitTime = avg;
}

//The function getFinalPassengerTime() returns the time that the final passenger
//will be created.
int Building::getFinalPassengerTime() const
{
	return this->parsed.back().at(0);
}

//The function getNextPassOnFlr() returns a pointer to the next passenger in the
//queue on the passed floor.
Passenger* Building::getNextPassOnFlr(int floor) const
{
	return this->floors[floor].nextPass();
}

//The function getNextFloorCall()
int Building::getNextFlrCall() const
{
	return this->passengers.front()->getFloorEnd();
}

//The function getTime() returns the simulation time in seconds
int Building::getTime() const
{
	return this->time;
}

//The function incrementClock() steps the Building's clock ahead by 1 second.
void Building::incrementClock()
{
	this->time = time + 1;
}

//The function makePassenger() searches through the parsed CSV data to see if 1 or
//more passengers are appearing at this time in the simulation.  If any exist,
//they are created in the queue of passengers and a pointer is created for them
//in the appropriate Floor object in the floors vector.
void Building::makePassenger(int time)
{
	bool cont = true; //continue to look for new passengers while true
	
	for(auto it : parsed) // iterate through parsed data
	{
		while(cont == true)
		{
			if(it[0] == time)
			{
				//create new passengers
				Passenger* passengerPtr = new Passenger(it[0], it[1], it[2]);
				this->passengers.push(passengerPtr);
				this->floors[it[1]].addPass(passengerPtr);
			}
			else if(it[0] > time)
			{
				cont = false;
			}
		}
	}
}

//The function rmNextPassFromFlr() pops the next passenger in the passed Floor's
//queue.
void Building::rmNextPassFromFlr(int floor)
{
	this->floors[floor].rmPass();
}

//The function updateCarStates() calls Car::updateState() on each Car object
//in the Building's cars vector.
void Building::updateCarStates()
{
	for(auto car : cars)
	{
		car.updateState();
	}
}

//REMOVE AFTER TESTING
int Building::sizeOfCars() const
{
	return this->cars.size();
}

//REMOVE AFTER TESTING
int Building::sizeOfFloors() const
{
	return this->floors.size();
}



