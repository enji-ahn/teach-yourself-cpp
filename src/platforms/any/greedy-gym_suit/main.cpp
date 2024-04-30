#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/42862
 * 풀이 :
 * reserve 인 학생 앞, 뒤가 lost 에 있다면, lost 에서 삭제
 * 전체 n 에서 lost 인 갯수를 뺀 수가 체육 할 수 있는 수
 *
 * 주의 :
 * 여벌 체육복을 가져온 학생이 체육복을 도난당했을 수 있습니다.
 * 이때 이 학생은 체육복을 하나만 도난당했다고 가정하며,
 * 남은 체육복이 하나이기에 다른 학생에게는 체육복을 빌려줄 수 없습니다.
 */
int solution(int n, vector<int> lost, vector<int> reserve) {
  // (5, {5, 3}, {4, 2}) 케이스 처리를 위해 정렬
  std::sort(std::begin(lost), std::end(lost));
  std::sort(std::begin(reserve), std::end(reserve));

  // 여벌 체육복을 가져온 학생이 체육복을 도난당한 경우 처리
  for (auto i = std::begin(lost); i != std::end(lost); ++i) {
    auto v = *i;
    auto f = std::find(std::begin(reserve), std::end(reserve), v);
    if (f != std::end(reserve)) {
      reserve.erase(f);
      lost.erase(i);
      i--;
    }
  }

  for (auto &r : reserve) {
    auto f = std::find(std::begin(lost), std::end(lost), r - 1);
    if (f != std::end(lost)) {
      lost.erase(f);
    } else {
      f = std::find(std::begin(lost), std::end(lost), r + 1);
      if (f != std::end(lost)) {
        lost.erase(f);
      }
    }
  }

  return n - lost.size();
}

int main(int argc, char const *argv[]) {

  std::cout << "result -> " << solution(5, {5, 3}, {4, 2}) << " expected -> "
            << 5 << std::endl;
  std::cout << "result -> " << solution(5, {2, 4}, {1, 3, 5}) << " expected -> "
            << 5 << std::endl;
  std::cout << "result -> " << solution(5, {2, 4}, {3}) << " expected -> " << 4
            << std::endl;
  std::cout << "result -> " << solution(3, {3}, {1}) << " expected -> " << 2
            << std::endl;

  return 0;
}
