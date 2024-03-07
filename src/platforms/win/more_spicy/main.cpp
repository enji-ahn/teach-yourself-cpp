
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
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/42626
 * ----
 * 내가 생각한 풀이 1차:
 * K 보다 작은 목록만 추출 (LQ)
 *   스코빌 계산을 수행 (횟수 기록)
 *   스코빌 계산 결과가 K 보다 작다면, 계산 결과를 LQ 에 재 삽입 & sort 수행
 * 반복
 * LQ 에 항목이 1개만 남은 경우라면, -1 반환
 * 횟수 반환
 * 
 * # 문제점 : K보다 작은 목록일 경우, 마지막 1개가 남았을때 K 보다 큰 값이랑 조합하면 
             모두 K 를 넘게 되니까. 이때의 횟수도 포함해야 함.
 * ----
 * 내가 생각한 풀이 2차:
 * 스코빌 지수 정렬 (오름차) (SV)
 * 첫번째 항목이 K 보다 작은 경우
 *   스코빌 계산을 수행 (횟수 기록)
 *   스코빌 계산 결과가 K 보다 작다면, 계산 결과를 SV 에 재 삽입 & sort 수행
 * 반복
 * SV 에 항목이 1개만 남은 경우라면, -1 반환
 * 횟수 반환
 * 
 * # 특정 테스트의 실패 케이스를 모르겠어서, 힌트 참고하여 `스코빌 계산 결과가 K 보다 작다면,` 삭제
   `K이하일때만 추가하게 되면 scoville=[1,2,3] K=5 같은 상황에서 첫 반복에서 생성된 5가 추가되지 않아 3이 처리되지 않고 -1이 리턴되기 때문에 실패합니다.`
 * # 정확도는 해결되었으나, 성능 X
 * 
 * ----
 * 내가 생각한 풀이 3차:
 * ~~https://yabmoons.tistory.com/246 를 참고하여 scoville vector 에서 index 치환을 통해서 처리~~
 * https://kbj96.tistory.com/15 를 참고하여 우선순위 queue 사용
 * 우선순위 큐를 만들어서 저장 (덜 매운것이 높은 우선순위)
 * 첫 항목이 K 보다 작은 경우
 *   스코빌 계산을 수행 (횟수 기록)
 *   스코빌 계산 결과가 K 보다 작다면, 계산 결과를 SV 에 재 삽입
 * 반복
 * SV 에 항목이 1개만 남은 경우라면, -1 반환
 * 횟수 반환
 * 
**/

using namespace std;


int solution(vector<int> scoville, int K) {
	auto calc_scovill = [](unsigned long long lowest, unsigned long long second) -> unsigned long long {
		return lowest + (second * 2);
	};
	auto cmp = [](const unsigned long long& a, const unsigned long long& b) -> bool {
		return a > b;
	};
	auto sv = priority_queue<unsigned long long, vector<unsigned long long>, decltype(cmp)>(cmp);
	std::for_each(std::begin(scoville), std::end(scoville), [&sv](unsigned long long v) { sv.push(v); });

	int answer = 0;

	while (sv.size() > 1 && sv.top() < K) {

		auto lowest = sv.top(); sv.pop();
		auto second = sv.top(); sv.pop();

		auto new_scoville = calc_scovill(lowest, second);
		sv.push(new_scoville);

		answer++;
	}

	if (sv.size() == 1 && sv.top() < K) return -1;

	return answer;
}

int main() {
	//auto r = solution({ 12, 1, 2, 3, 9, 10, 12 }, 7);
	//auto r = solution({1, 1, 2, 6}, 24);
	auto r = solution({ 1, 2, 3 }, 5);
	std::cout << "result : " << r << std::endl;
	return 0;
}
