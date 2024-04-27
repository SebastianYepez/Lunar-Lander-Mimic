#include <string>

class lander
{
public:
	lander(std::string = "", double = 0, double = 0, 
		double = 0, double = 0, double = 0);
	double get_velocity() const;
	double get_altitude() const;
	double get_fuel_amount() const;
	std::string get_name() const;
	char get_status() const;
	bool change_flow_rate(double);
	void simulate();

	bool operator<(const lander&) const;
private:
	std::string name;
	double flow_rate;
	double velocity;
	double altitude;
	double fuel_amount;
	bool stillLanding;
	double lander_mass;
	double max_fuel_consumption_rate;
	double max_thrust;
};