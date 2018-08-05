#include <algorithm>
#include <string>

int main() {
    std::string msg = " \t\n\t Hello, World! \t\n\t ";

    auto ltrim = [](std::string &in) {
        in.erase(in.begin(), std::find_if(in.begin(), in.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    };

    auto rtrim = [](std::string &in) {
        in.erase(std::find_if(in.rbegin(), in.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), in.end());
    };

    auto trim = [&](std::string &in) {
        ltrim(in);
        rtrim(in);
    };

    trim(msg);
    // msg is not "Hello, World!"
}
