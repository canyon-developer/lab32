// Lab 33, step 6: integrate all three operations into the simulation.
#include "Car.h"

#include <cstdlib>
#include <ctime>
#include <deque>
#include <iostream>

const int LANE_COUNT = 4;
const int INITIAL_CARS_PER_LANE = 2;
const int SIMULATION_PERIODS = 20;
const int PAY_PROBABILITY = 46;
const int JOIN_PROBABILITY = 39;
const int SWITCH_PROBABILITY = 15;
const int EMPTY_JOIN_PROBABILITY = 50;

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
    const int offset = std::rand() % (LANE_COUNT - 1) + 1;
    return (originalLane + offset) % LANE_COUNT;
}

void performLaneOperation(std::deque<Car> lanes[], int lane) {
    if (lanes[lane].empty()) {
        if (std::rand() % 100 < EMPTY_JOIN_PROBABILITY) {
            lanes[lane].push_back(Car());
            std::cout << "Lane: " << lane + 1 << " Joined: ";
            lanes[lane].back().print();
        } else {
            std::cout << "Lane: " << lane + 1 << " No car joined.\n";
        }
        return;
    }

    const int operation = std::rand() % 100;
    if (operation < PAY_PROBABILITY) {
        Car paidCar = lanes[lane].front();
        lanes[lane].pop_front();
        std::cout << "Lane: " << lane + 1 << " Paid: ";
        paidCar.print();
    } else if (operation < PAY_PROBABILITY + JOIN_PROBABILITY) {
        lanes[lane].push_back(Car());
        std::cout << "Lane: " << lane + 1 << " Joined: ";
        lanes[lane].back().print();
    } else {
        const int newLane = chooseDifferentLane(lane);
        Car switchingCar = lanes[lane].back();
        lanes[lane].pop_back();
        lanes[newLane].push_back(switchingCar);
        std::cout << "Lane: " << lane + 1 << " Switched to Lane "
                  << newLane + 1 << ": ";
        switchingCar.print();
    }
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::deque<Car> lanes[LANE_COUNT];
    fillInitialPlaza(lanes);

    std::cout << "Initial queue:\n";
    displayPlaza(lanes);

    for (int time = 1; time <= SIMULATION_PERIODS; ++time) {
        std::cout << "\nTime: " << time << '\n';
        for (int lane = 0; lane < LANE_COUNT; ++lane) {
            performLaneOperation(lanes, lane);
        }
        displayPlaza(lanes);
    }

    return 0;
}
