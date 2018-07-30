#include <iostream>
#include <boost/hof.hpp>
#include <functional>
#include <vector>

using namespace std;
namespace hof = boost::hof;

template<typename T>
vector<T> concat(const vector<T>& a, const vector<T>& b) {
	vector<T> ret(a.cbegin(), a.cend());
	ret.insert(ret.end(), b.cbegin(), b.cend());
	return ret;
}

// --- Example with vanilla Currying ---
auto curry2 = [](auto func) {
	return [=](auto x) {
		return [=](auto y) {
			return func(x, y);
		};
	};
};

int main()
{
	auto concatCurried = curry2(concat<int>);
	auto prepend012 = concatCurried(vector<int>{0, 1, 2});

	prepend012(vector<int>{7, 8, 9});
	// returns  [0, 1, 2, 7, 8, 9]

	// --- Example with Auto-Currying ---
	auto sum = [](auto a, auto b){
		return a + b;
	};

	auto biOp = [](auto func, auto a, auto b) {
		return func(a, b);
	};

	auto biOpCurried = hof::partial(biOp);
	auto plus = biOpCurried(sum);
	auto addFivePFive = plus(5.5);

	addFivePFive(4.5);
	// returns 10
}