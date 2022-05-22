#include <iostream>

template <class T> auto max(T const &a, T const &b) -> T const &;

namespace N {
struct I {
  I(int i) : v(i) {}
  int v;
};
auto operator<(I const &a, I const &b) -> bool { return a.v < b.v; }
} // namespace N

auto main() -> int { std::cout << max(N::I(7), N::I(42)).v << std::endl; }

template <class T> auto max(T const &a, T const &b) -> T const & {
  return a < b ? b : a;
}
