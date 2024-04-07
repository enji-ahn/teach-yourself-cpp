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
#include <numeric>
#include <algorithm>
#include <queue>

/**
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/1844
 * --내 풀이 ---
 * 목적지는 x 로 값을 치환
 * 재귀적으로 돌면서, 사방을 보면서 진행함.
 * 각 재귀 진입시다마 step 값 증가.
 * 지나온 길 체크 (backtracking?)
 * 목적지에 동작하면 step 값 반환.
 * 가장 작은값을 answer 로 선택
 * map[x] = visit
 * explore(map, cur_pos, step++)
 * map[x] = unvisit
 */

using namespace std;

using vertical = int;
using horizontal = int;

using found = bool;
using steps = int;

#define LOG_ON false

std::pair<found, steps> explore(vector<vector<int>>& maps, std::pair<vertical, horizontal> pos, int cur_steps) {
	cur_steps++;

	auto answer = 0;

	if (maps[pos.first][pos.second] == 100) {
		if (LOG_ON) std::cout << "found it!" << std::endl;
		return { true, cur_steps };
	}

	// left
	if (pos.second - 1 >= 0 && maps[pos.first][pos.second - 1]) {
		maps[pos.first][pos.second] = 0; // traversed
		if (LOG_ON) std::cout << "step [" << pos.first << "][" << pos.second << "]"
			<< "to [" << pos.first << "][" << pos.second - 1 << "]" << std::endl;
		auto result = explore(maps, { pos.first, pos.second - 1 }, cur_steps);
		if (result.first) {
			if (!answer) answer = result.second;
			else answer = (result.second < answer) ? result.second : answer;
		}
		maps[pos.first][pos.second] = 1; // un-traversed
	}
	// top
	if (pos.first - 1 >= 0 && maps[pos.first - 1][pos.second]) {
		maps[pos.first][pos.second] = 0; // traversed
		if (LOG_ON) std::cout << "step [" << pos.first << "][" << pos.second << "]"
			<< "to [" << pos.first - 1 << "][" << pos.second << "]" << std::endl;
		auto result = explore(maps, { pos.first - 1, pos.second }, cur_steps);
		if (result.first) {
			if (!answer) answer = result.second;
			else answer = (result.second < answer) ? result.second : answer;
		}
		maps[pos.first][pos.second] = 1; // un-traversed
	}
	// bottom
	if (pos.first + 1 < maps.size() && maps[pos.first + 1][pos.second]) {
		maps[pos.first][pos.second] = 0; // traversed
		if (LOG_ON) std::cout << "step [" << pos.first << "][" << pos.second << "]"
			<< "to [" << pos.first + 1 << "][" << pos.second << "]" << std::endl;
		auto result = explore(maps, { pos.first + 1, pos.second }, cur_steps);
		if (result.first) {
			if (!answer) answer = result.second;
			else answer = (result.second < answer) ? result.second : answer;
		}
		maps[pos.first][pos.second] = 1; // un-traversed
	}
	// right
	if (pos.second + 1 < maps[0].size() && maps[pos.first][pos.second + 1]) {
		maps[pos.first][pos.second] = 0; // traversed
		if (LOG_ON) std::cout << "step [" << pos.first << "][" << pos.second << "]"
			<< "to [" << pos.first << "][" << pos.second + 1 << "]" << std::endl;
		auto result = explore(maps, { pos.first, pos.second + 1 }, cur_steps);
		if (result.first) {
			if (!answer) answer = result.second;
			else answer = (result.second < answer) ? result.second : answer;
		}
		maps[pos.first][pos.second] = 1; // un-traversed
	}

	if (LOG_ON) {
		if (!answer) {
			std::cout << "no route to explore" << std::endl;
		}
	}

	return (!answer) ? std::pair{ false, -1 } : std::pair{ true, answer };
}

int solution_dfs(vector<vector<int>> maps)
{
	auto pos = std::pair<vertical, horizontal>(maps.size() - 1, maps[0].size() - 1);
	if (LOG_ON) std::cout << "step to [" << pos.first << "][" << pos.second << "]" << std::endl;

	maps[pos.first][pos.second] = 100; // target

	auto result = explore(maps, { 0, 0 }, 0);

	return (!result.first) ? -1 : result.second;
}

