#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

/**
 * @brief 문제 :
https://school.programmers.co.kr/learn/courses/30/lessons/42883?language=cpp
 * 문제 설명
어떤 숫자에서 k개의 수를 제거했을 때 얻을 수 있는 가장 큰 숫자를 구하려 합니다.

예를 들어, 숫자 1924에서 수 두 개를 제거하면 [19, 12, 14, 92, 94, 24] 를 만들 수
있습니다. 이 중 가장 큰 숫자는 94 입니다.

문자열 형식으로 숫자 number와 제거할 수의 개수 k가 solution 함수의 매개변수로
주어집니다. number에서 k 개의 수를 제거했을 때 만들 수 있는 수 중 가장 큰 숫자를
문자열 형태로 return 하도록 solution 함수를 완성하세요.

제한 조건
number는 2자리 이상, 1,000,000자리 이하인 숫자입니다.
k는 1 이상 number의 자릿수 미만인 자연수입니다.
입출력 예
number	k	return
"1924"	2	"94"
"1231234"	3	"3234"
"4177252841"	4	"775841"
 * ----
 * 4177252841
 * expected no => number of char (10) - k (4) => 6
 * keep last 6 char -> 4177'252841'
 * if first is less then privious number, then remove it -> 417'752841'
 * if first is equal to privious numer, then make largest number -> 41'775841'
(sequencly remove min numbers from '7752841'. 775284, 775841, 775281, ...)
 * if privious numer is lessthn first, then remove it -> 4'775841'
 * if privious numer is lessthn first, then remove it -> '775841'
 *
 *
 * 4177252841
 * 177252841
 * 477252841
 * 417252841
 * 417252841
 * 417752841
 * 417722841
 * 417725841
 * 417725241
 * 417725281
 * 417725284
 *
 * 477252841
 * 77252841
 * 47252841
 * 47252841
 * 47752841
 * 47722841
 * 47725841
 * 47725241
 * 47725281
 *
 * 77252841
 * 7252841
 * 7252841
 * 7752841
 * 7722841
 * 7725841
 * 7725241
 * 7725284
 *
 * 7752841
 * 752841
 * 752841
 * 772841
 * 775841
 * 775241
 * 775281
 **/

#define LOG_ON false
using namespace std;

std::string find_rm_index_more_bigger(std::string const &answer) {
  // 3124 에서 known_rm_idx 가 0 이라면, 3을 제외한 124 와
  // (3)124, 3(1)24, 31(2)4, 312(4) 를 비교해서 값이 커지는 삭제 index 를
  // 반환합니다.
  auto values = std::vector<std::pair<int /*index*/, std::string /*value*/>>();
  for (auto rm_idx = 0; rm_idx < answer.size(); ++rm_idx) {
    auto value = std::string();
    for (auto i = 0; i < answer.size(); ++i) {
      if (i != rm_idx)
        value.push_back(answer[i]);
    }
    if (LOG_ON)
      std::cout << "comparing => " << value << std::endl;
    values.push_back(std::make_pair(rm_idx, value));
  }

  std::sort(
      std::begin(values), std::end(values),
      [](std::pair<int, std::string> const &a,
         std::pair<int, std::string> const &b) { return a.second > b.second; });

  return values[0].second;
}

string solution(string number, int k) {
  auto answer = std::string(number.begin() + k, number.end());
  if (LOG_ON)
    std::cout << "answer : " << answer << std::endl;
  for (auto i = k - 1; i >= 0; --i) {
    if (LOG_ON)
      std::cout << i << "th => " << number[i] << std::endl;
    auto val = answer.front();
    auto compare = number[i];
    if (val < compare) {
      // 더 큰 값으로 치환
      *(std::begin(answer)) = compare;

      if (LOG_ON)
        std::cout << "answer ?= " << answer << std::endl;
    } else if (val == compare) {
      // 값이 같다면, 가지고 있는 값중에서 만들어질 수 가장 큰 값을 취함.
      // 그리고 새로운 값을 0 번 index 에 prepend
      answer = compare + find_rm_index_more_bigger(answer);
      if (LOG_ON)
        std::cout << "answer ?! " << answer << std::endl;
    }
  }

  return std::string(std::begin(answer), std::end(answer));
}

int main(int argc, char const *argv[]) {
  std::cout << "result -> " << solution("1924", 2) << " expected -> "
            << "94" << std::endl;
  std::cout << "result -> " << solution("1231234", 3) << " expected -> "
            << "3234" << std::endl;
  std::cout << "result -> " << solution("4177252841", 4) << " expected -> "
            << "775841" << std::endl;
  std::cout << "result -> " << solution("190000002", 3) << " expected -> "
            << "900002" << std::endl;
  std::cout << "result -> " << solution("3879781299", 2) << " expected -> "
            << "89781299" << std::endl;
  std::cout << "result -> " << solution("4321", 1) << " expected -> "
            << "432" << std::endl;

  return 0;
}
