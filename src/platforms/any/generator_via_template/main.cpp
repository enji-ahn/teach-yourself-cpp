#include <iostream>
#include <string>
#include <ctime>
#include <functional>

template <class T, class GenFunc>
struct Gen : private GenFunc
{
	using value_type = T;

	explicit Gen(GenFunc func)
		: GenFunc(std::move(func))
	{
	} 

	T generate()
	{
		return GenFunc::operator()();
	}
};

struct Integer
{
	explicit Integer(int i) :
		v(i) {}

	friend std::ostream& operator<<(std::ostream& os, const Integer& i);
	Integer operator-(Integer i) const {
		Integer r = *this;
		r.v -= i.v;
		return r;
	}

	int v;
};

std::ostream& operator<<(std::ostream& os, const Integer& i)
{
	os<<i.v;

	return os;
}

template <class GenFunc>
auto make_gen_from(GenFunc&& func)
{
	return Gen<decltype(func()), GenFunc>(std::forward<GenFunc>(func));
}

template <class Integer>
auto make_range_gen(Integer lo, Integer hi)
{
	return make_gen_from([lo, hi]() {
						 return static_cast<Integer>(lo + rand() % (hi - lo));
						 });
}

int main(void)
{
	std::size_t seed = time(nullptr);
	srandom(seed);

	Integer lo(20);
	Integer hi(25);

	auto ranger = make_range_gen(hi, lo);
    std::cout<<"random value : "<<ranger()<<std::endl;

    return EXIT_SUCCESS;
}
