
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
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/12909
 * 내가 생각한 풀이:
 * stack = Stack()
 * for (auto value : string.chars()) {
 *   if (value == '(' && stack.top == ')') stack.pop()
 *   elif (value == ')' && stack.top == '(') stack.pop()
 * }
 * return stack.empty()
**/

using namespace std;

bool solution(string s)
{
	auto stack = std::stack<char>();

	for (char v : s) {
		if (!stack.empty() && v == '(' && stack.top() == ')') stack.pop();
		else if (!stack.empty() && v == ')' && stack.top() == '(') stack.pop();
		else stack.push(v);

		if (stack.size() == 1 && stack.top() == ')') return false;
	}

	return stack.empty();
}

int main() {
	auto r = solution({ "())((()))(()" });
	std::cout << "result : " << r << std::endl;
	return 0;
}
