#include <string>
#include <string_view>

int main() {
    std::string greeting = "Hello";
    std::string to       = "World";

    std::string msg = greeting + ", " + to;
    // msg is a new string of "Hello, World"
    
    std::string_view view(msg);
    // create a "view" into the string

    view.substr(0, 5);
    // returns new string_view of "Hello"

    view.substr(7);
    // returns new string_view of "World!"
}
