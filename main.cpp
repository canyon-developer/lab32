// Lab 33, step 7: final toll plaza simulation.
#include "Car.h"

#include <cstdlib>
#include <ctime>
#include <deque>
#include <iostream>

const int LANE_COUNT = 4;
const int INITIAL_CARS_PER_LANE = 2;
const int SIMULATION_PERIODS = 20;
const int PERCENT_RANGE = 100;

const int PAY_PROBABILITY = 46;
const int JOIN_PROBABILITY = 39;
const int SWITCH_PROBABILITY = 15;
const int EMPTY_JOIN_PROBABILITY = 50;
const int EMPTY_NO_JOIN_PROBABILITY = 50;

const int PAY_LIMIT = PAY_PROBABILITY;
const int JOIN_LIMIT = PAY_PROBABILITY + JOIN_PROBABILITY;

static_assert(PAY_PROBABILITY + JOIN_PROBABILITY + SWITCH_PROBABILITY
                  == PERCENT_RANGE,
              "Lane operation probabilities must total 100 percent.");
static_assert(EMPTY_JOIN_PROBABILITY + EMPTY_NO_JOIN_PROBABILITY
                  == PERCENT_RANGE,
              "Empty lane probabilities must total 100 percent.");

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

void handleEmptyLane(std::deque<Car>& lane, int laneNumber) {
    if (std::rand() % PERCENT_RANGE < EMPTY_JOIN_PROBABILITY) {
        lane.push_back(Car());
        std::cout << "Lane: " << laneNumber << " Joined: ";
        lane.back().print();
    } else {
        std::cout << "Lane: " << laneNumber << " No car joined.\n";
    }
}

void performLaneOperation(std::deque<Car> lanes[], int lane) {
    const int laneNumber = lane + 1;
    if (lanes[lane].empty()) {
        handleEmptyLane(lanes[lane], laneNumber);
        return;
    }

    const int operation = std::rand() % PERCENT_RANGE;
    if (operation < PAY_LIMIT) {
        Car paidCar = lanes[lane].front();
        lanes[lane].pop_front();

        std::cout << "Lane: " << laneNumber << " Paid: ";
        paidCar.print();
    } else if (operation < JOIN_LIMIT) {
        lanes[lane].push_back(Car());

        std::cout << "Lane: " << laneNumber << " Joined: ";
        lanes[lane].back().print();
    } else {
        const int newLane = chooseDifferentLane(lane);
        Car switchingCar = lanes[lane].back();
        lanes[lane].pop_back();
        lanes[newLane].push_back(switchingCar);

        std::cout << "Lane: " << laneNumber << " Switched to Lane "
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

    std::cout << "\nSimulation complete after " << SIMULATION_PERIODS
              << " time periods.\n";
    return 0;
}
