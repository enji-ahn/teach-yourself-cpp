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
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/87694
 * --내 풀이 ---
 * 지형 영역을 1로 표시
 * 캐릭터의 시작 지점으로 부터 팔방을 확인하여 0인 값인 pos 를 탐색 helper queue 에 저장
 * 1인 값인 pos 는 다음에 탐색할 queue 에 저장
 * bfs 로 다음 depth 를 탐색할때, 해당 좌표의 8방을 확인했을때,
 *  이전 queue 에서 helper queue 에 저장해 둔 좌표가 있다면, 이어지는 outline 으로 판단
 *  만약 helper queue 에 저장해둔 좌표가 없다면, 현재 좌표는 outline 이 아님.
 * 현재 depth 탐색이 끝났다면, helper queue 를 비움.
 * 현재 지점으로 부터 팔방을 확인하여 0인 값인 pos 를 탐색 helper queue 에 저장.. 반복
 * 
 * 참고. 
 * 0 0 0 0 0 0 0 0 0
 * 0 x y 1 1 1 1 0 0
 * 0 z k 1 1 1 1 0 0
 * 0 1 1 1 1 1 1 0 0
 * 0 0 0 1 1 1 0 0 0
 * 0 0 0 0 1 1 0 0 0
 * 0 0 1 1 1 1 1 1 0
 * 0 0 1 1 1 1 1 1 0
 * 0 0 0 0 1 1 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 
 *  x 를 기준으로 보면 x 와 y 의 8방을 보면 겹치는 0 부분 존재
 *  x 를 기준으로 보면 x 와 z 의 8방을 보면 겹치는 0 부분 존재
 *  x 를 기준으로 보면 x 와 k 의 8방을 보면 겹치는 0 부분 부재
 */

using namespace std;

using x = int;
using y = int;
using x_offset = int;
using y_offset = int;

using steps = int;

#define LOG_ON true
#define LBX 0
#define LBY 1
#define RTX 2
#define RTY 3

int solution(vector<vector<int>> rectangle, int characterX, int characterY, int itemX, int itemY) {
	int answer = 0;

	auto w = 0;
	auto h = 0;
	for (auto& r : rectangle) {
		w = r[RTX]*2 + 2 > w ? r[RTX]*2 + 2 : w;
		h = r[RTY]*2 + 2> h ? r[RTY]*2 + 2 : h;
	}

	auto map = vector<vector<int>>(h);
	for (auto i = 0; i < h; ++i) {
		map[i] = vector<int>(w);
	}

	for (auto& r : rectangle) {
		for (auto x = r[LBX]*2; x <= r[RTX]*2; ++x) {
			for (auto y = r[LBY]*2; y <= r[RTY]*2; ++y) {
				map[y][x] = 1;
			}
		}
	}

	if (LOG_ON) {
		for (auto& row : map) {
			for (auto& col : row) {
				std::cout << col << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "---------------" << std::endl;
	}

	auto queue = std::queue<std::pair<y, x>>();
	queue.push({ characterY*2, characterX*2 });
	auto found = false;
	auto step = 0;
	auto dirs = std::vector<std::pair<y_offset, x_offset>>{
		{-1, -1}, {-1, 0}, {-1, 1}, //lt, t, rt
		{0, -1}, {0, 0}, {0, 1}, //l, c, r
		{1, -1}, {1, 0}, {1, 1}, //lb, b, rb
	};
	while (!found && !queue.empty()) {
		auto sibilings = queue.size();

		while (sibilings--) {
			auto pos = queue.front(); queue.pop();

			if (pos.second == itemX * 2 && pos.first == itemY * 2) {
				found = true;
				break;
			}

			// 8방에 0인 영역이 있다면, 외곽선임
			auto outline = false;
			for (auto& dir : dirs) {
				auto x_pos = pos.second + dir.second;
				auto y_pos = pos.first + dir.first;
				if (map[y_pos][x_pos] == 0) {
					outline = true;
					break;
				}
			}
			if (!outline) continue;

			// left
			if (pos.second - 1 >= 0 && map[pos.first][pos.second - 1] == 1) {
				queue.push({ pos.first, pos.second - 1 });
			}
			// top
			if (pos.first - 1 >= 0 && map[pos.first - 1][pos.second] == 1) {
				queue.push({ pos.first - 1, pos.second });
			}
			// bottom
			if (pos.first + 1 < map.size() && map[pos.first + 1][pos.second] == 1) {
				queue.push({ pos.first + 1, pos.second });
			}
			// right
			if (pos.second + 1 < map[0].size() && map[pos.first][pos.second + 1] == 1) {
				queue.push({ pos.first, pos.second + 1 });
			}

			map[pos.first][pos.second] = 9; // traversed
		}

		step++;
		if (step % 2 != 0) answer++;
	}


	return answer-1; // 이동 거리이기 때문에 -1 처리 (answer 는 칸 갯수 이기 때문)
}

int main(int argc, char const* argv[]) {
	std::cout << "result -> " << std::endl
		<< solution({ 
			{1, 1, 7, 4}, 
			{3, 2, 5, 5}, 
			{4, 3, 6, 9}, 
			{2, 6, 8, 8} 
		}, 1, 3, 7, 8)
		<< " exptected " << 17 << std::endl;
	std::cout << "result -> " << std::endl
		<< solution({ {1, 1, 8, 4}, {2, 2, 4, 9}, {3, 6, 9, 8}, {6, 3, 7, 7} }, 9, 7, 6, 1)
		<< " exptected " << 11 << std::endl;
	std::cout << "result -> " << std::endl
		<< solution({ {1, 1, 5, 7} }, 1, 1, 4, 7)
		<< " exptected " << 9 << std::endl;
	std::cout << "result -> " << std::endl
		<< solution({ {2, 1, 7, 5}, { 6, 4, 10, 10 } }, 3, 1, 7, 10)
		<< " exptected " << 15 << std::endl;
	std::cout << "result -> " << std::endl
		<< solution({ {2, 2, 5, 5}, { 1, 3, 6, 4 }, { 3, 1, 4, 6 } }, 1, 4, 6, 3)
		<< " exptected " << 10 << std::endl;

	return 0;
}

