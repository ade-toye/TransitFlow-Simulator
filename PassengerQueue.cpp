/*
PassengerQueue.cpp
Adetoye Adebayo
24th September, 2025
CS 15 HW 3 MetroSim
This file implements PassengerQueue which supports enqueue at back,
front lookup, dequeue from front, size, and printing the queue for
stations/train. It uses a standard list container for front/back 
operations.

*/

#include "PassengerQueue.h"
#include <stdexcept>


/*
name: PassengerQueue::front()
purpose: Return the passenger at the front of this queue so callers can
         see who is next
arguments: none
returns: the Passenger at the front of the queue (not removed)
effects: none
note: throws std::runtime_error if the queue is empty
*/
Passenger PassengerQueue::front() {
    // If the queue is empty, we throw a std::runtime_error
    if (data.empty()) {
        throw std::runtime_error("PassengerQueue::front on empty queue");
    }
    return data.front(); 
}

/*
name: PassengerQueue::dequeue()
purpose: Remove the passenger at the front of this queue.
arguments: none
returns: none
effects: queue size decreases by one
note: throws std::runtime_error if the queue is empty
*/
void PassengerQueue::dequeue() {
    // If the queue is empty, we throw a std::runtime_error
    if (data.empty()) {
        throw std::runtime_error("PassengerQueue::dequeue on empty queue");
    }
    // size() is reduced by 1 and front() advances 
    data.pop_front();
}

/*
name: PassengerQueue::enqueue(const Passenger &passenger)
purpose: Add the given passenger to the back of this queue.
arguments: passenger - the rider to add which represents 
           someone waiting in line
returns: none
effects: queue size increases by one
note: none
*/
void PassengerQueue::enqueue(const Passenger &passenger) {
    data.push_back(passenger);
}

/*
name: PassengerQueue::size()
purpose: Report how many passengers are in this queue.
arguments: none
returns: the current number of passengers in the queue
effects: none
note: none
*/
int PassengerQueue::size() {
    int n = data.size();
    return n;
}

/*

name: PassengerQueue::print(std::ostream &output)
purpose: Write all passengers in order from front to back to the given
         stream, using each passenger's print format
arguments: output - the stream to write the queue into
returns: none
effects: writes to the output stream
note: none
*/
void PassengerQueue::print(std::ostream &output) {
    // Copy so printing does not change the real queue.
    std::list<Passenger> copy = data;

    while (not copy.empty()) {
        Passenger p = copy.front();
        p.print(output);
        copy.pop_front();
    }
}