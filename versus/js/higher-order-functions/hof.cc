// TODO: Not sure if this import is right
// #include <boost/hof.hpp>
#include <functional>

template<typename T>
T sum(T a, T b) {
    return a + a;
}

template<typename T, typename U>
std::function<U (T)> collect(std::function<U (U, U)> fn, U init) {
    return [&fn](T list) -> U {
        U out;
        for (auto const &l: list) {
            out = fn(out, l);
        }
        return out;
    };
}

int main() {
    // TODO: call sumList and multList
    auto sumList = collect<std::vector<int>, int>(sum, 0);
}