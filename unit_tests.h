/*
unit_test.h
Adetoye Adebayos
3rd Ocrtober, 2025
CS 15 HW 3 MetroSim

unit_tests.h declares basic unit tests for Phase 1. It tests Passenger and
PassengerQueue with checks on constructors, getters, print,
enqueue/dequeue, front, size, and queue print).
*/

#include <cassert>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

#include "Passenger.h"
#include "PassengerQueue.h"
#include "MetroSim.h"


// Tests initial state print on 2 stations.
void test_metroSim_print() {
    std::vector<std::string> names;
    names.push_back("A");
    names.push_back("B");
    MetroSim simulator(names);
    std::ostringstream out;
    simulator.printInitialState(out);
    std::string expected =
        "Passengers on the train: {}\n"
        "TRAIN: [0] A {}\n"
        "       [1] B {}\n";
    assert(out.str() == expected);
}

// Tests Passenger constructor and getters on two riders.
void test_constructor() {
    Passenger passenger1(1, 0, 2);
    assert(passenger1.getId() == 1);
    assert(passenger1.getStartingStation() == 0);
    assert(passenger1.getEndingStation() == 2);

    Passenger passenger2(9, 3, 5);
    assert(passenger2.getId() == 9);
    assert(passenger2.getStartingStation() == 3);
    assert(passenger2.getEndingStation() == 5);
}


// Tests Passenger::print exact format in three cases.
void test_passenger_print() {
    Passenger passenger1(1, 0, 2);
    std::ostringstream string1;
    passenger1.print(string1);
    assert(string1.str() == "[1, 0->2]");

    Passenger passenger2(10, 3, 3);
    std::ostringstream string2;
    passenger2.print(string2);
    assert(string2.str() == "[10, 3->3]");

    Passenger passenger3(7, 5, 1);
    std::ostringstream string3;
    passenger3.print(string3);
    assert(string3.str() == "[7, 5->1]");
}


// Tests enqueue print shows the correct order. 
void test_queue_enqueue() {
    PassengerQueue testQueue;

    testQueue.enqueue(Passenger(1, 0, 2));
    testQueue.enqueue(Passenger(2, 1, 3));

    std::ostringstream out;
    testQueue.print(out);
    assert(out.str() == "[1, 0->2][2, 1->3]");
}


// Tests size at 0, 1, and 3 items.
void test_queue_size() {
    PassengerQueue testQueue;

    assert(testQueue.size() == 0);

    testQueue.enqueue(Passenger(1, 0, 2));
    assert(testQueue.size() == 1);

    testQueue.enqueue(Passenger(2, 1, 3));
    testQueue.enqueue(Passenger(3, 2, 0));
    assert(testQueue.size() == 3);
}


// Tests print on empty, after two enqueues, and after a dequeue.
void test_queue_print() {
    PassengerQueue testQueue;

    std::ostringstream a;
    testQueue.print(a);
    assert(a.str() == "");

    testQueue.enqueue(Passenger(1, 0, 2));
    testQueue.enqueue(Passenger(2, 1, 3));

    std::ostringstream b;
    testQueue.print(b);
    assert(b.str() == "[1, 0->2][2, 1->3]");

    testQueue.dequeue();

    std::ostringstream c;
    testQueue.print(c);
    assert(c.str() == "[2, 1->3]");
}


// Tests front before/after dequeue and that empty queue throws.
void test_queue_front() {
    PassengerQueue testQueue;

    testQueue.enqueue(Passenger(1, 0, 2));
    testQueue.enqueue(Passenger(2, 1, 3));

    Passenger f1 = testQueue.front();
    assert(f1.getId() == 1);

    testQueue.dequeue();

    Passenger f2 = testQueue.front();
    assert(f2.getId() == 2);

    testQueue.dequeue();
    bool caught = false;
    try {
        (void) testQueue.front();
    } catch (const std::runtime_error& e) {
        caught = true;
    }
    assert(caught);
}


// Tests dequeue updates size/front and that empty dequeue throws.
void test_queue_dequeue() {
    PassengerQueue testQueue;

    testQueue.enqueue(Passenger(1, 0, 2));
    testQueue.enqueue(Passenger(2, 1, 3));

    testQueue.dequeue();
    assert(testQueue.size() == 1);
    assert(testQueue.front().getId() == 2);

    testQueue.dequeue();
    assert(testQueue.size() == 0);

    bool caught = false;
    try {
        testQueue.dequeue();
    } catch (const std::runtime_error& e) {
        caught = true;
    }
    assert(caught);
}