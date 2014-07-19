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

class Building
{
public:

	Building(std::string filepath, int numCars, int speed, int numFloors);
	virtual ~Building();

	void addTravelTime(int travelTime);
	void addWaitTime(int waitTime);
	void calcTravelTime();
	void calcWaitTime();
	int getNextFloorCall() const;
	void incrementClock();
	void updateCarStates();

private:

	int avgTravelTime;
	int avgWaitTime;
	std::vector<Car> cars;
	std::vector<Floor> floors;
	std::queue<Passenger> passengers;
	int time = 0;
	std::vector<int> travelTimes;
	std::vector<int> waitTimes;

};

#endif // _BUILDING_H_

