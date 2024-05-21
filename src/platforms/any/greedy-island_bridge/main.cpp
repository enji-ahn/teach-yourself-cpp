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
#include <numeric>
#include <set>

/**
섬 연결하기
---------
**문제 설명**
n개의 섬 사이에 다리를 건설하는 비용(costs)이 주어질 때, 최소의 비용으로 모든 섬이 
서로 통행 가능하도록 만들 때 필요한 최소 비용을 return 하도록 solution을 완성하세요.

다리를 여러 번 건너더라도, 도달할 수만 있으면 통행 가능하다고 봅니다. 
예를 들어 A 섬과 B 섬 사이에 다리가 있고, B 섬과 C 섬 사이에 다리가 있으면 
A 섬과 C 섬은 서로 통행 가능합니다.

**제한사항**
* 섬의 개수 n은 1 이상 100 이하입니다.
* costs의 길이는 ((n-1) * n) / 2이하입니다.
* 임의의 i에 대해, costs[i][0] 와 costs[i] [1]에는 다리가 연결되는 두 섬의 번호가 
  들어있고, costs[i] [2]에는 이 두 섬을 연결하는 다리를 건설할 때 드는 비용입니다.
* 같은 연결은 두 번 주어지지 않습니다. 또한 순서가 바뀌더라도 같은 연결로 봅니다. 
  즉 0과 1 사이를 연결하는 비용이 주어졌을 때, 1과 0의 비용이 주어지지 않습니다.
* 모든 섬 사이의 다리 건설 비용이 주어지지 않습니다. 이 경우, 두 섬 사이의 건설이 
  불가능한 것으로 봅니다.
* 연결할 수 없는 섬은 주어지지 않습니다.
* 
* 0,1 :1
* 1,3 :1
* 0,2 :2
* 1,2 :5
* 2,3 :8
*
* 0 -> 0,1 / 0,2 = (1+2) *
* 1 -> 0,1 / 1,3 / 1,2 = (1+1+5)
* 2 -> 0,2 / 1,2 / 2,3 = (2+5+8)
* 3 -> 1,3 / 2,3 = (1+8)
* 
* 0 ok, 1 ok, 2 ok, 3 nok
* 0-3 x 
* 1-3 1 *
* 2-3 8 
* 
* ------------------------------
*
* 0, 1: 5
* 0, 3: 2
* 0, 4: 3
* 1, 4: 1
* 3, 4: 10
* 1, 2: 2
* 2, 5: 3
* 4, 5: 4
* result : 11
* 
* 0 : 0,1 / 0,3 / 0,4 = (10)
* 1 : 0,1 / 1,4 / 1,2 = (8)
* 2 : 1,2 / 2,5 = (5) *
* 3 : 0,3 / 3,4 = (12)
* 4 : 0,4 / 1,4 / 3,4 / 4,5 = (18)
* 5 : 2,5 / 4,5 = (7)
* 
* 0 nok, 1 ok, 2 ok, 3 nok, 4 nok, 5 ok
* 0-1 : 5
* 1-4 : 1 *
* 1-2 : x
* 2-5 : 3
* 4-5 : 4
* 
* 0 nok, 1 ok, 2 ok, 3 nok, 4 ok, 5 ok
* 0-1 : 5
* 1-4 : x
* 1-2 : x
* 2-5 : 3
* 4-5 : 4
* 0-4 : 3 *
* 3-4 : 10
* 4-5 : 4
* 
* 0 ok, 1 ok, 2 ok, 3 nok, 4 ok, 5 ok
* 0-1 : 5
* 1-4 : x
* 1-2 : x
* 2-5 : 3
* 4-5 : 4
* 0-4 : x
* 3-4 : 10
* 4-5 : 4
* 0-3 : 2 *
* 
* 5
0, 1, 5
1, 2, 3
2, 3, 3
3, 1, 2
3, 0, 4
2, 4, 6
4, 0, 7
result : 15

0, 1, 5
0, 3, 4
0, 4, 7
=16
1, 2, 3
1, 3, 2
=5
2, 3, 3
2, 4, 6
=9

1, 2, 3

0, 1, 5
0, 3, 4
2, 4, 6
=5+4
0, 1, 2, 3

0, 4, 7
2, 4, 6
=5+4+6
* 
*/

