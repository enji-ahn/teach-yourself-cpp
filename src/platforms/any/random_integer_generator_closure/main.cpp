#include <iostream>
#include <string>
#include <ctime>

/**
 * @brief : lo ~ hi 값을 반환하는 함수(람다 함수 객체) 를 반환함.
 */
auto make_range_generator(int lo, int hi)
{
	return [lo, hi]() {
		return lo + rand() % (hi - lo + 1);
	};
}

int main(void)
{
    std::size_t seed = time(nullptr);
    srandom(seed);

	auto ranger = make_range_generator(20, 25);
	for (int i = 0; i < 10; ++i)
	{
		std::cout<<"random value "<<i<<" th : "<<ranger()<<std::endl;
	}

    return EXIT_SUCCESS;
}
