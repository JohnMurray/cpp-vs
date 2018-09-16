#include <boost/asio.hpp>
#include <csignal>
#include <iostream>

#define BOOST_THREAD_VERSION 4
#include <boost/thread/future.hpp>

using namespace std;
namespace asio = ::boost::asio;

int main() {
	asio::io_context ioc;

	asio::signal_set terminationSignals(ioc, SIGINT, SIGTERM);

	auto shutdown = [&](const boost::system::error_code& ec, int ) {
		if (!ec) {
			terminationSignals.cancel();
		}
	};

	terminationSignals.async_wait(shutdown);

	asio::post(ioc, [](){
		cout << "Hello World!" << endl;
	});

	cout << "setup done." << endl;

	// This method blocks the main thread.
	ioc.run();

	cout << "exiting..." << endl;

	return 0;
}

