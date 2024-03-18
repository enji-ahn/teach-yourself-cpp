#include <any>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

/**
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/1845
 * --내 풀이 ---
 * 값들을 hash table 에 입력
 * std::min(hash_table.size(), 포켓몬 숫자 / 2 한 갯수) 를 취득
 *
 */

using namespace std;

int solution(vector<int> nums) {
  auto kind = std::map<int, vector<int>>();
  for (auto &n : nums) {
    if (kind.find(n) == std::end(kind)) {
      kind[n] = vector<int>();
    }
    kind[n].push_back(n);
  }

  return std::min(kind.size(), nums.size() / 2);
}

int main(int argc, char const *argv[]) {

  auto r = solution({3, 1, 2, 3});
  std::cout << "result : " << r << std::endl;

  return 0;
}
