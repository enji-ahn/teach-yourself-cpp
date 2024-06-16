#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <map>

/**
문제 설명

    7
   3 8
  8 1 0
 2 7 4 4
4 5 2 6 5

2  7  4  4
45 52 26 65
위와 같은 삼각형의 꼭대기에서 바닥까지 이어지는 경로 중, 거쳐간 숫자의 합이 가장 큰 경우를 찾아보려고 합니다. 아래 칸으로 이동할 때는 대각선 방향으로 한 칸 오른쪽 또는 왼쪽으로만 이동 가능합니다. 예를 들어 3에서는 그 아래칸의 8 또는 1로만 이동이 가능합니다.

삼각형의 정보가 담긴 배열 triangle이 매개변수로 주어질 때, 거쳐간 숫자의 최댓값을 return 하도록 solution 함수를 완성하세요.

제한사항
삼각형의 높이는 1 이상 500 이하입니다.
삼각형을 이루고 있는 숫자는 0 이상 9,999 이하의 정수입니다.

**/

#define LOG_ON false
using namespace std;

int solution(vector<vector<int>> triangle) {
	int answer = 0;

	for (auto i = triangle.size() - 1; i > 0; --i) {
		auto& upper_line = triangle[i - 1];
		auto& line = triangle[i];
		for (auto j = 0; j < upper_line.size(); j++) {
			auto upper_value = upper_line[j];
			auto choose = max(line[j] + upper_value, line[j + 1] + upper_value);
			upper_line[j] = choose;
		}

		if (LOG_ON) {
			for (auto& l : triangle) {
				for (auto& v : l) {
					std::cout << v << " ";
				}
				std::cout << std::endl;
			}
		}
	}

	return triangle[0][0];
}

int main(int argc, char const* argv[]) {
	std::cout << "result -> " << solution(
		{ {7},{3, 8},{8, 1, 0},{2, 7, 4, 4},{4, 5, 2, 6, 5} }
	) << " expected -> " << 30
		<< std::endl;
	return 0;
}