using namespace std;

constexpr bool LOG_ON = true;
using island_no = int;

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    auto built = set<island_no>();

    for (auto& cost : costs) {
        if (cost[0] > cost[1]) std::swap(cost[0], cost[1]);
    }
    sort(begin(costs), end(costs), [](vector<int>const& a, vector<int>const& b) { return a[0] < b[0]; });

    map<island_no, vector<pair<island_no, int>>> islands;

    while (built.size() < n) {
        islands = map<island_no, vector<pair<island_no, int>>>();
        for (auto& cost : costs) {
            if (find(begin(built), end(built), cost[0]) != end(built) &&
                find(begin(built), end(built), cost[1]) != end(built)) continue;
            std::cout << "cost : " << cost[0] << "," << cost[1] << " : " << cost[2] << std::endl;
            islands[cost[0]].push_back(make_pair(cost[1], cost[2]));
        }
        std::cout << "------------" << std::endl;

        island_no key = -1;
        int min_val = INT32_MAX;
        for (auto& island_group : islands) {
            auto value = accumulate(begin(island_group.second), end(island_group.second), 0,
                [](int acc, pair<island_no, int>const& cur) {
                    return acc + cur.second;
                });
            if (min_val > value) {
                min_val = value;
                key = island_group.first;
            }
        }
        assert(key != -1);

        built.insert(key);
        for (auto& connected_island : islands[key]) {
            built.insert(connected_island.first);
        }
        answer += min_val;
    }

    return answer;
}

int main(int argc, char const* argv[]) {
	std::cout << "result -> " << solution(
		5,
		{ {0, 1, 5}, {1, 2, 3}, {2, 3, 3}, {3, 1, 2}, {3, 0, 4},{2, 4, 6},{4, 0, 7} })
		<< " expected -> " << 15 << std::endl;
    std::cout << "result -> " << solution(
        4,
        { {0, 1, 1},{0, 2, 2},{1, 2, 5},{1, 3, 1},{2, 3, 8} })
        << " expected -> " << 4 << std::endl;
    std::cout << "result -> " << solution(
		5,
		{ {0, 1, 1}, {3, 4, 1}, {1, 2, 2}, {2, 3, 4} })
		<< " expected -> " << 8 << std::endl;
	std::cout << "result -> " << solution(
		4,
		{ {0, 1, 5}, {1, 2, 3}, {2, 3, 3}, {1, 3, 2}, {0, 3, 4} })
		<< " expected -> " << 9 << std::endl;
	std::cout << "result -> " << solution(
		5,
		{ {0, 1, 1}, {3, 1, 1}, {0, 2, 2}, {0, 3, 2}, {0, 4, 100} })
		<< " expected -> " << 104 << std::endl;
	std::cout << "result -> " << solution(
		6,
		{ {0, 1, 5}, {0, 3, 2}, {0, 4, 3}, {1, 4, 1}, {3, 4, 10},{1, 2, 2},{2, 5, 3},{4, 5, 4} })
		<< " expected -> " << 11 << std::endl;
	std::cout << "result -> " << solution(
		5,
		{ {0, 1, 1}, {2, 3, 1}, {3, 4, 2}, {1, 2, 2}, {0, 4, 100} })
		<< " expected -> " << 6 << std::endl;
	std::cout << "result -> " << solution(
		5,
		{ {0, 1, 1}, {0, 4, 5}, {2, 4, 1}, {2, 3, 1}, {3, 4, 1} })
		<< " expected -> " << 8 << std::endl;
	std::cout << "result -> " << solution(
		5,
		{ {0, 1, 1}, {0, 2, 2}, {0, 3, 3}, {0, 4, 4}, {1, 3, 1} })
		<< " expected -> " << 8 << std::endl;
	return 0;
}
