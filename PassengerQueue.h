/*
PassengerQueue.h
Adetoye Adebayo
24th September, 2025
CS 15 HW 3 MetroSim

This file declares PassengerQueue using the queue ADT. New queues start
empty. Clients can add to the back, look at and remove from the front, get
the size, and print the queue. It uses a standard list container for
front/back operations.
*/

#ifndef __PASSENGERQUEUE_H__
#define __PASSENGERQUEUE_H__

#include <iostream>
#include <list>
#include "Passenger.h"

class PassengerQueue {
   public:
    Passenger front();
    void dequeue();
    void enqueue(const Passenger &passenger);
    int size(); // Current number of passengers in the queue.
    void print(std::ostream &output);

   private:
    std::list<Passenger> data; // The list that holds the passengers in line.
};

#endif