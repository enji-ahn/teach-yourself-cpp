#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <iterator>
#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

/**
구명보트
문제 설명
무인도에 갇힌 사람들을 구명보트를 이용하여 구출하려고 합니다. 구명보트는 작아서
한 번에 최대 2명씩 밖에 탈 수 없고, 무게 제한도 있습니다.

예를 들어, 사람들의 몸무게가 [70kg, 50kg, 80kg, 50kg]이고 구명보트의 무게 제한이
100kg이라면 2번째 사람과 4번째 사람은 같이 탈 수 있지만 1번째 사람과 3번째
사람의 무게의 합은 150kg이므로 구명보트의 무게 제한을 초과하여 같이 탈 수
없습니다.

구명보트를 최대한 적게 사용하여 모든 사람을 구출하려고 합니다.

사람들의 몸무게를 담은 배열 people과 구명보트의 무게 제한 limit가 매개변수로
주어질 때, 모든 사람을 구출하기 위해 필요한 구명보트 개수의 최솟값을 return
하도록 solution 함수를 작성해주세요.

제한사항
무인도에 갇힌 사람은 1명 이상 50,000명 이하입니다.
각 사람의 몸무게는 40kg 이상 240kg 이하입니다.
구명보트의 무게 제한은 40kg 이상 240kg 이하입니다.
구명보트의 무게 제한은 항상 사람들의 몸무게 중 최댓값보다 크게 주어지므로
사람들을 구출할 수 없는 경우는 없습니다. 입출력 예 people	limit	return
[70, 50, 80, 50]	100	3
[70, 80, 50]	100	3
**/

/*
50 50 70 80
[50, 80] x
[50, 70] x
[50, 50] o
[70, 80] x
[70] o
[80] o
-----------
50, 70, 80
[50, 80] x
[50, 70] x
[50] o
[70, 80] x
[70] o
[80] o
*/

/*
성능
40, 55, 55, 60, 60, 60, 70, 80
->                          <-
^                   ^           // 1
  , 55, 55, 60, 60,   , 70, 80
    ^^                          // 1
cross 되었다면, cross 된 다음 index 부터 끝까지의 갯수 count
  ,   , 55, 60, 60,   , 70, 80  // 5

*/

using namespace std;

constexpr bool LOG_ON = true;

using taken = bool;

int solution(vector<int> people_, int limit) {
  int answer = 0;
  auto people = vector<pair<int, taken>>();
  for (auto& p : people_) { people.push_back(make_pair(p, false)); }

  sort(begin(people), end(people),
	  [](pair<int, taken> const& a, pair<int, taken> const& b) {
		  return b.first > a.first;
	  }
  );

  int from = 0;
  int rfrom = people.size() - 1;

  while (from < rfrom) {
      auto& first = people[from];
      auto& last = people[rfrom];
      if (first.first + last.first <= limit) {
          first.second = true;
          last.second = true;
          from++;
          rfrom--;
          answer++;
      }
      else {
          rfrom--;
      }
  }

  for (auto& p : people) {
      if (!p.second) answer++;
  }

  return answer ;
}

int main(int argc, char const *argv[]) {
    std::cout << "result -> " << solution({ 70, 80, 50 }, 100) << " expected -> "
        << 3 << std::endl;
    std::cout << "result -> " << solution({70, 50, 80, 50}, 100)
            << " expected -> " << 3 << std::endl;
  std::cout << "result -> " << solution({20, 60, 70, 80, 30}, 100)
            << " expected -> " << 3 << std::endl;
  std::cout << "result -> " << solution({40, 40, 40, 40, 50}, 200)
            << " expected -> " << 3 << std::endl;
  std::cout << "result -> " << solution({60, 60, 51, 51, 100}, 100)
            << " expected -> " << 5 << std::endl;
  std::cout << "result -> " << solution({40}, 40) << " expected -> " << 1
            << std::endl;
  std::cout << "result -> " << solution({40, 55, 55, 60, 60, 60, 70, 80}, 100)
            << " expected -> " << 7 << std::endl;
  std::cout << "result -> "
            << solution({10, 20, 30, 40, 50, 60, 70, 80, 90}, 100)
            << " expected -> " << 5 << std::endl;
  std::cout << "result -> " << solution({30, 40, 60, 70}, 100)
            << " expected -> " << 2 << std::endl;
  std::cout << "result -> " << solution({40, 50, 150, 160}, 200)
            << " expected -> " << 2 << std::endl;
  std::cout << "result -> " << solution({10, 50, 50, 90, 95}, 100)
            << " expected -> " << 3 << std::endl;
  std::cout << "result -> " << solution({30, 40, 50, 60}, 100)
            << " expected -> " << 2 << std::endl;
  std::cout << "result -> " << solution({40, 40, 40, 40}, 40) << " expected -> "
            << 4 << std::endl;
  std::cout << "result -> " << solution({40, 40, 40, 40, 40}, 40)
            << " expected -> " << 5 << std::endl;
  std::cout << "result -> " << solution({40, 50, 60, 90}, 100)
            << " expected -> " << 3 << std::endl;

  std::cout << "result -> " << solution({160, 150, 140, 60, 50, 40}, 200)
            << " expected -> " << 3 << std::endl;

  std::cout << "result -> " << solution({40, 40, 80}, 160) << " expected -> "
            << 2 << std::endl;
  return 0;
}
