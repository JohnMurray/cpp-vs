#include <iostream>
#include <chrono>
#include <memory>
#include <boost/asio.hpp>

using namespace std;
namespace asio = ::boost::asio;

int main() {
	asio::io_context ioc;

	auto stepTimer = asio::steady_timer(ioc, chrono::seconds(1));

	stepTimer.async_wait([&ioc](const boost::system::error_code& ec) {
		if (!ec) {
			cout << "That's one small step for a man," << flush;

			auto leapTimer = make_shared<asio::steady_timer>(
                    ioc, chrono::seconds(1));

			// WITHOUT CAPTURING leapTimerPtr the handler would be
            // invoked IMMEDIATELY with non-zero error code
			leapTimer->async_wait(
                [leapTimer](const boost::system::error_code& ec) {
                    if (!ec) {
                        cout << " one giant leap for mankind." << endl;
                    }
                });
		}
	});

	ioc.run();
	return 0;
}
