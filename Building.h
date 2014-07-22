/*
 *	 Building.h
 * 
 *  Building class header file: 
 * 
 *  Author: Mike Ricci
 *  Date: 20140716
 */

#ifndef _BUILDING_H_
#define _BUILDING_H_

//WHY DID I HAVE TO INCLUDE THESE HERE TO GET IT TO COMPILE SUCCESSFULLY?
#include <array>
#include <cstdlib>
#include <vector>
//#include <queue>
#include <iostream> // REMOVE IF UNUSED
#include <fstream>
#include <sstream>
#include <string>
#include "Passenger.h"
#include "Car.h"
#include "Floor.h"

class Building
{
public:

	//singleton instance function to call private constructor
	static Building* Instance(std::string filepath, int numCars, int speed, int numFloors); 
	virtual ~Building();

	void addTravelTime(int travelTime);
	void addWaitTime(int waitTime);
	void calcTravelTime();
	void calcWaitTime();
	void destroyPassenger(Passenger* passenger);
	int getAvgTravel() const;
	int getAvgWait() const;
	int getFinalPassengerTime() const;
	Passenger* getNextPassOnFlr(int floor) const;
	int getNextFlrCall() const;
	int getTime() const;
	void incrementClock();
	void makePassenger(int time);
	void rmNextPassFromFlr(int floor); // REMOVE IF UNUSED
	void transactPassengers();
	void updateCarStates();

	//REMOVE THESE FUNCTIONS AFTER TESTING 
	int sizeOfCars() const;
	int sizeOfFloors() const;
	int getCarFlr(int car) const;
	int getCarState(int car) const;

private:

	//Singleton constructor
	Building(std::string filepath, int numCars, int speed, int numFloors);
	static Building* instance;

	int avgTravelTime;
	int avgWaitTime;
	std::vector<Car> cars;
	std::vector<Floor> floors;
	std::vector< std::array<int,3> > parsed;
	std::deque<Passenger*> passengers;
	int time = 0;
	std::vector<int> travelTimes;
	std::vector<int> waitTimes;

};

#endif // _BUILDING_H_

