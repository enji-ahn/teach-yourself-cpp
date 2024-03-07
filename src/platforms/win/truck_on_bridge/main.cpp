
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
#include <list>
#include <queue>

/**
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/42583
 * 내가 생각한 풀이:
 * beidge_length 크기의 queue
 * weight 를 넘지 않도록 push
 * 매 turn 마다 queue 에서 한칸씩 전진
 * queue 가 비었을때, 진행된 turn 수를 반환
**/

using namespace std;


int solution(int bridge_length, int weight, vector<int> truck_weights) {
	auto bridge = std::list<std::pair<int/*index*/, int/*truck_weight*/>>();
	auto sum = [](std::list<std::pair<int/*index*/, int/*truck_weight*/>>& trucks) -> int {
		return std::accumulate(std::begin(trucks), std::end(trucks), 0,
			[](int& acc, std::pair<int, int>& v) -> int {
				return acc + v.second; 
			}); 
		};
	auto turn = 0;
	auto cur = std::begin(truck_weights);
	auto end = std::end(truck_weights);
	do {
		for (auto itr = std::begin(bridge); itr != std::end(bridge); ) {
			itr->first--;
			if (itr->first <= 0) itr = bridge.erase(itr);
			else itr++;
		}

		if (cur != end && sum(bridge) + *cur <= weight) {
			bridge.push_back(std::pair<int, int>(bridge_length, *cur));
			cur++;
		}
		turn++;
	} while (cur != end || bridge.size());

	return turn;
}

int main() {
	//auto r = solution(100, 100, {10, 10, 10, 10, 10, 10, 10, 10, 10, 10});
	auto r = solution(2, 10, { 7, 4, 5, 6 });
	std::cout << "result : " << r << std::endl;
	return 0;
}
