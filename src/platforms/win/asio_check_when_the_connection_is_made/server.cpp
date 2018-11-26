#include "pch.h"

using namespace boost::asio;
using namespace boost::asio::ip;

io_service server_ioservice;
tcp::socket server_socket{ server_ioservice };
io_service::work server_worker{ server_ioservice };

boost::shared_ptr<tcp::acceptor> server_acceptor;

static void accept_handler(const boost::system::error_code &ec)
{
	if (ec)
	{
		std::cout << "failed to accept data : " << ec.message() << std::endl;
		return;
	}

	boost::this_thread::sleep_for(boost::chrono::seconds(10));

	std::cout << "connected. "<< std::endl;
}

void work_as_server(unsigned short port)
{
	tcp::endpoint ep{ tcp::v4(), port };
	server_acceptor = boost::make_shared<tcp::acceptor>(server_ioservice, ep);

	server_acceptor->listen();

	auto io_thread = boost::make_shared<boost::thread>([=]() { server_ioservice.run(); });

	server_acceptor->async_accept(server_socket, accept_handler);

	io_thread->join();
}