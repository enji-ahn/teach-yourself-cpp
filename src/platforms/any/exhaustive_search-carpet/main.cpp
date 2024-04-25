#include <algorithm>
#include <any>
#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

/**
 * WIPWIPWIPWIPWIPWIPWIP
 *
 * 24	, 24	, [8, 6] 값일때
 *
 * 안쪽에 들어가는값 이 만들어 질 수 있는 조건
1x1
2x1
2x2
3x1
3x2
3x3
5x4 = 20
5x5 25

    6x4 = 24

7x3 = 21
7x4 = 28


 * 바깥쪽에 들어가는 값 이 만들어 질 수 있는 조건
85 = 40 - 24 => 16
86 = 48 - 24 => 24

  **/
using namespace std;

#define SHOW_LOG false

using score = int;
using name = int;

std::string join(std::vector<int> results) {
  auto r = std::string();
  for (auto &result : results) {
    r += std::to_string(result);
    r += ", ";
  }
  return r;
}

int main(int argc, char const *argv[]) {
  std::cout << "result -> " << join(solution({1, 2, 3, 4, 5}))
            << " expected -> " << join({1}) << std::endl;
  std::cout << "result -> " << join(solution({1, 3, 2, 4, 2}))
            << " expected -> " << join({1, 2, 3}) << std::endl;

  return 0;
}
