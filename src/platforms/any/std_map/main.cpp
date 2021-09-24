#include <any>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

using namespace std;

int main(int argc, char const *argv[]) {
  // {abc: {
  //     abd: {
  //         hahah: hahah
  //     },
  //     hello: [1, 2, 3]
  // }}

  std::unordered_map<std::string, std::string> abd;
  abd["hahah"] = "hahah";

  std::unordered_map<std::string, std::any> abc;
  abc["abd"] = abd;
  abc["hello"] = std::vector<int>{1, 2, 3};

  std::unordered_map<std::string, std::any> dic;
  dic["abc"] = abc;

  auto abc_ = std::any_cast<std::unordered_map<std::string, std::any>>(dic["abc"]);
  auto hello_ = std::any_cast<std::vector<int>>(abc_["hello"]);
  std::cout << hello_[2] << std::endl;
  auto abd_ = std::any_cast<std::unordered_map<std::string, std::string>>(abc_["abd"]);
  std::cout << abd_["hahah"] << std::endl;

  return 0;
}