/*
Passenger.h 
Adetoye Adebayo 
24th Septemeber, 2025

CS 15 HW 3 MetroSim
This file declares the Passenger class where a Passenger is a rider
with an id, a start station, and an end station. Clients can read these 
values and print the rider for use in station queues and on the train.
*/

#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include <iostream>

class Passenger {
   public:
    Passenger(int id, int startingStation, int endingStation);
    int getId(); // Gets the passenger ID 
    int getStartingStation(); // Gets the start location
    int getEndingStation(); // Gets the end location
    void print(std::ostream &output);

   private:
    int id; // Unique rider ID
    int startingStation; // Where the rider starts 
    int endingStation; // Where tghe rider ends 
};

#endif

