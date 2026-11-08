// Lab 33, step 1: validate an array of deque<Car> lanes.
#include "Car.h"

#include <deque>
#include <iostream>

const int LANE_COUNT = 4;

int main() {
    std::deque<Car> lanes[LANE_COUNT];

    // Exercise both ends of several deques in the array.
    lanes[0].push_back(Car());
    lanes[0].push_back(Car());
    lanes[1].push_front(Car());
    lanes[2].push_back(Car());
    lanes[3].push_back(Car());

    lanes[0].pop_front();
    lanes[2].pop_back();

    for (int lane = 0; lane < LANE_COUNT; ++lane) {
        std::cout << "Lane " << lane + 1 << " contains "
                  << lanes[lane].size() << " car(s).\n";
    }

    return 0;
}
