/*
main.cpp
Adetoye Adebayo
3rd Ocrtober, 2025
CS 15 HW 3 MetroSim
This file runs MetroSim by reading station names and optional commands, 
opening the output file, printing the starting state, then processing
commands to drive the simulator.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "MetroSim.h"
#include <cstdlib>
using namespace std;


/*
name: error_abort(string error_message)
purpose: Print a fatal error message and end the program immediately.
arguments: error_message – the message to show the user explaining what
           went wrong.
returns: none
effects: Writes the message to std::cerr and terminates the process
         with EXIT_FAILURE.
note: none. 
*/
void error_abort(string error_message) {
    cerr << error_message << "\n";
    exit(EXIT_FAILURE);
}

/*
name: open_or_die(streamtype &stream, const std::string &file_name)
purpose: Open a file for reading or writing so the caller can safely use
the stream thereafter.
arguments: stream – an ifstream/ofstream to be opened;
           file_name – path of the file to open.
returns: none.
effects: Attempts to open the stream and on success leaves the stream
open and ready but on failure prints an error and terminates the
program with EXIT_FAILURE.
note: none. 
*/
template<typename streamtype>
void open_or_die(streamtype &stream, const std::string &file_name) {
    stream.open(file_name);
    if (not stream.is_open()) { // Prints this error message if it 
                                // cannot open the stream
        error_abort("Error: could not open file " + file_name);
    }
}


/*
name: read_stations(std::istream &in, std::vector<std::string> &names)
purpose: Load station names from a text input, one name per line, into
       the given vector so the simulator knows its station list.
arguments: in - source to read lines from; names - vector to fill.
returns: true if at least two names were read and false otherwise.
effects: Consumes lines from 'in' and appends to 'names'.
note: none
*/
bool read_stations(std::istream &in, std::vector<std::string> &names) {
    std::string line; // Holds each line. 
    while (std::getline(in, line)) {
        names.push_back(line); 
    }
    return names.size() >= 2; // Require at least 2 stations
}


/*
name: main(int argc, char *argv[])
purpose: It Parses args, open files/streams, builds the
       MetroSim, prints the initial state, and runs command processing.
arguments: argc - count of command-line args; argv - the arg strings:
       argv[1] = stations file, argv[2] = output log file,
       optional argv[3] = commands file.
returns: 0 on success; 1 on usage or file/open/read errors.
effects: Opens/reads files or std::cin and writes to std::cout and to the
       output log file as well as running the simulation loop.
note: none
*/
int main(int argc, char *argv[]) {
    if (not(argc == 3 or argc == 4)) {
        // If there are not up to 2 or 3 args plus the program name, 
        // print this error message 
        cerr << "Usage: ./MetroSim stationsFile outputFile [commandsFile]\n";
        return EXIT_FAILURE;
    } 
    const string stationsPath = argv[1];
    const string outputPath = argv[2];
    ifstream stationsIn;
    open_or_die(stationsIn, stationsPath);   // aborts on failure
    ofstream logout;
    open_or_die(logout, outputPath); 
    vector<string> stationNames;
    if (not read_stations(stationsIn, stationNames)) {
        // Open succeeded but content is invalid (too few stations)
        error_abort("Error: could not open file " + stationsPath);
    }
    stationsIn.close();
    MetroSim simumlator(stationNames);
    simumlator.printInitialState(cout);
    if (argc == 4) {
        const string commandsPath = argv[3];
        ifstream commandsIn;
        open_or_die(commandsIn, commandsPath);   // aborts on failure
        simumlator.processCommands(commandsIn, cout, logout);
        commandsIn.close();
    } else {
        simumlator.processCommands(cin, cout, logout);
    }
    logout.close();
    return 0;
}