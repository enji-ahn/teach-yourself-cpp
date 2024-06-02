#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

/**
문제 설명
아래와 같이 5와 사칙연산만으로 12를 표현할 수 있습니다.

12 = 5 + 5 + (5 / 5) + (5 / 5)
12 = 55 / 5 + 5 / 5
12 = (55 + 5) / 5

5를 사용한 횟수는 각각 6,5,4 입니다. 그리고 이중 가장 작은 경우는 4입니다.
이처럼 숫자 N과 number가 주어질 때, N과 사칙연산만 사용해서 표현 할 수 있는 방법
중 N 사용횟수의 최솟값을 return 하도록 solution 함수를 작성하세요.

제한사항
N은 1 이상 9 이하입니다.
number는 1 이상 32,000 이하입니다.
수식에는 괄호와 사칙연산만 가능하며 나누기 연산에서 나머지는 무시합니다.
최솟값이 8보다 크면 -1을 return 합니다.
입출력 예
N	number	return
5	12	4
2	11	3

--------------
2 + 2 + 2 + 2 + 2 + (2/2)
22/2



--------------
2
--
2@2
2+2
2-2
2x2
2/2
--
22@2
22+2
22-2
22x2
22/2
(2+2)+2
(2+2)-2
(2+2)x2
(2+2)/2
(2-2)+2
(2-2)-2
(2-2)x2
(2-2)/2
(2x2)+2
(2x2)-2
(2x2)x2
(2x2)/2
(2/2)+2
(2/2)-2
(2/2)x2
(2/2)/2
--
222@2
222+2
222-2
222x2
222/2
((2+2)+2)+2
((2+2)+2)-2
((2+2)+2)x2
((2+2)+2)/2

**/

#define LOG_ON false
using namespace std;

int gen(int N, std::vector<int> prevs, int number, int expect) {
  if (number == 1 && N != expect)
    return gen(N, number + 1, expect);

  for (auto &p : prevs) {
    if (p + N == expect)
      return number;
    if (P - N == expect)
      return number;
    if (P * N == expect)
      return number;
    if (P / N == expect)
      return number;
  }
}

int solution(int N, int number) {
  int answer = gen(N, 1, number);
  return answer;
}

int main(int argc, char const *argv[]) {

  std::cout << "result -> " << solution(5, 12) << " expected -> " << 4
            << std::endl;
  std::cout << "result -> " << solution(2, 11) << " expected -> " << 3
            << std::endl;
  std::cout << "result -> " << solution(5, 2) << "expected -> " << 4
            << std::endl;
  std::cout << "result -> " << solution(2, 11) << "expected -> " << 3
            << std::endl;
  std::cout << "result -> " << solution(5, 5) << "expected -> " << 1
            << std::endl;
  std::cout << "result -> " << solution(5, 10) << "expected -> " << 2
            << std::endl;
  std::cout << "result -> " << solution(5, 31168) << "expected -> " << -1
            << std::endl;
  std::cout << "result -> " << solution(1, 1121) << "expected -> " << 7
            << std::endl;
  std::cout << "result -> " << solution(5, 1010) << "expected -> " << 7
            << std::endl;
  std::cout << "result -> " << solution(3, 4) << "expected -> " << 3
            << std::endl;
  std::cout << "result -> " << solution(5, 5555) << "expected -> " << 4
            << std::endl;
  std::cout << "result -> " << solution(5, 5550) << "expected -> " << 5
            << std::endl;
  std::cout << "result -> " << solution(5, 20) << "expected -> " << 3
            << std::endl;
  std::cout << "result -> " << solution(5, 30) << "expected -> " << 3
            << std::endl;
  std::cout << "result -> " << solution(6, 65) << "expected -> " << 4
            << std::endl;
  std::cout << "result -> " << solution(5, 2) << "expected -> " << 3
            << std::endl;
  std::cout << "result -> " << solution(5, 4) << "expected -> " << 3
            << std::endl;
  std::cout << "result -> " << solution(1, 1) << "expected -> " << 1
            << std::endl;
  std::cout << "result -> " << solution(1, 11) << "expected -> " << 2
            << std::endl;
  std::cout << "result -> " << solution(1, 111) << "expected -> " << 3
            << std::endl;
  std::cout << "result -> " << solution(1, 1111) << "expected -> " << 4
            << std::endl;
  std::cout << "result -> " << solution(1, 11111) << "expected -> " << 5
            << std::endl;
  std::cout << "result -> " << solution(7, 7776) << "expected -> " << 6
            << std::endl;
  std::cout << "result -> " << solution(7, 7784) << "expected -> " << 5
            << std::endl;
  std::cout << "result -> " << solution(2, 22222) << "expected -> " << 5
            << std::endl;
  std::cout << "result -> " << solution(2, 22223) << "expected -> " << 7
            << std::endl;
  std::cout << "result -> " << solution(2, 22224) << "expected -> " << 6
            << std::endl;
  std::cout << "result -> " << solution(2, 11111) << "expected -> " << 6
            << std::endl;
  std::cout << "result -> " << solution(2, 11) << "expected -> " << 3
            << std::endl;
  std::cout << "result -> " << solution(2, 111) << "expected -> " << 4
            << std::endl;
  std::cout << "result -> " << solution(2, 1111) << "expected -> " << 5
            << std::endl;
  std::cout << "result -> " << solution(9, 36) << "expected -> " << 4
            << std::endl;
  std::cout << "result -> " << solution(9, 37) << "expected -> " << 6
            << std::endl;
  std::cout << "result -> " << solution(9, 72) << "expected -> " << 3
            << std::endl;
  std::cout << "result -> " << solution(3, 18) << "expected -> " << 3
            << std::endl;
  std::cout << "result -> " << solution(2, 1) << "expected -> " << 2
            << std::endl;
  std::cout << "result -> " << solution(4, 17) << "expected -> " << 4
            << std::endl;
  std::cout << "result -> " << solution(4, 1936) << "expected -> " << 4
            << std::endl; // -> 44*44
  std::cout << "result -> " << solution(4, 3872) << "expected -> " << 6
            << std::endl; // -> (44+44)*44
  return 0;
}
