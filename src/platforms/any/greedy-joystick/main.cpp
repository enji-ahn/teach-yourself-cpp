#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

/**
 * @brief 문제 :
 * 풀이 ----
 * 1. 왼쪽으로 움직이는 경우, 오른쪽으로 움직이는 경우 2가지로 확인
 * 2. 미지의 알파벳 x 가 a-> 부터 찾는게 빠른지, <- z 부터 찾는게 빠른지 확인
 *    (26 - (x - 'a'))
 *
 */

using namespace std;

int solution2(string name) {
  int answer = 0;
  auto len = name.size();
  auto from = std::string();

  from.assign(len, 'A');

  std::cout << "from " << from << std::endl;

  auto straight = 0;
  auto reveresd = 0;

  for (auto i = 0; i < len; ++i) {
    if (from == name)
      break;
    auto x = name[i];
    auto diff_from_a = x - 'A';
    auto diff_from_z = 'Z' - x;
    auto r =
        (diff_from_a < diff_from_z) ? 'A' + diff_from_a : 'Z' - diff_from_z;
    from[i] = r;

    straight += std::min(diff_from_a, diff_from_z);
    straight++;
  }

  std::cout << "changed " << from << std::endl;

  return answer;
}

int solution(string name) {
  int answer = 0;
  int len = name.size();
  auto from = std::string();

  from.assign(len, 'A');

  std::cout << "from " << from << std::endl;

  for (auto i = 0; i > (len * -1); --i) {
    if (from == name) {
      std::cout << "equal " << std::endl;
      break;
    }
    std::cout << "i : " << i << " len " << len << std::endl;
    auto index = (i < 0) ? len + i : i;
    std::cout << "index " << index << std::endl;
    auto x = name[index];
    auto diff_from_a = x - 'A';
    auto diff_from_z = 'Z' - x;
    auto r =
        (diff_from_a < diff_from_z) ? 'A' + diff_from_a : 'Z' - diff_from_z;
    from[index] = r;

    answer += std::min(diff_from_a, diff_from_z);
    answer++;
  }

  std::cout << "changed " << from << std::endl;

  return answer;
}

int main(int argc, char const *argv[]) {

  std::cout << "result -> " << solution("JAZ") << " expected -> " << 11
            << std::endl;
  std::cout << "result -> " << solution("JEROEN") << " expected -> " << 56
            << std::endl;
  std::cout << "result -> " << solution("JAN") << " expected -> " << 23
            << std::endl;

  return 0;
}
