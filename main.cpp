// Lab 33, step 2: add helpers for working with the toll plaza.
#include "Car.h"

#include <deque>
#include <iostream>

const int LANE_COUNT = 4;

void displayPlaza(std::deque<Car> lanes[]) {
    for (int lane = 0; lane < LANE_COUNT; ++lane) {
        std::cout << "Lane " << lane + 1 << " Queue:";

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

int main() {
    std::deque<Car> lanes[LANE_COUNT];

    for (int lane = 0; lane < LANE_COUNT; ++lane) {
        lanes[lane].push_back(Car());
    }

    // Validate that a rear car can be removed from one lane and added to another.
    Car switchingCar = lanes[0].back();
    lanes[0].pop_back();
    lanes[2].push_back(switchingCar);

    displayPlaza(lanes);
    return 0;
}
