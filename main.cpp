// Lab 33, step 3: populate every toll lane before the simulation.
#include "Car.h"

#include <cstdlib>
#include <ctime>
#include <deque>
#include <iostream>

const int LANE_COUNT = 4;
const int INITIAL_CARS_PER_LANE = 2;

void displayPlaza(std::deque<Car> lanes[]) {
    for (int lane = 0; lane < LANE_COUNT; ++lane) {
        std::cout << "Lane " << lane + 1 << ":";

        if (lanes[lane].empty()) {
            std::cout << " empty\n";
            continue;
        }

        std::cout << '\n';
        for (Car& car : lanes[lane]) {
            std::cout << "    ";
            car.print();
        }
    }
}

void fillInitialPlaza(std::deque<Car> lanes[]) {
    for (int lane = 0; lane < LANE_COUNT; ++lane) {
        for (int car = 0; car < INITIAL_CARS_PER_LANE; ++car) {
            lanes[lane].push_back(Car());
        }
    }
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::deque<Car> lanes[LANE_COUNT];
    fillInitialPlaza(lanes);

    std::cout << "Initial queue:\n";
    displayPlaza(lanes);
    return 0;
}
