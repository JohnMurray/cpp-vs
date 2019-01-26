#include <algorithm>
#include <functional>
#include <vector>

int main() {
    std::function<int(int)> addOne = [](int x) -> int {
        return x + 1;
   };

   addOne(5);
   // returns 6

    // use lambda as value, do in-place modification
    std::vector<int> v = {1, 2, 3, 4, 5};
    std::transform(v.begin(), v.end(), v.begin(),
        addOne);
    // new value of 'v' is [2, 3, 4, 5, 6]
}