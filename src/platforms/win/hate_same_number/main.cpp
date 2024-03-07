
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
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/12906
 * 내가 생각한 풀이: 
 * stack = Stack()
 * while(value in list) {
 *   if (stack.size == 0) stack.push(value)
 *   elif (stack.last != value) stack.push(value)
 * }
 * stack.toList()
**/

std::vector<int> solution(std::vector<int> arr) {
	auto stack = std::vector<int>();
	for (auto& v : arr) {
		if (stack.empty() || stack.back() != v)
			stack.push_back(v);
	}
	return stack;
}

int main() {
	auto r = solution({ 1, 1, 3, 3, 0, 1, 1 });
	for (auto& v : r) {
		std::cout << v << " ";
	}
	return 0;
}
