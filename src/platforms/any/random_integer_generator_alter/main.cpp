#include <iostream>
#include <string>
#include <chrono>
#include <random>

std::size_t seed = std::chrono::system_clock::now().time_since_epoch().count();

namespace user {
	std::size_t rand()
	{
		static std::mt19937 mt(seed);
		return mt();
	}
}

int main(void)
{
	std::cout<<"random value : "<<user::rand()<<std::endl;

    return EXIT_SUCCESS;
}
