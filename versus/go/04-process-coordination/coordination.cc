#include <atomic>
#include <iostream>
#include <thread>
#include <string>
#include <vector>

int main() {
    std::string msg = "Hello, World!";
    std::atomic_int index = -1;

    std::vector<std::thread> threads;
    for (auto i = 0; i < msg.length(); i++) {
        threads.push_back(std::thread([ii = i, c = msg[i], &index]() {
            while ((ii - 1) != index.load()) {
                // busy wait
            }
            std::cout << c;
            index.fetch_add(1);
        }));
    }

    for (auto &t: threads) {
        t.join();
    }
}