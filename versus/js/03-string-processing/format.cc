#include <array>
#include <iostream>
#include <iomanip>
#include <string>

int main() {
    std::string name = "FOOBAR";
    auto max_gain = 0.15f;
    auto max_loss = 0.76f;

    std::cout << "Weekly Changes: " << name
        << " +" << (max_gain * 100) << "%"
        << " -" << (max_loss * 100) << "%"
        << "\n";
    // prints "Weekly Changes: FOOBAR +15% -76%"

    // Print list as a right-aligned list of hex values
    std::array some_numbers { 123456, 90346873, 28 };

    std::ios state(nullptr);
    state.copyfmt(std::cout);

    for (auto num: some_numbers) {
        std::cout << "\t0x";
        std::cout << std::hex << std::uppercase << std::setw(8)
            << std::setfill('0') << num;
        std::cout.copyfmt(state);
        std::cout << "\n";
    }
    /* Prints:
        0x0001E240
        0x05629579
        0x0000001C
    */
}