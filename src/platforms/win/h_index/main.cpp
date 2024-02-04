
#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <map>

/**
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/42747
 * 내가 생각한 풀이: 
 *   1. 정렬 수행 (오름차순 정렬)
 *   2. 가운 값을 잡고, 가운데 값을 포함하여 우측 갯수가 가운데 값과 같거나 크고,
        촤특 값들은 모두 합한 값이 가운데 값 이하라면, 해당 값을 취득한다.
        3 0 6 1 5 -> 0 1 3 5 6
        [3]
        우측 갯수 3
        좌측 합 1
**/

int solution(std::vector<int> citations) {
    int answer = -1;
    std::sort(std::begin(citations), std::end(citations));
    int index = std::floor(citations.size()/2);
    for (; index < citations.size(); ++index) {
        int count = citations.size() - index;
        if (count >= citations[index]) {
            answer = citations[index];
        }
        else {
            break;
        }
    }

    return answer;
}

int main() {
    auto r = solution({ 3, 0, 6, 1, 5 });
    std::cout << "r : " << r << std::endl;
	return 0;
}
