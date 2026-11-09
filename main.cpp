// Lab 33, step 4: run a 50/50 pay-or-join simulation on all lanes.
#include "Car.h"

#include <cstdlib>
#include <ctime>
#include <deque>
#include <iostream>

const int LANE_COUNT = 4;
const int INITIAL_CARS_PER_LANE = 2;
const int SIMULATION_PERIODS = 20;
const int PAY_PROBABILITY = 50;

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

void performLaneOperation(std::deque<Car>& lane, int laneNumber) {
    const bool pay = std::rand() % 100 < PAY_PROBABILITY;

    if (pay && !lane.empty()) {
        Car paidCar = lane.front();
        lane.pop_front();
        std::cout << "Lane: " << laneNumber << " Paid: ";
        paidCar.print();
    } else if (!pay) {
        lane.push_back(Car());
        std::cout << "Lane: " << laneNumber << " Joined: ";
        lane.back().print();
    } else {
        std::cout << "Lane: " << laneNumber << " No car joined.\n";
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
            performLaneOperation(lanes[lane], lane + 1);
        }
        displayPlaza(lanes);
    }

    return 0;
}
