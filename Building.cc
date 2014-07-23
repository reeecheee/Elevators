/*
 *	 Building.cc
 * 
 *  Building class source file: 
 * 
 *  Author: Mike Ricci
 *  Date: 20140716
 */

#include <algorithm> // std::find()
#include <deque>
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
						++tokIndex; // increment token index						
						ss.str(std::string()); // clear the stream
					}				
				}
			}

			if(tokIndex < 3)
			{
				// convert stream to int assign to tok[tokIndex]
				toks[tokIndex] = atoi(ss.str().c_str()); 
				++tokIndex; // increment token index						
				ss.str(std::string()); // clear the stream
			}
			
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
		this->cars.push_back(Car(i, speed));
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
	std::cout << "travel: " << travelTime << std::endl; //REMOVE AFTER TESTING
	this->travelTimes.push_back(travelTime);
}

//The function addWaitTime() adds a passenger's wait time to the Building's
//waitTimes vector.  Wait time = (pick up time) - (start time)
void Building::addWaitTime(int waitTime)
{
	std::cout << "wait: " << waitTime << std::endl; //REMOVE AFTER TESTING
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

	std::vector<int>::iterator iter = this->waitTimes.begin();
	for(iter; iter != this->waitTimes.end(); ++iter)
	{
		sum += *iter;
		++count;
	}
/*	for(int i : waitTimes)
	{
		sum += i;
		++count;
	}*/

	std::cout << "sum: " << sum << std::endl;
	std::cout << "count: " << count << std::endl;
	//std::cout << "avg: " << avg << std::endl;
	
	avg = sum / count;
	this->avgWaitTime = avg;
}

//The function destroyPassenger() adds the passed passenger's wait and travel times
//to the Building's listing of wait and travel times, then deletes the passenger.
void Building::destroyPassenger(Passenger* passenger)
{
	//bandaid fix to prevent segfaults from deleting nonexistent passengers
	std::cout << "passed start time: " << passenger->getTimeStart() << std::endl; // REMOVE AFTER TESTING
	
	for(int i = 0; i < this->passengers.size(); ++i)
	{
		//std::cout << "start time in building deque: " << this->passengers.at(i)->getTimeStart() << std::endl; //REMOVE AFTER TESTING
			
		int tempWait = passenger->getTimePickUp() - passenger->getTimeStart();
		int tempTravel = passenger->getTimeDropOff() - passenger->getTimePickUp();

		std::cout << "tempWait: " << tempWait << std::endl; //REMOVE AFTER TESTING
		std::cout << "tempTravel: " << tempTravel << std::endl; //REMOVE AFTER TESTING
		this->waitTimes.push_back(tempWait);
		this->travelTimes.push_back(tempTravel);
		
		if(this->passengers.at(i) == passenger)
		{
			delete passenger;
		}
	}
}

//The function getAvgTravel() returns the average travel time.
int Building::getAvgTravel() const
{
	return this->avgTravelTime;
}

