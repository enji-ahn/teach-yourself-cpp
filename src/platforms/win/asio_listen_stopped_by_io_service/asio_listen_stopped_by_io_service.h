#pragma once

int main();

boost::shared_ptr<boost::thread>
start_listen_thread();

void 
on_accept(
	boost::system::error_code const& ec,
	boost::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor,
	boost::shared_ptr<boost::asio::ip::tcp::socket> socket
);
