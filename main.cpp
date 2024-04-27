/*
Written By Sebastian Yepez, 2024
*/

#include "priorityQ.h"
#include "priorityQ.cpp"
#include "lander.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main() {
    //open input file
    ifstream inFile("LanderInput.txt");
    //create priority queue
    priorityQ<string, lander> landerList;

    //read input file
    string s;
    while(getline(inFile, s)) {
        if(s.empty()) continue; //avoid empty line
        stringstream sstream(s);
        string name;
        double alt, fuel, mass, max_fuel_rate, thrust; //parse input file
        sstream >> name >> mass >> thrust >> max_fuel_rate >> alt >> fuel;
        lander newlander(name, mass, thrust, max_fuel_rate, alt, fuel); // 1 new lander per line
        landerList.push_back(name, newlander); //push lander onto priority queue
    }

    //close the input file
    inFile.close();

    cout << endl;

    while(!landerList.isEmpty()){
    //output the top 3 landers
    priorityQ<string, lander> tempList;

    for (int i = 0; i < 3; i++) {
        cout << fixed << setprecision(6);
        tempList.push_back(landerList.get_front_key(), landerList.get_front_priority());
        cout << "(" << i+1 << ") Name: " << landerList.get_front_key() << " " <<
        landerList.get_front_priority().get_altitude() << " meters from the moon surface" << endl;
        cout << "traveling at " << landerList.get_front_priority().get_velocity() << " m/s" << endl;
        cout << "Fuel: " << landerList.get_front_priority().get_fuel_amount() << endl;
        cout << endl;
        landerList.pop_front();
        if(landerList.isEmpty()) break;
    }

    for (int i = 0; i < 3; i++) {
        landerList.push_back(tempList.get_front_key(), tempList.get_front_priority());
        tempList.pop_front();
        if(tempList.isEmpty()) break;
    }

    //read in from cin
    string inName;
    double inThrottle;
    cout << "\nEnter lander name and throttle amount: ";
    cin >> inName >> inThrottle;
    cin.clear();
    cin.ignore();
    cout << inName << " " << inThrottle << endl;

    //find lander
    lander tempLander = landerList.get_element(inName);
    //update flow amount
    tempLander.change_flow_rate(inThrottle);
    //call simulate function
    tempLander.simulate();
    //call the update function on the priority queue
    landerList.update_element(inName, tempLander);

    //if a lander has landed
    if(tempLander.get_status() == 'l') {
        cout << inName << " landed :)" << endl;
    // remove from priorityQ
        landerList.pop_front();
    }
    // if lander crashed
    else if (tempLander.get_status() == 'c') {
        cout << inName << " crashed :(" << endl;
        landerList.pop_front();
    }
    }
return 0; // end main
}