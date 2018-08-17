#include <string>
#include <boost/algorithm/string_regex.hpp>
#include <boost/regex.hpp>

int main() {
    std::string msg = "Total Price -> [1.23]";

    boost::to_lower(msg);
    // msg is now "total price -> [1.23]"

    msg = "Total Price -> [1.23]";
    boost::to_upper(msg);
    // msg is now "TOTAL PRICE -> [1.23]"

    msg = "Total Price -> [1.23]";
    boost::replace_all(msg, "[", "(");
    boost::replace_all(msg, "]", ")");
    // msg is now "Total Prices -> (1.23)"

    msg = "Total Price -> [1.23]";    
    boost::replace_all_regex(msg, boost::regex("[\\[\\]\\->]"),
        std::string(""));
    // msg is not "Total Prices  1.23"
}
