#include <boost/asio.hpp>
#include <csignal>
#include <iostream>

#define BOOST_THREAD_VERSION 4
#include <boost/thread/future.hpp>

using namespace std;
namespace asio = ::boost::asio;

int main() {
	asio::io_context ioContext;

	auto shutdown = [&](const boost::system::error_code& ec, int signal_number) {
		if (!ec) {
			terminationSignals.cancel();
		}
	});

	asio::signal_set terminationSignals(ioContext, SIGINT, SIGTERM);

	terminationSignals.async_wait(shutdown);

	asio::post(io, [&](){
		cout << "Hello World!" << endl;
	});

	// Since this method blocks it should
	// be the last line in the main thread.
	ioContext.run();

	return 0;
}

