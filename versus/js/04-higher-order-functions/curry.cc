#include <iostream>
#include <boost/hof.hpp>
#include <functional>

using namespace std;
namespace hof = boost::hof;

int main()
{
	auto sum = [](auto a, auto b){
		return a + b;
	};

	auto biOp = [](auto a, auto b, auto c) {
		return a(b, c);
	};

	auto biOpCurried = hof::partial(biOp);
	auto plus = biOpCurried(sum);
	auto addFivePFive = plus(5.5);

	cout << addFivePFive(4.5) << endl; // ->10
}