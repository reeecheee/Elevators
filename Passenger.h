/*
 *	 Passenger.h
 * 
 *  Passenger class header file: The passenger class represents elevator passengers
 *  and stores their origin and destination floors, the time they arrive at the
 *  origin, and their pick up and drop off times.  Getters are provided for the
 *  initial time/floors, getters and setters are provided for the times that are
 *  determined at pick up and drop off.
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
	int getFloorStart() const;
	int getTimeDropOff() const;
	int getTimePickUp() const;
	int getTimeStart() const;
	void setTimeDropoff(int time);
	void setTimePickUp(int time);

private:

	int floorEnd;
	int floorStart;
	int timeStart;
	int timePickUp;
	int timeDropOff;

}; // end Passenger class

#endif // _PASSENGER_H_