//The function getAvgWait() returns the average wait time.
int Building::getAvgWait() const
{
	return this->avgWaitTime;
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

//The function getNextFlrCall()
int Building::getNextFlrCall() const
{
	if(this->passengers.size() != 0)
	{
		return this->passengers.front()->getFloorStart();
	}
	else
	{
		return -1;
	}
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
	for(auto it : parsed) // iterate through parsed data
	{
		if(it[0] == time)
		{
			//create new passenger
			Passenger* passengerPtr = new Passenger(it[0], it[1], it[2]);
			this->passengers.push_back(passengerPtr);
			this->floors[it[1]].addPass(passengerPtr);
		}
	} // end for loop
} // end makePassenger()

//The function rmNextPassFromFlr() pops the next passenger in the passed Floor's
//queue.
void Building::rmNextPassFromFlr(int floor)
{
	this->floors[floor].rmPass();
}

//The function transactPassengers() unloads passengers from cars if they've reached
//their destination, and loads passengers into cars if a car with unused capacity
//has arrived at their floor.
void Building::transactPassengers()
{
	std::vector<Car>::iterator carIter = this->cars.begin();
	for(carIter; carIter != this->cars.end(); ++carIter) // iterate through all cars
	{
		if(carIter->getState() == Car::STOPPED)
		{
			//unload passengers from car and note who left
			std::vector<Passenger*> complete = carIter->rmPassenger(carIter->getFloor());

			if(complete.size() != 0) // passengers were unloaded
			{
				std::vector<Passenger*>::iterator passIter = complete.begin();
				for(passIter; passIter != complete.end(); ++passIter) //iterate through unloaded passengers
				{			
					(*passIter)->setTimeDropoff(this->getTime());
					//tabulate wait/travel times and delete passenger
					this->destroyPassenger(*passIter);
				}
			}
			
			//determine if passengers are on the floor; load 'em up till the car's full
			while(this->floors.at(carIter->getFloor()).nextPass() != nullptr &&
			      carIter->getNumPassAboard() < 8)
			{
				this->floors.at(carIter->getFloor()).nextPass()->setTimePickUp(this->getTime());
				carIter->addPassenger(this->floors.at(carIter->getFloor()).nextPass());
				
				//remove passenger from building deque
				std::deque<Passenger*>::iterator passIter = this->passengers.begin();
				while(passIter != this->passengers.end())
				{
					if(*passIter == this->floors.at(carIter->getFloor()).nextPass())
					{
						this->passengers.erase(passIter);
					}
					else
					{
						++passIter; //iterate passIter if it wasn't iterated by erase()
					}
				}

				//remove passenger from floor's queue
				this->floors.at(carIter->getFloor()).rmPass();
			}
		} // end if on stopped cars
	} // end iteration through all cars
} // end transactPassengers() function

//The function passOnNext() returns true if there is a passenger on the next floor
//that the passed car is approaching.
bool Building::passOnNext(int car) const
{
	int nextFloor;
	
	if(this->cars.at(car).getState() == Car::MOVING_UP &&  //car is MOVING_UP
	   this->cars.at(car).getFloor()+1 <= 99) // car isn't at top floor
	{
		nextFloor = this->cars.at(car).getFloor() + 1; //next floor is above

		if(this->floors.at(nextFloor).nextPass() == nullptr) //next floor is empty
		{
			return false;
		}
		else // next floor has passengers waiting
		{
			return true;
		}
	}
	else if(this->cars.at(car).getState() == Car::MOVING_DOWN &&  // car is MOVING_DOWN
	        this->cars.at(car).getFloor()-1 >= 0) // car isn't at bottom floor
	{
		nextFloor = this->cars.at(car).getFloor() - 1; // next floor is below

		if(this->floors.at(nextFloor).nextPass() == nullptr) //next floor is empty
		{
			return false;
		}
		else // next floor has passengers waiting
		{
			return true;
		}
	}
	else // car is STOPPED or STOPPING, do nothing
	{
		return false;
	}
} // end function passOnNext()

//The function updateCarStates() calls Car::updateState() on each Car object
//in the Building's cars vector.
void Building::updateCarStates()
{
	int nextFlrCall = this->getNextFlrCall();
	
	std::vector<Car>::iterator iter = this->cars.begin();
	for(iter; iter != this->cars.end(); ++iter)
	{
		int carNum = std::distance(this->cars.begin(), iter); //convert iterator to index
		bool passOnNext = Building::passOnNext(carNum); // peek at next floor
		iter->updateState(nextFlrCall, passOnNext);
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

//REMOVE AFTER TESTING
int Building::getCarFlr(int car) const
{
	return this->cars.at(car).getFloor();
}

//REMOVE AFTER TESTING
int Building::getCarState(int car) const
{
	return this->cars.at(car).getState();
}