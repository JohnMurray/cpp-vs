#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>

void sendEmail(std::string to, std::string from, std::string subject,
               std::string body,
               std::function<void(std::string)> success_cb,
               std::function<void(std::string)> failure_cb) {
    if (std::rand() > 0.5) {
        success_cb(to);
    } else {
        failure_cb(to);
    }
}

int main() {
    sendEmail("you@your_domain.com", "me@my_domain.com",
        "Very Important Email",
        "TODO: remember to write email body. :-D",
        [](std::string to) -> void {
            std::cout << "Successful email sent to: " << to << "\n";
        },
        [](std::string to) -> void {
            std::cout << "OH NO! Very important email not sent to " << to << "\n";
        });
}