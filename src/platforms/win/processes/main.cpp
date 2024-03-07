
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
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/42587
 * 내가 생각한 풀이:
 * 환형큐를 만들고, 큐에서 모두 뽑힐때까지
 * 높은 순서대로 가져옴.
 * 만약 뽑아온 값의 pid 가 location 과 같다면, 해당 전체 뽑아온 갯수(index 가 되겠져?) 를 반환
**/

using namespace std;


int solution(vector<int> priorities, int location) {
	auto pid_with_priority = std::list<std::pair<int/*prio*/, int/*pid*/>>();
	for (auto i = 0; i < priorities.size(); ++i) {
		pid_with_priority.push_back(std::pair<int, int>(priorities[i], i));
	}

	auto answer = std::queue<std::pair<int/*prio*/, int/*pid*/>>();
	auto begin = std::begin(pid_with_priority);
	for (auto i = 9; pid_with_priority.size(); --i) {
		auto end = std::end(pid_with_priority);

		auto next_begin = begin;
		auto search_to = begin;

		for (auto itr = begin; itr != end;) {
			if (itr->first == i) {
				answer.push(*itr);
				if (itr->second == location) return answer.size();
				auto need_update_search_to = itr == search_to;
				itr = pid_with_priority.erase(itr);
				next_begin = itr;
				if (need_update_search_to) search_to = itr;
			}
			else itr++;
		}

		for (auto itr = std::begin(pid_with_priority); itr != search_to;) {
			if (itr->first == i) {
				answer.push(*itr);
				if (itr->second == location) return answer.size();
				itr = pid_with_priority.erase(itr);
				next_begin = itr;
			}
			else itr++;
		}

		begin = next_begin;
	}
}

int main() {
	auto r = solution({ 1, 1, 9, 1, 1, 1 }, 0);
	std::cout << "result : " << r << std::endl;
	return 0;
}
