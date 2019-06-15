#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <cassert>
#include <boost/make_shared.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

const int port = 7003;

void on_sent(
    boost::shared_ptr<boost::asio::ip::udp::endpoint> ep_from,
	boost::shared_ptr<std::vector<uint8_t>> buffer,
	boost::system::error_code const& ec,
	std::size_t const& bytes_tranferred);

int main(void)
{
	std::cout<<"Enter"<<std::endl;

	boost::asio::io_service io_service;
	boost::asio::io_service::work worker(io_service);

	auto thread = std::shared_ptr<std::thread>(new std::thread([&io_service](){ io_service.run(); }));
	assert(thread != nullptr);


	auto socket = boost::make_shared<boost::asio::ip::udp::socket>(
		io_service,
		boost::asio::ip::udp::endpoint());
	assert(socket != nullptr);

	auto buffer = boost::make_shared<std::vector<uint8_t>>();
	assert(buffer != nullptr);

	std::string hello = "HELLO UDP WORLD";
	buffer->assign(hello.begin(), hello.end());

	auto ep_from = boost::make_shared<boost::asio::ip::udp::endpoint>(
		    boost::asio::ip::udp::v4(),
		    port);
    assert(ep_from != nullptr);

	socket->async_send_to(
		boost::asio::buffer(*buffer),
		*ep_from,
		boost::bind(on_sent,
			ep_from,
			buffer, // prevent to loose reference count
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));


	thread->join();

	std::cout<<"Exit"<<std::endl;
    return EXIT_SUCCESS;
}


void on_sent(
    boost::shared_ptr<boost::asio::ip::udp::endpoint> ep_from, // ep to response
	boost::shared_ptr<std::vector<uint8_t>> buffer,
	boost::system::error_code const& ec,
	std::size_t const& bytes_tranferred)
{
	if (ec)
	{
		std::cerr<<__func__<<"() error code : "<<ec.message()<<std::endl;
		return ;
	}

	std::cout<<__func__<<"() sent "<<bytes_tranferred<<" bytes"<<std::endl;
}
