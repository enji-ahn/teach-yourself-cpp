#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <map>

/**
문제 설명
계속되는 폭우로 일부 지역이 물에 잠겼습니다. 
물에 잠기지 않은 지역을 통해 학교를 가려고 합니다. 
집에서 학교까지 가는 길은 m x n 크기의 격자모양으로 나타낼 수 있습니다.

아래 그림은 m = 4, n = 3 인 경우입니다.

H * * *
* * * *
* * * S

가장 왼쪽 위, 즉 집이 있는 곳의 좌표는 (1, 1)로 나타내고 가장 오른쪽 아래, 
즉 학교가 있는 곳의 좌표는 (m, n)으로 나타냅니다.

격자의 크기 m, n과 물이 잠긴 지역의 좌표를 담은 2차원 배열 puddles이 매개변수로 주어집니다. 
오른쪽과 아래쪽으로만 움직여 집에서 학교까지 갈 수 있는 최단경로의 개수를 1,000,000,007로 나눈 나머지를 
return 하도록 solution 함수를 작성해주세요.

제한사항
격자의 크기 m, n은 1 이상 100 이하인 자연수입니다.
m과 n이 모두 1인 경우는 입력으로 주어지지 않습니다.
물에 잠긴 지역은 0개 이상 10개 이하입니다.
집과 학교가 물에 잠긴 경우는 입력으로 주어지지 않습니다.
입출력 예
m	n	puddles	return
4	3	[[2, 2]]	4

--------------------------

H 1 2 3
4 5 6 7
8 9 0 S


             H
         /       \
        4         1
       / \       / \
      8   5    [5]  2
     /   / \       / \
    9  [9]  6    [6]  3
   /       / \         \
  0      [0]  7        [7]
 /             \
S               S

**/

#define LOG_ON false
using namespace std;

bool route(
	vector<vector<int>>const& map, 
	int x, 
	int y, 
	std::map<int, vector<vector<pair<int, int>>>>& routes
) {
	if (map[y][x] == 'S') return true;

	auto found_y = false;
	auto found_x = false;
	if (map.size() - 1 > y) {
		y++;
		found_y = route(map, x, y, routes);
		if (found_y) {
			if (routes.find(y * 100 + x) == end(routes)) {
				routes[y * 100 + x] = { {} };
			}
			auto& last = --(routes[y * 100 + x].end());
			last->push_back({ x, y });
		}
	}

	if (map[y].size() - 1 > x) {
		x++;
		found_x = route(map, x, y, routes);
		if (found_x) {
			if (routes.find(y * 100 + x) == end(routes)) {
				routes[y * 100 + x] = { {} };
			}
			auto idx = routes[y * 100 + x].size() - 1;
			auto& last = routes[y * 100 + x][idx];

			if (routes.find(y * 100 + (x + 1)) != end(routes)) {
				auto idx = routes[y * 100 + (x + 1)].size() - 1;
				auto& route = routes[y * 100 + (x + 1)][idx];
				for (auto& v : route) {
					last.push_back(v);
				}
			}
			last.push_back({ x, y });
		}
	}

	return found_y || found_x;
}

int solution(int m, int n, vector<vector<int>> puddles) {
	int answer = 0;
	auto map = vector<vector<int>>{};
	for (int h = 0; h < n; ++h) {
		map.push_back(vector<int>{});
		for (int w = 0; w < m; ++w) {
			map[h].push_back(1);
		}
	}
	map[0][0] = 'H';
	map[n - 1][m - 1] = 'S';

	for (auto& h : map) {
		for (auto& w : h) {
			std::cout << w << " ";
		}
		std::cout << std::endl;
	}

	//auto routes = vector<pair<int, int>>{};
	auto routes = std::map<int /*x*100+y*/, vector<vector<pair<int, int>>>>{};
	route(map, 0, 0, routes);
	return answer;
}

int main(int argc, char const* argv[]) {
	std::cout << "result -> " << solution(4, 3, { {2, 2} }) << " expected -> " << 4
		<< std::endl;
	return 0;
}
