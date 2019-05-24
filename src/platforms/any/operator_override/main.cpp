#include <iostream>
#include <string>
#include <ctime>

class Integer {
public:
    explicit Integer(int i) : v{i} {}
    Integer operator+(Integer const& p) {
        return Integer(v + p.v);
    }
    Integer operator+(int const& p) {
        return Integer(v + p);
    }
    Integer operator-(Integer const& p) {
        return Integer(v - p.v);
    }
    friend Integer operator%(int const& p, Integer const& i) {
        return Integer(p % i.v);
    }
    friend std::ostream& operator<<(std::ostream& os, const Integer& i) {
        os<<i.v;
	    return os;
	}
private:
    int v;
};

int main(void)
{
    Integer i{3};
    Integer j(5);

    Integer k = i + j;

    std::cout<<i<<"+"<<j<<"="<<k<<std::endl;

	std::size_t seed = time(nullptr);
	srandom(seed);

    Integer r = static_cast<Integer>(i + rand());
    std::cout<<r<<"=rand()"<<std::endl;

    Integer l = static_cast<Integer>(rand() % j);
    std::cout<<l<<"=rand() / "<<j<<std::endl;

    Integer m = static_cast<Integer>(i + rand() % (i - j));
    std::cout<<m<<"=between "<<i<<" , "<<j<<std::endl;

    return EXIT_SUCCESS;
}
