/*
 *	 Building.h
 * 
 *  Building class header file: The Building class represents a building in which
 *  and elevator simulation is ran.  This class is a singleton meaning only one
 *  instantiation is allowed at a time.  The building constructs all the passenger,
 *  car, and floor objects dynamically.  The passengers are deleted as they are
 *  dropped off at their destinations.  When destroyed, the passenger's wait and
 *  travel times are noted and added to a collection of the times.  After the
 *  simulation is completed, the times are averaged and displayed in main.cc.
 * 
 *  Author: Mike Ricci
 *  Date: 20140716
 */

#ifndef _BUILDING_H_
#define _BUILDING_H_

#include <array>
#include <cstdlib>
#include <vector>
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
	bool passOnNext(int car) const;
	void transactPassengers();
	void updateCarStates();

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