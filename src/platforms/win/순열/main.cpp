
#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <map>

/// <summary>
/// 파라메터로 전달된 string vector 를 하나의 문자열로 합쳐서 반환합니다.
/// </summary>
/// <param name="sv"></param>
/// <returns></returns>
static std::string join(std::vector<std::string> sv, int until = 0) {
	std::string result;
	for (const auto& s : sv) {
		if (!--until) break;
		result += s;
	}
	return result;
}

static std::string join(std::vector<int> nv, int until = 0) {
	std::string result;
	for (const auto& n : nv) {
		if (!--until) break;
		result += std::to_string(n);
	}
	return result;
}

// 생각한 방법 : 
//   앞자리 순서로 배열후 조합한다.
//   앞자리가 같은 숫자 그룹은 순열을 통해서 가장 큰 값으로 만든다.

int main() {
	std::map<int, std::vector<int>> nmap;
	auto candidates = std::vector<std::string>(10); 
	std::vector<int> sv = { 3, 30, 34, 5, 9 };
	
	// 앞자리가 같은 숫자 그룹으로 분류
	for (auto& s : sv) nmap[std::to_string(s)[0] - '0'].push_back(s);

	// 2개 이상 아이템이 있는 그룹의 경우, 정렬
	for (auto& m : nmap) {
		auto& numbers = m.second;
		if (numbers.size() > 1) {
			std::sort(std::begin(numbers), std::end(numbers));
		}
	}

	// 2개 이상 아이템이 있는 그룹의 순열을 획득하여, 가장 큰 값을 candidate 에 저장
	for (auto& m : nmap) {
		auto index = m.first;
		auto& numbers = m.second;
		if (numbers.size() > 1) {
			candidates[index] = join(numbers);
			do {
				for (auto& str : numbers) std::cout << str << " ";
				std::cout << std::endl;

				auto joined = join(numbers);
				for (auto i = 0; i < joined.size(); ++i) {
					if (joined[i] < candidates[index][i]) {
						break;
					} else if (joined[i] > candidates[index][i]) {
						candidates[index] = joined;
						break;
					}
				}
			} while (next_permutation(std::begin(numbers), std::end(numbers)));
			std::cout << std::endl;
		}
		else {
			candidates[index] = std::to_string(numbers.at(0));
		}

		std::cout << " max : " << candidates[index] << std::endl;
	}

	std::reverse(std::begin(candidates), std::end(candidates));
	std::cout << "result : " << join(candidates) << std::endl;

	return 0;
}
