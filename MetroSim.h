/*
MetroSim.h
Adetoye Adebayo
3rd Ocrtober, 2025
CS 15 HW 3 MetroSim
This file declares MetroSim, which runs the simulation that holds station
names, station wait lines, train buckets by destination, current station,
and next passenger id. It also processes commands, moves, boards, unloads, 
and prints the state of the simulation.
*/

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "Passenger.h"
#include "PassengerQueue.h"
#include <string>
#include <vector>
#include <iostream>


class MetroSim
{
public:
    // Make a sim with the given station names.
    MetroSim(const std::vector<std::string> &stationNames);
    void printInitialState(std::ostream &out);
    void processCommands(std::istream &in, std::ostream &out, 
                                            std::ostream &log);


private:
    void printState(std::ostream &out);
    void printTrains(std::ostream &out);
    void printStatiions(std::ostream &out);
    void unloadAt(int stationIndex, std::ostream &log);
    void boardAt(int stationIndex);

    std::vector<std::string> names;
    std::vector<PassengerQueue> stations;
    std::vector<PassengerQueue> trainByDest; // Riders on the 
                                             // train by their destination.
    int cur; // The index of the current station.
    int nextId; // The index of the next passengers id.
};

#endif
