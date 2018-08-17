#include <functional>

template<typename T>
std::function<T(T)> addX(T x) {
    return [x](T n) -> T {
        return n + x;
    };
}

int main() {
    auto addFive = addX<int>(5);

    addFive(10);
    // returns 15
}