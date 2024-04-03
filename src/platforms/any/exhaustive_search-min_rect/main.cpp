#include <algorithm>
#include <any>
#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

/**
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/42839
 * --내 풀이 ---
 * 결과값을 {a/큰값/, b/작은값/} 형태로 저장
 * list 를 순회
 * element 값중 큰 값이 결과값 a 보다 크다면 치환
 * element 값중 작은 값이 결과값 b 보다 크다면 치환
 * return a*b
 */

using namespace std;

using big = int;
using small = int;

int solution(vector<vector<int>> sizes) {
    auto result = std::pair<big, small>(0, 0);
    big b;
    small s;

    for (auto& size: sizes) {
      std::tie(b, s) = (size[0] > size[1]) ? std::pair(size[0], size[1]) : std::pair(size[1], size[0]);
      result.first = (b > result.first) ? b : result.first;
      result.second = (s > result.second) ? s : result.second;
    }

    return result.first * result.second;
}

int main(int argc, char const *argv[]) {
  auto r1 = solution({{60, 50}, {30, 70}, {60, 30}, {80, 40}});
  std::cout<<"expected "<<4000<<" result -> "<<r1<<std::endl;
  auto r2 = solution({{10, 7}, {12, 3}, {8, 15}, {14, 7}, {5, 15}});
  std::cout<<"expected "<<120<<" result -> "<<r2<<std::endl;
  auto r3 = solution({{14, 4}, {19, 6}, {6, 16}, {18, 7}, {7, 11}});
  std::cout<<"expected "<<133<<" result -> "<<r3<<std::endl;

  return 0;
}
