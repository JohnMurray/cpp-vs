#include <atomic>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>

using namespace std;
using vec_iter = std::vector<int>::iterator;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100);

    auto nums = vector<int>(4096);
    for (auto i = 0; i < nums.size(); i++) {
        nums[i] = dis(gen);
    }

    atomic<int> totalSum;
    vector<thread> threads;

    // divide into 1024 blocks
    int from = 0;
    int to = 1024;
    while (to < nums.size()) {
        from += 1024;
        to += 1024;
        threads.push_back(
            thread([&totalSum,
                    start = nums.begin() + from,
                    end   = nums.begin() + to   ]() -> void {
                int sum = 0;
                for (vec_iter cur = start; cur != end; cur++) {
                    sum += *cur;
                }
                totalSum.fetch_add(sum);
            })
        );
    }

    for (auto &t: threads) {
        t.join();
    }

    cout << "Total Sum: " << totalSum.load() << "\n";
}
