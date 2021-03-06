#include <iostream>
#include <chrono>
#include <memory>
#include <boost/asio.hpp>

using namespace std;
namespace asio = ::boost::asio;

int main() {
	asio::io_context ioc;

	auto keepAliveTimer = make_shared<asio::steady_timer>(
            ioc, chrono::hours(11 * 24));

	auto quitAfterGreetingPersonToo =
        [keepAliveTimer](const boost::system::error_code& ec,
                         const string& name) {
            if (!ec) {
                cout << "Hello " << name << "!" << endl;

                keepAliveTimer->cancel();
            }
        };

	// timer begins to run now
	auto greetTimer = asio::steady_timer(ioc, chrono::seconds(1));

	// later we can attach the completion handler
	greetTimer.async_wait(bind(
		quitAfterGreetingPersonToo,
		std::placeholders::_1,
		"World"));

	ioc.run();
	return 0;
}
