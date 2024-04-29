#include <algorithm>
#include <any>
#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

/**
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/42842
 * 풀이 
 * ----
 * Leo는 카펫을 사러 갔다가 아래 그림과 같이 중앙에는 노란색으로 칠해져 있고 
 * ```````테두리 1줄````````은 갈색으로 칠해져 있는 격자 모양 카펫을 봤습니다.
 * 
 * WIPWIPWIPWIPWIPWIPWIP
 *
 * 24	, 24	, [8, 6] 값일때
 *
 * 안쪽에 들어가는값 이 만들어 질 수 있는 조건
1x1
2x1
2x2
3x1
3x2
3x3
5x4 = 20
5x5 25

	6x4 = 24

7x3 = 21
7x4 = 28


 * 바깥쪽에 들어가는 값 이 만들어 질 수 있는 조건
85 = 40 - 24 => 16
86 = 48 - 24 => 24

  **/
using namespace std;

#define SHOW_LOG false

vector<int> solution(int brown, int yellow) {
	auto ok = false;
	auto y_height = 0;
	auto b_width = 0;
	do {
		y_height++;
		for (auto j = 1; j <= y_height; ++j) {
			if (j * y_height == yellow) {
				auto y_width = (j > y_height) ? j : y_height;
				auto tmp_height = (j < y_height) ? j : y_height;

				// 테두리 ````1줄```` 체크
				auto b_ok = false;
				b_width = y_width + 2;
				if (b_width * (tmp_height + 2) - yellow == brown) {
					b_ok = true;
				}

				if (b_ok) {
					ok = true;
	
					if (j < y_height) {
						y_width = y_height;
						y_height = j;
					}

					break;
				}
			}
		}
	} while (!ok);

	return { b_width, y_height + 2 /*top, bottom line*/};
}

std::string join(std::vector<int> results) {
	auto r = std::string();
	for (auto& result : results) {
		r += std::to_string(result);
		r += ", ";
	}
	return r;
}

int main(int argc, char const* argv[]) {

	std::cout << "result -> " << join(solution(18, 6))
		<< " expected -> " << join({ 8, 3 }) << std::endl;
	std::cout << "result -> " << join(solution(10, 2))
		<< " expected -> " << join({ 4, 3 }) << std::endl;
	std::cout << "result -> " << join(solution(8, 1))
		<< " expected -> " << join({ 3, 3 }) << std::endl;
	std::cout << "result -> " << join(solution(24, 24))
		<< " expected -> " << join({ 8, 6 }) << std::endl;

	return 0;
}
