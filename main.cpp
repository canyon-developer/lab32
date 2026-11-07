// Stage 3: perform and display one randomly selected time period.
#include "Car.h"

#include <cstdlib>
#include <ctime>
#include <deque>
#include <iostream>

const int INITIAL_QUEUE_SIZE = 2;
const int PAY_PROBABILITY = 55;

void displayQueue(std::deque<Car>& tollLane) {
    if (tollLane.empty()) {
        std::cout << "  Empty\n";
        return;
    }

    for (Car& car : tollLane) {
        std::cout << "  ";
        car.print();
    }
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::deque<Car> tollLane;
    for (int i = 0; i < INITIAL_QUEUE_SIZE; ++i) {
        tollLane.push_back(Car());
    }

    std::cout << "Initial queue:\n";
    displayQueue(tollLane);

    std::cout << "\nTime: 1 Operation: ";
    if (std::rand() % 100 < PAY_PROBABILITY) {
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
    return 0;
}
