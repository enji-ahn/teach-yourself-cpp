
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
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/42584
 * 내가 생각한 풀이:
 * queue 에서 하나씩 뽑아가면서 B queue (value, time)에 넣음.
 * queue 에서 뽑을때 값이마다, B queue 의 값보다 크다면 time 을 1씩 누적함.
**/

using namespace std;


vector<int> solution(vector<int> prices) {
	vector<int>::iterator point = prices.begin();

	while (point != prices.end()) {
		int time = 1;
		auto cur = (point + 1);
		for (cur; cur != prices.end(); ++cur) {
			if (*point <= *cur) time++;
			else break;
		}
		if (cur == prices.end()) time--;

		*point = time;
		point++;
	}

	return prices;
}

int main() {
	auto r = solution({ 4, 5, 1, 2, 6, 1, 1 });
	std::cout << "result : "; // 2, 1, 4, 2, 1, 1, 0
	for (auto& i : r) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
	return 0;
}
