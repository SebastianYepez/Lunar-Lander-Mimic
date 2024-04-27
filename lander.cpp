/*
Written by Sebastian Yepez, 2024
*/

#include "lander.h"
#include <cmath>
#include <string>
#include <iostream>
using namespace std;

const int TIME = 1; //1 second of time for the simulation function

/*------------------------------------------------------------------
Constructor that initializes the lunar lander at the start of
the simulation
------------------------------------------------------------------*/
lander::lander(string name, double mass, double thrust, double max_fuel, 
						double alt, double fuel)
{
	lander_mass = mass;
	max_thrust = thrust; 
	max_fuel_consumption_rate = max_fuel;

	stillLanding = true;
	flow_rate = 0.0;
	velocity = 0.0;
	altitude = alt;
	fuel_amount = fuel;
	this->name = name;
}

double lander::get_velocity() const
{
	return velocity;
}

double lander::get_altitude() const
{
	return altitude;
}

double lander::get_fuel_amount() const
{
	return fuel_amount;
}

string lander::get_name() const
{
	return name;
}

// returns ’a’ if still airborne, returns ’c’ if not airborn and the
// velocity is less than or equal to -2 (lander crashed), and returns ’l’ if not airborne and velocity is greater
// than -2 (lander has landed)
char lander::get_status() const
{
	if(stillLanding) return 'a'; // airborne
	if(velocity <= -2) return 'c'; //lander crashed
	return 'l'; // lander landed "successfully"
}

// if r is between 0 and 1 (inclusive), then set flow rate
// with r if fuel amount is larger than 0 and the return true, return false if r is not between 0 and 1
// (inclusive) and do not set flow rate, also if fuel_amount is 0, set the flow_rate with 0
bool lander::change_flow_rate(double r)
{
	if(r >= 0 && r <= 1) { // if fuel_amount != 0, then it is > 0 b/c it cannot be negative
		if(fuel_amount == 0) {
		flow_rate = 0;
		return true;
		}
		flow_rate = r;
		return true;
	}
	return false;
}

// if the lander is airborne
// 1. Calculate the instantaneous velocity (TIME is a constant that contains 1)
// v = TIME x (flow rate × max thrust)/(lander mass + fuel amount) − 1.62
// 2. Increment/update velocity field by v
// 3. Increment/update altitude field by TIME × velocity field
// 4. Update stillLanding field if necessary
// 5. Decrement/update fuel_amount by TIME × max_fuel_rate × |v|
// 6. Set fuel_amount to 0 if the amount in the above step results to negative for fuel amount
void lander::simulate()
{
	if(stillLanding) {
		double v = (TIME * ((flow_rate * max_thrust)/(lander_mass + fuel_amount))) - 1.62;
		velocity += v;
		altitude += (TIME * velocity);
		if(altitude <= 0) stillLanding = false;
		if(flow_rate > 0) fuel_amount -= (TIME * max_fuel_consumption_rate * abs(v));
		if(fuel_amount < 0) fuel_amount = 0;
	}
}

// you need to implement the less than operator to be used in the priority queue class (min or max heap), 
// 		you compare the priority of two lander objects (the *this object and the rhs object), the following 
//		tier system is how the priorities between the two objects can be determined:
// 1. The object with the smallest altitude has the higher priority
// 2. The object with less fuel has the higher priority
// 3. The object with the larger mass has the higher priority
// 4. The object with the name earlier in alphabetic order has the higher priority
bool lander::operator<(const lander& rhs) const
{
	if(this->altitude < rhs.altitude) return true;
	else if(altitude == rhs.altitude){
		if(fuel_amount < rhs.fuel_amount) return true;
		else if(fuel_amount == rhs.fuel_amount){
			if(lander_mass > rhs.lander_mass) return true;
			else if(lander_mass == rhs.lander_mass){
					if(name < rhs.name) return true; 
			}
		}
	}
	return false;
}
