#pragma once

#include <string>
#include <vector>

/**
 * @brief Replace a portion of the string with a new value
 * 
 * @param in       The string to perform the replacement on
 * @param replace  The sub-string to replace
 * @param with     The value to replace the found sub-string with
 * @return std::string 
 */
std::string str_replace(std::string const &in, std::string const &replace, std::string const &with) {
    size_t n = in.find(replace);
    if (n == std::string::npos) {
        return in;
    }
    std::string out(in);
    out.replace(n, replace.length(), with.c_str());
    return out;
}

/**
 * @brief Replace all occurrences of a given value in the string with a new value
 * 
 * @param in      The string to perform the replacement on
 * @param replace The sub-string to replace
 * @param with    The value to replace the found sub-string with
 * @return std::string 
 */
std::string str_replace_all(std::string const &in, std::string const &replace, std::string const &with) {
    size_t n = in.find(replace);
    if (n == std::string::npos) {
        return in;
    }
    std::string out(in);
    do {
        out.replace(n, replace.length(), with.c_str());
        n = out.find(replace);
    } while (n != std::string::npos);
    return out;
}