#include <any>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

/**
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/42578
 * --내 풀이 ---
 *  종류별로 list 에 입력
 *  리스트 갯수 조합 반환
 *  예) h 2 e 1 f 3
 *  n => (2, 1, 3)
 *  nCr => 3C1 + 3C2 + 3C3
 *
 *  nCr => n! / (n - r)!r!
 */

using namespace std;

int solution(vector<vector<string>> clothes) {
  auto group = std::map<string /*kind*/, std::vector<string> /*clothes*/>();
  for (auto &cloth : clothes) {
    auto name = cloth[0];
    auto kind = cloth[1];
    if (group.find(kind) == std::end(group)) {
      group[kind] = std::vector<std::string>();
    }
    group[kind].push_back(name);
  }

  auto answer = 0;

  return answer;
}

int main(int argc, char const *argv[]) {

  auto r = solution({{"yellow_hat", "headgear"},
                     {"blue_sunglasses", "eyewear"},
                     {"green_turban", "headgear"}});
  std::cout << "expect : 5, result -> " << r << std::endl;

  auto r2 = solution({{"crow_mask", "face"},
                      {"blue_sunglasses", "face"},
                      {"smoky_makeup", "face"}});
  std::cout << "expect : 3, result -> " << r << std::endl;

  return 0;
}
