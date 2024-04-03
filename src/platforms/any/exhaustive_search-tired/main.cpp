#include <algorithm>
#include <any>
#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <set>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

/**
 * 문제 :
 * https://school.programmers.co.kr/learn/courses/30/lessons/87946
 * --내 풀이 ---
 * 순열을 획득
 * 만약 모든 던전을 탐색했다면, 더이상 확인하지 않고, 리턴
 */

using namespace std;

int solution(int k, vector<vector<int>> dungeons) {
  auto cmp = [](const vector<int> &a, const vector<int> &b) -> bool {
    return a[0] < b[0] ? true : a[1] < b[1];
  };
  std::sort(std::begin(dungeons), std::end(dungeons), cmp);

  for (auto &dungeon : dungeons) {
    std::cout << "[" << dungeon[0] << "," << dungeon[1] << "] ";
  }
  std::cout << std::endl << "--------------------" << std::endl;

  int answer = 0;
  do {
    int tiredness = k;
    int pass = 0;

    for (auto &dungeon : dungeons) {
      std::cout << "[" << dungeon[0] << "," << dungeon[1] << "] ";
    }
    std::cout << std::endl;

    for (auto &dungeon : dungeons) {
      if (tiredness < dungeon[0])
        break;
      tiredness -= dungeon[1];
      pass++;
    }

    if (pass > answer)
      answer = pass;
  } while (std::next_permutation(std::begin(dungeons), std::end(dungeons)));

  return answer;
}

int main(int argc, char const *argv[]) {
  auto r = solution(80, {{80, 20}, {50, 40}, {30, 10}});
  std::cout << "expected " << 3 << " result -> " << r << std::endl;

  return 0;
}
