// Lab 33, step 5: isolate and test rear-car lane switching.
#include "Car.h"

#include <cstdlib>
#include <ctime>
#include <deque>
#include <iostream>

const int LANE_COUNT = 4;
const int INITIAL_CARS_PER_LANE = 2;

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

void fillInitialPlaza(std::deque<Car> lanes[]) {
    for (int lane = 0; lane < LANE_COUNT; ++lane) {
        for (int car = 0; car < INITIAL_CARS_PER_LANE; ++car) {
            lanes[lane].push_back(Car());
        }
    }
}

int chooseDifferentLane(int originalLane) {
    // The offset is at least one, so the result cannot be the original lane.
    const int offset = std::rand() % (LANE_COUNT - 1) + 1;
    return (originalLane + offset) % LANE_COUNT;
}

void switchRearCar(std::deque<Car> lanes[], int originalLane) {
    if (lanes[originalLane].empty()) {
        return;
    }

    const int newLane = chooseDifferentLane(originalLane);
    Car switchingCar = lanes[originalLane].back();
    lanes[originalLane].pop_back();
    lanes[newLane].push_back(switchingCar);

    std::cout << "Lane: " << originalLane + 1 << " Switched to Lane "
              << newLane + 1 << ": ";
    switchingCar.print();
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::deque<Car> lanes[LANE_COUNT];
    fillInitialPlaza(lanes);

    std::cout << "Before switching:\n";
    displayPlaza(lanes);

    std::cout << "\nSwitch operations:\n";
    for (int lane = 0; lane < LANE_COUNT; ++lane) {
        switchRearCar(lanes, lane);
    }

    std::cout << "\nAfter switching:\n";
    displayPlaza(lanes);
    return 0;
}
