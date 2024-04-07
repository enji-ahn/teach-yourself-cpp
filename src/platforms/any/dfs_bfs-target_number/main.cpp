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

/**
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/43165
 * --내 풀이 ---
 * 재귀적으로 돌면서, target 을 +/- 인 경우로 입력
 * 결과가 원하는 값이 아닌 경우 0 반환
 * 결과가 원하는 값인 경우 1 반환
 * 예)
 * initial : [] [1, 1, 1, 1]
 *   case odd  => [+1] [1, 1, 1]
 *     case odd  => [+1, +1] [1, 1]
 *     case even => [+1, -1] [1, 1]
 *       ...
 *   case even => [-1] [1,1 , 1]
 *     case odd  => [-1, +1] [1, 1]
 *     case even => [-1, -1] [1, 1]
 *       ...
 */

using namespace std;

int calc_queue(vector<int> queue, vector<int> numbers, int target) {
	if (numbers.size() == 0) {
		auto r = std::accumulate(std::begin(queue), std::end(queue), 0);
		return (r == target) ? 1 : 0;
	}

	auto item = numbers.back(); numbers.pop_back();
	auto pq = vector<int>(queue); pq.push_back(item);
	auto nq = vector<int>(queue); nq.push_back(-1 * item);
	auto p = calc_queue(pq, numbers, target);
	auto n = calc_queue(nq, numbers, target);
	return p + n;
}

int solution(vector<int> numbers, int target) {
	auto item = numbers.back(); numbers.pop_back();
	auto p = calc_queue({ item }, numbers, target);
	auto n = calc_queue({ -1 * item }, numbers, target);
	return p + n;
}

int main(int argc, char const* argv[]) {
	std::cout << "result -> " << solution({ 1, 1, 1, 1, 1 }, 3)
		<< " expected " << 5 << std::endl;
	std::cout << "result -> " << solution({ 4, 1, 2, 1 }, 4)
		<< " expected " << 2 << std::endl;

	return 0;
}
