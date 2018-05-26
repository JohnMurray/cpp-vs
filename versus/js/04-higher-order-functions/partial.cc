#include <boost/hof.hpp>
#include <functional>

template<typename T>
T sum(T a, T b) {
    return a + b;
}

int main() {
    std::function<int(int)> addFiveInt = boost::hof::partial(
            BOOST_HOF_LIFT(sum)
        )(5);

    addFiveInt(10);
    // returns 15
}