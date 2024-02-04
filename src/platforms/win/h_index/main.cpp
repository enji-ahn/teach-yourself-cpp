
#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <map>

/**
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/42747
 * 이해 : https://school.programmers.co.kr/questions/64629 설명
 * 내가 생각한 풀이: 
 *   1. 정렬 수행 (내림차순 정렬)
 *   2. index 를 올려가면서, 값과, 인용한 갯수중 작은 값을 answer 에 저장
 *   4. 만약 값이 answer 보다 작다면, 이후는 볼 필요 없음.
        3 0 6 1 5 -> 6 5 3 1 0
        [6] : 인용 갯수 1 -> min(6, 1) => 1
        [5] : 인용 갯수 2 -> min(5, 2) => 2
        [3] : 인용 갯수 3 -> min(3, 3) => 3
        2 는 answer 보다 작으므로, 더 이상 보지 않음. 3 반환.
**/

int solution(std::vector<int> citations) {
    int answer = 0;
    std::sort(std::begin(citations), std::end(citations), std::greater<>{});
    for (auto i = 0; i < citations.size(); ++i) {
        if (answer > citations[i]) break;
        auto h = std::min(citations[i], i + 1);
        answer = std::max(h, answer);
    }

    return answer;
}

int main() {
    auto r = solution({ 9, 7, 6, 2, 1 });
    std::cout << "r : " << r << std::endl;
    r = solution({ 3, 0, 6, 1, 5 });
    std::cout << "r : " << r << std::endl;
	return 0;
}
