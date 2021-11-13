#include <iostream>
#include <string>
#include <vector>

using namespace std;

void func2() {
  try {
    throw std::runtime_error("TESTING NESTED EXCEPTION");
  } catch (std::exception &) {
    std::throw_with_nested(std::runtime_error("func2 failed"));
  }
}

void func1() {
  try {
    func2();
  } catch (std::exception &) {
    std::throw_with_nested(std::runtime_error("func1() failed"));
  }
}

void print_nested_exception(const std::exception_ptr &eptr = std::current_exception(), size_t level = 0) {
  static auto get_nested = [](const std::exception &e) -> std::exception_ptr {
    try {
      return dynamic_cast<const std::nested_exception &>(e).nested_ptr();
    } catch (const std::bad_cast &) {
      return nullptr;
    }
  };

  try {
    if (eptr)
      std::rethrow_exception(eptr);
  } catch (const std::exception &e) {
    std::cerr << std::string(level, ' ') << "exception: " << e.what() << std::endl;
    print_nested_exception(get_nested(e), level + 1);
  }
}

int main(int argc, char const *argv[]) {
  try {
    func1();
  } catch (const std::exception &) {
    print_nested_exception();
  }

  return 0;
}