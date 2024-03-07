
#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <map>
#include <algorithm>
#include <numeric>
#include <stack>

/**
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/42586
 * 내가 생각한 풀이:
 * returns = [];
 * progressWithSpeed = Queue<pair<progress, speed>>();
 * while (queue.size() > 0) {
 *   queue.for_each { x => x.first += x.second }
 *   i = queue.find_index { x => x.first < 100 }
 *   if (i >= 0) {
 *     for (idx : 0..i) queue.pop(idx);
 *     returns.push_back(i);
	 }
 * }
 * return returns;
**/

using namespace std;

std::vector<int> solution(vector<int> progresses, vector<int> speeds) {
	auto progress_with_speeds = std::vector<std::pair<int, int>>();
	for (auto i = 0; i < progresses.size(); ++i) {
		progress_with_speeds.push_back(std::pair<int, int>(progresses[i], speeds[i]));
	}

	auto begin = std::begin(progress_with_speeds);
	auto end = std::end(progress_with_speeds);

	auto returns = std::vector<int>();
	while (begin != end) {
		std::for_each(begin, end, [](std::pair<int, int>& v) {
			v.first += v.second;
			});

		auto found = std::find_if(begin, end,
			[](const std::pair<int, int>& v) { return v.first < 100; });
		if (found != begin) {
			returns.push_back(std::distance(begin, found));
			begin = found;
		} else if (found == end) {
			begin = found;
		}
	}

	return returns;
}

int main() {
	auto r = solution({ 93, 30, 55 }, { 1, 30, 5 });
	for (auto& v : r) {
		std::cout << v << " ";
	}
	return 0;
}
