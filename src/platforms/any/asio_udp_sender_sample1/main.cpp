#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <cstdint>
#include <cassert>
#include <memory>
#include <functional>
#include <asio.hpp>

const int port = 7013;

void on_sent(
    std::shared_ptr<asio::ip::udp::endpoint> ep_from,
	std::shared_ptr<std::vector<uint8_t>> buffer,
	std::error_code const& ec,
	std::size_t const& bytes_tranferred);

int main(void)
{
	std::cout<<"Enter"<<std::endl;

	asio::io_service io_service;
	asio::io_service::work worker(io_service);

	auto thread = std::shared_ptr<std::thread>(new std::thread([&io_service](){ io_service.run(); }));
	assert(thread != nullptr);


	auto socket = std::make_shared<asio::ip::udp::socket>(io_service, asio::ip::udp::endpoint(asio::ip::udp::v4(), 0));
	assert(socket != nullptr);

	auto buffer = std::make_shared<std::vector<uint8_t>>();
	assert(buffer != nullptr);

	std::string hello = "HELLO UDP WORLD";
	buffer->assign(hello.begin(), hello.end());

	auto ep_from = std::make_shared<asio::ip::udp::endpoint>(asio::ip::address::from_string("127.0.0.1"), port);
    assert(ep_from != nullptr);

	socket->async_send_to(
		asio::buffer(*buffer),
		*ep_from,
		std::bind(on_sent,
			ep_from,
			buffer, // prevent to loose reference count
			std::placeholders::_1 /* error_code */,
			std::placeholders::_2 /* bytes_transferred */));

	thread->join();

	std::cout<<"Exit"<<std::endl;
    return EXIT_SUCCESS;
}


void on_sent(
    std::shared_ptr<asio::ip::udp::endpoint> ep_from, // ep to response
	std::shared_ptr<std::vector<uint8_t>> buffer,
	std::error_code const& ec,
	std::size_t const& bytes_tranferred)
{
	if (ec)
	{
		std::cerr<<__func__<<"() error code : "<<ec.value()<<", message: "<<ec.message()<<std::endl;
		return ;
	}

	std::cout<<__func__<<"() sent "<<bytes_tranferred<<" bytes"<<std::endl;
}
