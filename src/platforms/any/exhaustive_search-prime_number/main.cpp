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
 * 문제 :
 * https://school.programmers.co.kr/learn/courses/30/lessons/86491?language=cpp
 * --내 풀이 ---
 * 순열을 획득
 * 순열중에서 가장 큰 수 확인
 * `2 부터 가장 큰 수` 까지 나눠 가면서 소수(prime number) 인지 확인
 * 참고. 3 부터는 +2 씩 증가처리. (모든 짝수는 2 로 나눠지기 때문)
 */

using namespace std;

int solution(string numbers) {
  std::sort(std::begin(numbers), std::end(numbers));
  auto permutation = std::vector<int>();
  auto biggest = 0;

  do {
    auto i = std::stoi(numbers);
    permutation.push_back(i);
    biggest = (biggest < i) ? i : biggest;
  } while (next_permutation(std::begin(numbers), std::end(numbers)));

  std::cout << "biggest " << biggest << std::endl;

  auto inc = 1;
  for (auto i = 2; i < biggest; i += inc) {
    auto itr = std::begin(permutation);
    while (itr != std::end(permutation)) {
      // 현재 loop 값 으로 나눠서 나머지가 0 이라면, prime number 가 아님
      auto item = *itr;
      if (i < item && item % i == 0) {
        // permutation 에서 삭제
        itr = permutation.erase(itr);
      } else
        ++itr;
    }

    if (i == 2)
      inc = 2;
  }

  return permutation.size();
}

int main(int argc, char const *argv[]) {
  auto r = solution("17");
  std::cout << "expected " << 3 << " result -> " << r << std::endl;
  r = solution("011");
  std::cout << "expected " << 2 << " result -> " << r << std::endl;

  return 0;
}
