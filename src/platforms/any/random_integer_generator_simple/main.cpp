#include <iostream>
#include <string>
#include <ctime>

namespace user {
    std::size_t rand()
    {
        return random();
    }
}

int main(void)
{
    std::size_t seed = time(nullptr);
    srandom(seed);

    std::cout<<"random value : "<<user::rand()<<std::endl;
    return EXIT_SUCCESS;
}
