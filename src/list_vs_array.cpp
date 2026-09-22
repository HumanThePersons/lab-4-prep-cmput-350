#include <cstddef>  // size_t
#include <cstdint>  // uint64_t
#include <random>   // mt19937_64
#include <iostream> // cout
#include <vector>
#include <list>

#include "timer.h"

constexpr size_t SIZE = 16000000;

int main() {
    Timer timer = Timer();  // Initializing a timer

    std::vector<uint64_t> arrayTestReserve = std::vector<uint64_t>();
    arrayTestReserve.reserve(SIZE);

    std::vector<uint64_t> arrayTestNoReserve = std::vector<uint64_t>();
    std::list<uint64_t> listTest = std::list<uint64_t>();

    std::mt19937_64 rng(0);

    // Testing time to fill arrrays vs list
    // Vector with reserve
    rng.seed(0);
    timer.restart();
    for (size_t i = 0; i < SIZE; i++) {
        arrayTestReserve.push_back(rng());  // appends the next random number to the array
    }
    uint64_t arrayReserveTime = timer.click<Timer::Micros>();
    std::cout << "Time for array with reserve: " << arrayReserveTime << " microseconds.\n";

    // Vector without reserve
    rng.seed(0);
    timer.restart();
    for (size_t i = 0; i < SIZE; i++) {
        arrayTestNoReserve.push_back(rng()); // appends the next random number to the array
    }
    uint64_t arrayNoReserveTime = timer.click<Timer::Micros>();
    std::cout << "Time for array without reserve: " << arrayNoReserveTime << " microseconds.\n";

    // Doubly linked list
    rng.seed(0);
    timer.restart();
    for (size_t i = 0; i < SIZE; i++) {
        listTest.push_back(rng());
    }
    uint64_t listTime = timer.click<Timer::Micros>();
    std::cout << "Time for list: " << listTime << " microseconds.\n";

    // Testing time to sum data in arrays vs list
    uint64_t arrayReserveSum = 0;
    uint64_t arrayNoReserveSum = 0;
    uint64_t listSum = 0;

    // Vector with reserve
    timer.restart();
    for (size_t i = 0; i < arrayTestReserve.size(); i++) {
        arrayReserveSum += arrayTestReserve[i];
    }
    uint64_t arrayReserveSumTime = timer.click<Timer::Micros>();
    std::cout << "Sum for array with reserve: " << arrayReserveSum << " found in " << arrayReserveSumTime << " microseconds.\n";

    // Vector without reserve
    timer.restart();
    for (size_t i = 0; i < arrayTestNoReserve.size(); i++) {
        arrayNoReserveSum += arrayTestNoReserve[i];
    }
    uint64_t arrayNoReserveSumTime = timer.click<Timer::Micros>();
    std::cout << "Sum for array without reserve: " << arrayNoReserveSum << " found in " << arrayNoReserveSumTime << " microseconds.\n";

    // List
    timer.restart();
    for (auto curr = listTest.begin(); curr != listTest.end(); ++curr) {
        listSum += *curr;
    }
    uint64_t listSumTime = timer.click<Timer::Micros>();
    std::cout << "Sum for list: " << listSum << " found in " << listSumTime << " microseconds.\n";

    return 0;
}