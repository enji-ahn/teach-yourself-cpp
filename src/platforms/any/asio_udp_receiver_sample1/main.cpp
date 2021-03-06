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

void on_recv(
    std::shared_ptr<asio::ip::udp::socket> socket,
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

	auto socket = std::make_shared<asio::ip::udp::socket>(
		io_service,
        asio::ip::udp::endpoint(
		    asio::ip::udp::v4(),
		    port));
	assert(socket != nullptr);

	auto buffer = std::make_shared<std::vector<uint8_t>>(10); // 10 byte length
	assert(buffer != nullptr);

	auto ep_from = std::make_shared<asio::ip::udp::endpoint>();
    assert(ep_from != nullptr);

	socket->async_receive_from(
		asio::buffer(*buffer),
		*ep_from,
		std::bind(on_recv,
            socket,
            ep_from,
			buffer,
			std::placeholders::_1 /*error code*/,
			std::placeholders::_2 /*bytes_transferred*/));


	thread->join();

	std::cout<<"Exit"<<std::endl;
    return EXIT_SUCCESS;
}


void on_recv(
    std::shared_ptr<asio::ip::udp::socket> socket, // local socket
    std::shared_ptr<asio::ip::udp::endpoint> ep_from, // ep to response
	std::shared_ptr<std::vector<uint8_t>> buffer, // received buffer
	std::error_code const& ec,
	std::size_t const& bytes_tranferred)
{
	if (ec)
	{
		std::cerr<<__func__<<"() error code : "<<ec.message()<<std::endl;
		return ;
	}

	std::cout<<__func__<<"() recv "<<bytes_tranferred<<" bytes"<<std::endl;

    std::string message(buffer->begin(), buffer->end());
    std::cout<<__func__<<"() received message : "<<message<<std::endl;


    socket->async_receive_from(
		asio::buffer(*buffer),
		*ep_from,
		std::bind(on_recv,
            socket,
            ep_from,
			buffer,
			std::placeholders::_1 /*error_code*/,
			std::placeholders::_2 /*bytes_transferred*/));

}
