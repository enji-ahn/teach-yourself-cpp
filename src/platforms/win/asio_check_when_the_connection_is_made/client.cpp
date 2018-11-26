#include "pch.h"

using namespace boost::asio;
using namespace boost::asio::ip;

io_service client_ioservice;
tcp::socket client_socket{ client_ioservice };

void work_as_client(unsigned short port)
{
	tcp::endpoint ep(tcp::endpoint(address::from_string("127.0.0.1"), port));

	client_socket.connect(ep);
	std::cout << "connected" << std::endl;
}