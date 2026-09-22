#include <cassert>  // assert
#include <cstddef>  // size_t
#include <cstdint>  // uint64_t, uint32_t
#include <random> // mt19937_64
#include <iostream>  // cout
#include <bitset>  //bitset for testing

// Expands the binary representation of input by a factor of scale.
// e.g., expand(0b1111ull, 3) == 0b001001001001
// References: https://www.geeksforgeeks.org/cpp/cpp-bitwise-operators/
uint64_t expand(uint64_t input, uint32_t scale) {
    assert(scale >= 1);
    uint64_t newNum = 0b0;

    for (uint64_t place = 0; place < 64; place++) {
        uint64_t nextPlace = place*scale;  // example: the bit at place 2 with scale 3 moves to place 2*3 = 6
        if (nextPlace >= 64) {
            // the bit as well as any that follow would be cut off anyways
            break;
        }
        // getting the next digit as 0b0...01 or 0b0...00
        uint64_t nextDigit = input >> place; // shift input to the right so that the current place is now at place 0
        nextDigit = nextDigit & 1; // AND sets all bits except the one at place 0, and leaves place 0 as what it was

        uint64_t placedBit = nextDigit << nextPlace;  // puts nextDigit into its new place (place*scale)
        newNum = newNum | placedBit;  // bitwise or just adds
    }
    return newNum; 
}

int main() {
    // 0b111 with scale 3 should give: 0b001001001 (printing with leading zeros up to 64 digits)
    std::cout << std::bitset<64>(expand(0b111, 3)) << "\n";

    // 0b111 with scale 5 should give: 0b000010000100001
    std::cout << std::bitset<64>(expand(0b111, 5)) << "\n";

    // 0b10101 with scale 2 should give: 0b0100010001
    std::cout << std::bitset<64>(expand(0b10101, 2)) << "\n";

    // 0b111 with scale 45 should give smth idk but it should only have 2 1s (the third 1 would be out of bounds)
    std::cout << std::bitset<64>(expand(0b111, 45)) << "\n";

    return 0;
}
