// asio_listen_stopped_by_io_service.cpp : This file contains the 
// 'main' function. Program execution begins and ends there.
//

// asio 를 사용해서 async_accept 를 호출해 놓은 상황에서,
// io_service.stop() 을 호출했다면, on_accept 가 error 로 호출되는지 확인

#include "pch.h"
#include <iostream>
#include "asio_listen_stopped_by_io_service.h"

using namespace boost::asio;
using namespace boost::asio::ip;

io_service service;

int main()
{
	auto listener = start_listen_thread();

	for (int i = 0; i < 10; ++i)
	{
		boost::this_thread::sleep(boost::posix_time::seconds(1));
		std::cout << "passed " << i + 1 << " sec" << std::endl;
	}

	if (!service.stopped())
	{
		service.stop();
	}
	else 
	{
		std::cout << "service already stopped" << std::endl;
	}
	
	listener->join();

	std::getchar();
}

boost::shared_ptr<boost::thread> start_listen_thread()
{
	tcp::endpoint ep{ tcp::v4(), 30338 };
	auto acceptor = boost::make_shared<tcp::acceptor>(service, ep);
	_ASSERT(acceptor != nullptr);
	acceptor->listen();

	auto socket = boost::make_shared<tcp::socket>(service);
	_ASSERT(socket != nullptr);

	acceptor->async_accept(*socket,
		boost::bind(on_accept,
			placeholders::error,
			acceptor,
			socket));

	auto io_thread = boost::make_shared<boost::thread>([=]() {
		std::cout << "io_service run" << std::endl;
		service.run();
		std::cout << "io_service stopped" << std::endl;
	});
	_ASSERT(io_thread != nullptr);

	return io_thread;
}

void on_accept(
	boost::system::error_code const & ec,
	boost::shared_ptr<tcp::acceptor> acceptor,
	boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
{
	if (ec)
	{
		std::cout
			<< "failed : "
			<< ec.message()
			<< std::endl;
		return;
	}

	std::cout 
		<< "connected from : " 
		<< socket->remote_endpoint().address().to_string() 
		<< std::endl;

	std::cout << "wait connection again" << std::endl;
	socket = boost::make_shared<tcp::socket>(service);
	_ASSERT(socket != nullptr);

	acceptor->async_accept(*socket,
		boost::bind(on_accept,
			placeholders::error,
			acceptor,
			socket));
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or 
//      Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to 
//      File > Open > Project and select the .sln file