int solution_bfs_slow(vector<vector<int>> maps) {
	auto step = 0;

	auto pos = std::pair<vertical, horizontal>(maps.size() - 1, maps[0].size() - 1);
	maps[pos.first][pos.second] = 9; // target
	auto found = false;

	auto queue = std::queue<std::vector<std::pair<vertical, horizontal>>>();
	queue.push({ { 0, 0 } });

	while (!queue.empty()) {
		auto& list = queue.front();
		auto next_list = std::vector<std::pair<vertical, horizontal>>();

		for (auto& pos : list) {
			if (maps[pos.first][pos.second] == 9) {
				found = true;
				step++;
				break;
			}

			// left
			if (pos.second - 1 >= 0 && maps[pos.first][pos.second - 1]) {
				next_list.push_back({ pos.first, pos.second - 1 });
			}
			// top
			if (pos.first - 1 >= 0 && maps[pos.first - 1][pos.second]) {
				next_list.push_back({ pos.first - 1, pos.second });
			}
			// bottom
			if (pos.first + 1 < maps.size() && maps[pos.first + 1][pos.second]) {
				next_list.push_back({ pos.first + 1, pos.second });
			}
			// right
			if (pos.second + 1 < maps[0].size() && maps[pos.first][pos.second + 1]) {
				next_list.push_back({ pos.first, pos.second + 1 });
			}

			maps[pos.first][pos.second] = 0; // traversed
		}

		if (next_list.size()) queue.push(next_list);
		if (found) break;

		if (LOG_ON) {
			for (auto& a : maps) {
				for (auto& b : a) {
					std::cout << b << " ";
				}
				std::cout << std::endl;
			}
			std::cout << "----" << std::endl;
		}

		step++;

		queue.pop();
	}

	return found ? step : -1;
}

int solution(vector<vector<int>> maps) {
	auto depth = 0;

	auto pos = std::pair<vertical, horizontal>(maps.size() - 1, maps[0].size() - 1);
	maps[pos.first][pos.second] = 9; // target
	auto found = false;

	auto queue = std::queue<std::pair<vertical, horizontal>>();
	queue.push({ 0, 0 });

	while (!found && !queue.empty()) {
		
		auto step = queue.size();

		while (step--) {
			auto pos = queue.front(); queue.pop();

			// 이미 확인한 영역은, 재 확인하지 않도록 처리. 
			// 다음과 같을때, 1 인 영역이 함께 겹치는 부분이 x 임
			// 0 1
			// 1 x
			// 이 상황에서 x 가 중복 탐색되지 않도록 처리.
			if (!maps[pos.first][pos.second]) {
				continue;
			}

			if (maps[pos.first][pos.second] == 9) {
				found = true;
				break;
			}

			// left
			if (pos.second - 1 >= 0 && maps[pos.first][pos.second - 1]) {
				queue.push({ pos.first, pos.second - 1 });
			}
			// top
			if (pos.first - 1 >= 0 && maps[pos.first - 1][pos.second]) {
				queue.push({ pos.first - 1, pos.second });
			}
			// bottom
			if (pos.first + 1 < maps.size() && maps[pos.first + 1][pos.second]) {
				queue.push({ pos.first + 1, pos.second });
			}
			// right
			if (pos.second + 1 < maps[0].size() && maps[pos.first][pos.second + 1]) {
				queue.push({ pos.first, pos.second + 1 });
			}

			maps[pos.first][pos.second] = 0; // traversed
		}

		if (!LOG_ON) {
			for (auto& a : maps) {
				for (auto& b : a) {
					std::cout << b << " ";
				}
				std::cout << std::endl;
			}
			std::cout << "----" << std::endl;
		}

		depth++;
	}

	return found ? depth : -1;
}

int main(int argc, char const* argv[]) {
	std::cout << "result -> " << std::endl << solution({
		{1, 0, 1, 1, 1},
		{1, 0, 1, 0, 1},
		{1, 0, 1, 1, 1},
		{1, 1, 1, 0, 1},
		{0, 0, 0, 0, 1} })
		<< " expected " << 11 << std::endl;

	std::cout << "result -> " << solution({
		{1, 0, 1, 1, 1},
		{1, 0, 1, 0, 1},
		{1, 0, 1, 1, 1},
		{1, 1, 1, 0, 0},
		{0, 0, 0, 0, 1} })
		<< " exptected " << -1 << std::endl;

	return 0;
}

