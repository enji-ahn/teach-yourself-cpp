
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
#include <cassert>
#include <set>

/**
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/42628
 * ----
 * 내가 생각한 풀이 1차:
 * I 면 입력
 * D 면 삭제
 * 반복
 * Q 의 가장 최소와 최대 반환
 * ----

 * 
**/

using namespace std;


vector<int> solution(vector<string> operations) {
	auto dq = std::multiset<int>();

	for (auto& op : operations) {
		switch (op[0]) {
			case 'I':
			{
				auto n = std::stoi(op.substr(2, op.length() - 2));
				dq.insert(n);
				break;
			}
			case 'D':
			{
				if (dq.size() > 0) {
					if (std::stoi(op.substr(2, op.length() - 2)) < 0) { // 최소값 삭제
						dq.erase(dq.begin());
					}
					else { // 최대값 삭제
						dq.erase(--dq.end());
					}
				}
				break;
			}
			default: assert(false);
		}
	}

	if (dq.size() == 0) return { 0, 0 };
	else return { *dq.rbegin(), * dq.begin() };
}

int main() {
	//auto r = solution({ 12, 1, 2, 3, 9, 10, 12 }, 7);
	//auto r = solution({1, 1, 2, 6}, 24);
	//auto r = solution({"I 16", "I -5643", "D -1", "D 1", "D 1", "I 123", "D -1" });
	auto r = solution({ "I -45", "I 653", "D 1", "I -642", "I 45", "I 97", "D 1", "D -1", "I 333" });
	std::cout << "result : " << r[0] <<" "<<r[1]<< std::endl;
	return 0;
}
