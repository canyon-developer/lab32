// Stage 1: create and print the initial cars.
#include "Car.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

const int INITIAL_QUEUE_SIZE = 2;

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::cout << "Cars generated for the initial toll line:\n";
    for (int i = 0; i < INITIAL_QUEUE_SIZE; ++i) {
        Car car;
        car.print();
    }

    return 0;
}
