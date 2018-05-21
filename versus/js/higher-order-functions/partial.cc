#include <boost/hof.hpp>
#include <functional>

template<typename T>
T sum(T a, T b) {
    return a + b;
}

int main() {
    std::function<int(int)> addFive = boost::hof::partial(
            BOOST_HOF_LIFT(sum<int>)
        )(5);

    addFive(10);
    // returns 15
}