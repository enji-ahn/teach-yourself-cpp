
#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
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


// 앞자리 순서로 배열후 조합한다.
// 앞자리가 같은 숫자 그룹은 순열을 통해서 가장 큰 값으로 만든다.

int main() {
	std::map<char, std::vector<std::string>> nmap;
	auto candidates = std::vector<std::string>(10); 
	std::vector<std::string> sv = { "4", "321", "31", "300", "5"};
	
	// 앞자리가 같은 숫자 그룹으로 분류
	for (auto& s : sv) nmap[s.at(0)].push_back(s);

	// 2개 이상 아이템이 있는 그룹의 경우, 정렬
	for (auto& m : nmap) {
		auto& numbers = m.second;
		if (numbers.size() > 1) {
			std::sort(std::begin(numbers), std::end(numbers),
				[](std::string& left, std::string& right)->bool {
					if (left.size() != right.size()) {
						return left.size() > right.size();
					}

					for (auto i = 0; i < left.size(); ++i) {
						if (left.at(i) > right.at(i)) return true;
					}
					return false;
				}
			);
		}
	}

	// 2개 이상 아이템이 있는 그룹의 순열을 획득하여, 가장 큰 값을 candidate 에 저장
	for (auto& m : nmap) {
		auto index = m.first - '0';
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
			} while (next_permutation(std::begin(numbers), std::end(numbers), 
				[](std::string& left, std::string& right)->bool {
					if (left.size() != right.size()) {
						return left.size() > right.size();
					}

					for (auto i = 0; i < left.size(); ++i) {
						if (left.at(i) > right.at(i)) return true;
					}
					return false;
				}
			));
			std::cout << std::endl;
		}
		else {
			candidates[index] = numbers.at(0);
		}

		std::cout << " max : " << candidates[index] << std::endl;
	}

	std::reverse(std::begin(candidates), std::end(candidates));
	std::cout << "result : " << join(candidates) << std::endl;

	return 0;
}
