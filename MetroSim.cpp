/*
MetroSim.cpp
Adetoye Adebayo
3rd Ocrtober, 2025
CS 15 HW 3 MetroSim
My metrosim.cpp implements MetroSim and is really the MetroSim engine.
It reads commands, prints the state after each one, moves the train 
with wrap-around, unloads riders at arrival, boards waiting riders, 
and logs exits. Stations use queues; the train stores riders in 
queues grouped by destination buckets on the train.
*/
#include "MetroSim.h"
#include <sstream>

/*
name: MetroSim::MetroSim(const std::vector<std::string> &stationNames)
purpose: Creates a new simulation with the given station names, sets up
    empty station queues and empty train buckets and sets the start at
    station 0 with the first passenger id.
arguments: stationNames - list of station names in travel order
returns: none
effects: Initializes internal vectors to stationNames.size() and sets 
    cur = 0 and nextId = 1.
note: none
*/
MetroSim::MetroSim(const std::vector<std::string> &stationNames) {
    names = stationNames;
    int n = (int)stationNames.size();
    stations = std::vector<PassengerQueue>(n);
    trainByDest = std::vector<PassengerQueue>(n); // One bucket per 
                                                    // destination.
    cur = 0;
    nextId = 1; // Riders ID starting from 1. 
}

/*
name: MetroSim::printTrains(std::ostream &out)
purpose: Print the current riders on the train in the required format.
arguments: out - output stream to write to.
returns: none
effects: Writes to the given stream
note: none
*/
void MetroSim::printTrains(std::ostream &out) {
    out << "Passengers on the train: {";
    for (int d = 0; d < (int)trainByDest.size(); d++) {
        trainByDest[d].print(out); // Print riders grouped by 
                                            // destination d.
    }
    out << "}\n";
}

/*
name: MetroSim::printStatiions(std::ostream &out)
purpose: Print all stations in order, marking the current station with
       "TRAIN:" and showing each station’s waiting line.
arguments: out - output stream to write to.
returns: none
effects: Writes to the given stream
note: none
*/
void MetroSim::printStatiions(std::ostream &out) {
    for (int i = 0; i < (int) names.size(); i++) {
        if (i == cur) {
            out << "TRAIN: "; // Current station marker.
        } else {
            out << "       "; 
        }
        out << "[" << i << "] " << names[i] << " {"; 
        stations[i].print(out); // Print waiting line at station i.
        out << "}\n";
    }
}

/*
name: MetroSim::printState(std::ostream &out)
purpose: Print the full simulation state (train line, then stations).
arguments: out - output stream to write to.
returns: none
effects: Writes to the given stream.
note: none
*/
void MetroSim::printState(std::ostream &out) {
    printTrains(out);
    printStatiions(out);
}


/*
name: MetroSim::printInitialState(std::ostream &out)
purpose: Print the starting state of the simulation before any commands.
arguments: out - output stream to write to.
returns: none
effects: Writes to the given stream
note: none
*/
void MetroSim::printInitialState(std::ostream &out) {
    printState(out);
}

/*

name: MetroSim::unloadAt(int stationIndex, std::ostream &log)
purpose: Remove from the train all riders whose destination is the given
       station and log each rider’s exit.
arguments: stationIndex - index of the arrival station in the names list;
       log - stream to record exit messages.
returns: none
effects: Empties the train bucket for stationIndex
note: none. 
*/
void MetroSim::unloadAt(int stationIndex, std::ostream &log) {
    // Only unload riders whose destination is stationsIndex.
    while (trainByDest[stationIndex].size() > 0) {
        Passenger p = trainByDest[stationIndex].front();
        trainByDest[stationIndex].dequeue();  // Remove them from train.
        log << "Passenger " << p.getId()
            << " left train at station " << names[stationIndex] << "\n";
    }
}

/*

name: MetroSim::boardAt(int stationIndex)
purpose: Move all waiting riders at the given station onto the train,
       grouping them by their destination.
arguments: stationIndex - index of the boarding station in the names list.
returns: none
effects: Removes riders from that station’s queue; adds them to the
       train’s destination buckets.
note: 
*/
void MetroSim::boardAt(int stationIndex) {
    while (stations[stationIndex].size() > 0) {
        Passenger p = stations[stationIndex].front(); 
        stations[stationIndex].dequeue(); // Line shrinks by one.
        int d = p.getEndingStation(); // Destination bucket index.
        trainByDest[d].enqueue(p); // Board into that bucket.
    }
}

/*

name: MetroSim::processCommands(std::istream &in, std::ostream &out, 
std::ostream &log)
purpose: Run the simulation loop by reading commands, updating the system,
    printing thhe state, and loging exits. 
arguments: in - where commands come from (file or std::cin);
       out - where the current state is printed;
       log - where passenger exit lines are written.
returns: none
effects: Changes simulation state (board, move, unload).
note: 
*/
void MetroSim::processCommands(std::istream &in, std::ostream &out, 
std::ostream &log) {
    const int N = (int) names.size();
    std::string line;

    while (true) { // Command loop ends on "m f".
        out << "Command? ";
        if (not std::getline(in, line)) {
        out << "Thanks for playing MetroSim. Have a nice day!\n";
        return;
        }
        std::istringstream iss(line);
        std::string command;
        bool hasCommand = (bool)(iss >> command);

        if (not hasCommand){
            printState(out); // An empty line so just reprint state.
        }
        else if (command == "p"){
            int staringStation;
            int endingStation;
            if (iss >> staringStation >> endingStation) { // Valid "p
                                                // start destiantion".
                Passenger p(nextId++, staringStation, endingStation);
                stations[staringStation].enqueue(p);  // Add to that 
                                                     // station line.
            }
        printState(out);
        } else if (command == "m") {
            std::string sub; // Expect "m m" or "m f".
            bool hasSub = (bool)(iss >> sub);
            if (hasSub and sub == "m") {
                boardAt(cur); // Board first at current station.
                cur = (cur + 1) % N; // Move one stop; wrap-around.
                unloadAt(cur, log); // Then unload at arrival and log exits.
                printState(out); // Print the new state.
            } else if (hasSub and sub == "f") {
                out << "Thanks for playing MetroSim. Have a nice day!\n";
                return;
            } else {
                printState(out); // Unrecognized simulator commands so 
                                                // just print the state. 
            }
        } else {
            printState(out); // Unknown command so just print state
        }
    }
}
