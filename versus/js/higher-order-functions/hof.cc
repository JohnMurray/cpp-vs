#include <functional>

template<typename T>
T sum(T a, T b) {
    return a + b;
}

template<typename T, typename U>
std::function<U (T)> collect(std::function<U (U, U)> fn, U init) {
    return [fn, init](T list) -> U {
        U out = init;
        for (auto const &l: list) {
            out = fn(out, l);
        }
        return out;
    };
}

int main() {
    auto sumListInt = collect<std::vector<int>, int>(sum<int>, 0);
    auto multListInt = collect<std::vector<int>, int>(
        [](int a, int b) -> int {
            return a * b;
        }, 1);

    sumListInt(std::vector<int> {{1, 2, 3, 4}});
    // returns 10

    multListInt(std::vector<int> {{1, 2, 3, 4}});
    // returns 24
}