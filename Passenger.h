/*
 *	 Passenger.h
 * 
 *  Passenger class header file: 
 * 
 *  Author: Mike Ricci
 *  Date: 20140716
 */

#ifndef _PASSENGER_H_
#define _PASSENGER_H_

class Passenger
{
public:

	Passenger(int timeStart, int floorStart, int floorEnd);
	virtual ~Passenger();
	int getFloorEnd() const;

private:

	int floorEnd;
	int floorStart;
	int timeStart;
	int timePickUp;
	int timeDropOff;

}; // end Passenger class

#endif // _PASSENGER_H_

