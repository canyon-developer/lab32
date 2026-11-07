// Stage 5: completed toll-booth deque simulation.
#include "Car.h"

#include <cstdlib>
#include <ctime>
#include <deque>
#include <iostream>

const int INITIAL_QUEUE_SIZE = 2;
const int PAY_PROBABILITY = 55;

void displayQueue(std::deque<Car>& tollLane) {
    if (tollLane.empty()) {
        std::cout << "    Empty\n";
        return;
    }

    for (Car& car : tollLane) {
        std::cout << "    ";
        car.print();
    }
}

void fillInitialQueue(std::deque<Car>& tollLane) {
    for (int i = 0; i < INITIAL_QUEUE_SIZE; ++i) {
        tollLane.push_back(Car());
    }
}

void performTimePeriod(std::deque<Car>& tollLane, int timePeriod) {
    std::cout << "\nTime: " << timePeriod << " Operation: ";

    const bool carPays = std::rand() % 100 < PAY_PROBABILITY;
    if (carPays) {
        Car paidCar = tollLane.front();
        tollLane.pop_front();

        std::cout << "Car paid: ";
        paidCar.print();
    } else {
        tollLane.push_back(Car());

        std::cout << "Joined lane: ";
        tollLane.back().print();
    }

    std::cout << "Queue:\n";
    displayQueue(tollLane);
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::deque<Car> tollLane;
    fillInitialQueue(tollLane);

    std::cout << "Initial queue:\n";
    displayQueue(tollLane);

    int timePeriod = 0;
    while (!tollLane.empty()) {
        ++timePeriod;
        performTimePeriod(tollLane, timePeriod);
    }

    std::cout << "\nThis simulation ran " << timePeriod
              << " cycles until the queue was empty.\n";
    return 0;
}
