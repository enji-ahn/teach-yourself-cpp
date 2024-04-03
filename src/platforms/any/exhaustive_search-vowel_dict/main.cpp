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
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/84512
 *
 * 입출력 예 #1
 *  사전에서 첫 번째 단어는 "A"이고, 그다음은 "AA", "AAA", "AAAA", "AAAAA",
 *  "AAAAE", ... 와 같습니다. "AAAAE"는 사전에서 6번째 단어입니다.
 *
 * 입출력 예 #2
 *  "AAAE"는 "A", "AA", "AAA", "AAAA", "AAAAA", "AAAAE", "AAAAI", "AAAAO",
 *  "AAAAU"의 다음인 10번째 단어입니다.
 * --내 풀이 ---
 * 규칙
 * 1. max length 가 되지 않았는데, 값이 A 만 있다면, max length 가 될때까지 A 를
 *    채운다.
 * 2. max length 가 되지 않았는데, 중간에 값이 A 가 아닌 항목이 있다면 max
 *    length 가 될때까지 해당 항목 이후를 A 로 채운다.
 * 3. max length 까지 채워져 있다면, 가장 마지막 값을 증가한다.
 * 4. 마지막 값이 U 였다면, 이전 index 의 값을 증가시키고 마지막 값은 빈 값으로
 *    처리한다.
 *   * 이후 2로 진행
 */

using namespace std;

class StrangeNumber {
public:
  StrangeNumber()
      : number(""), num_map({{'A', 'E'}, {'E', 'I'}, {'I', 'O'}, {'O', 'U'}}),
        count(0) {}

  StrangeNumber operator++(int) {
    StrangeNumber temp = *this;

    if (number.size() < 5) {
      auto notA = std::find_if(std::begin(number), std::end(number),
                               [](const char v) { return v != 'A'; });
      if (notA == std::end(number)) { // number has all 'A'
        number += 'A';
      } else { // not all 'A'
        number += 'A';
      }
    } else {
      auto ritr = number.rbegin();
      auto round_up = number.size();
      while (ritr != number.rend()) {
        // std::cout << "number : " << number << std::endl;
        if (*ritr == 'U') {
          *ritr = 'x'; // x mean end of string
          round_up--;
          ritr++;
        } else {
          *ritr = num_map[*ritr];
          break;
        }
      }

      if (round_up) {
        number.resize(round_up);
      }
    }

    count++;

    return temp;
  }

  int count;
  std::string number;

private:
  std::map<char, char> num_map;
};

int solution(string word) {
  StrangeNumber sn;
  while (sn.number != word) {
    sn++;
  }
  return sn.count;
}

int main(int argc, char const *argv[]) {
  std::cout << "result -> " << solution("AAAAE") << " expected " << 6
            << std::endl;
  std::cout << "result -> " << solution("AAAE") << " expected " << 10
            << std::endl;
  std::cout << "result -> " << solution("I") << " expected " << 1563
            << std::endl;
  std::cout << "result -> " << solution("EIO") << " expected " << 1189
            << std::endl;

  return 0;
}
