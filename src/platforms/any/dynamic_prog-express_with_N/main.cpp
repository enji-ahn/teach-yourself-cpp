#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

/**
문제 설명
아래와 같이 5와 사칙연산만으로 12를 표현할 수 있습니다.

12 = 5 + 5 + (5 / 5) + (5 / 5)
12 = 55 / 5 + 5 / 5
12 = (55 + 5) / 5

5를 사용한 횟수는 각각 6,5,4 입니다. 그리고 이중 가장 작은 경우는 4입니다.
이처럼 숫자 N과 number가 주어질 때, N과 사칙연산만 사용해서 표현 할 수 있는 방법
중 N 사용횟수의 최솟값을 return 하도록 solution 함수를 작성하세요.

제한사항
N은 1 이상 9 이하입니다.
number는 1 이상 32,000 이하입니다.
수식에는 괄호와 사칙연산만 가능하며 나누기 연산에서 나머지는 무시합니다.
최솟값이 8보다 크면 -1을 return 합니다.
입출력 예
N	number	return
5	12	4
2	11	3

--------------
2 + 2 + 2 + 2 + 2 + (2/2)
22/2



--------------
2
--
2@2
2+2
2-2
2x2
2/2
--
22@2
22+2
22-2
22x2
22/2
(2+2)+2
(2+2)-2
(2+2)x2
(2+2)/2
(2-2)+2
(2-2)-2
(2-2)x2
(2-2)/2
(2x2)+2
(2x2)-2
(2x2)x2
(2x2)/2
(2/2)+2
(2/2)-2
(2/2)x2
(2/2)/2
--
222@2
222+2
222-2
222x2
222/2
((2+2)+2)+2
((2+2)+2)-2
((2+2)+2)x2
((2+2)+2)/2

--------------------------------
1 개

2

2개 

2+2
2-2
2*2
2/2
22

3 개

2+2+2
2+2-2
2+2*2
2+2/2

2-2+2
2-2-2
2-2*2
2-2/2

2*2+2
2*2-2
2*2*2
2*2/2

2/2+2
2/2-2
2/2*2
2/2/2

22+2
22-2
22*2
22/2

2+22
2-22
2*22
2/22

**/

#define LOG_ON false
using namespace std;

int gen(int N, int count, int expect) {
	if (count > 8) return -1;
	if (count == 1) return gen(N, count + 1, expect);

	// 2 => 1 calc 2 // nn, n+n, n-n, n*n, n/n
	// 3 => (1 calc 2 result) calc 3 // nnn, nn{?}n, n+n{?}n, n-n{?}n, n*n{?}n, n/n{?}n
}

int gen2(int N, std::vector<long long> prevs, int number, int expect) {
	if (number > 8) return -1;
	if (N != expect) {
		auto default_ = 0L;
		for (auto i = 0; i < number+1; ++i) default_ = default_ * 10 + N;
		std::vector<long long> news = { default_ };
		for (auto& p : prevs) {
			auto plus = p + N; news.push_back(plus);
			if (plus == expect) {
				return number + 1;
			}
			auto minus = p - N; news.push_back(minus);
			if (minus == expect) {
				return number + 1;
			}
			auto mul = p * N; news.push_back(mul);
			if (mul == expect) {
				return number + 1;
			}
			auto div = p / N; news.push_back(div);
			if (div == expect) {
				return number + 1;
			}
		}

		return gen2(N, news, number + 1, expect);
	}
	else return number;
}

int solution(int N, int number) {
	std::vector<long long> prevs = { N };
	int answer = gen2(N, prevs, 1, number);
	return answer;
}

int main(int argc, char const* argv[]) {
	std::cout << "result -> " << solution(5, 12) << " expected -> " << 4
		<< std::endl;
	std::cout << "result -> " << solution(2, 11) << " expected -> " << 3
		<< std::endl;
	std::cout << "result -> " << solution(5, 31168) << " expected -> " << -1
		<< std::endl;

	std::cout << "result -> " << solution(4, 1936) << " expected -> " << 4
		<< std::endl; // -> 44*44
	std::cout << "result -> " << solution(4, 3872) << " expected -> " << 6
		<< std::endl; // -> (44+44)*44
	return 0;
}
