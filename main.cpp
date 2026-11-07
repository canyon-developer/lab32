// Stage 2: store the initial cars in a deque and display the lane.
#include "Car.h"

#include <cstdlib>
#include <ctime>
#include <deque>
#include <iostream>

const int INITIAL_QUEUE_SIZE = 2;

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
    return 0;
}
