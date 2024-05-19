#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <utility>
#include <vector>

/**
 * @brief 문제 :
https://school.programmers.co.kr/learn/courses/30/lessons/42883?language=cpp
 * 문제 설명
어떤 숫자에서 k개의 수를 제거했을 때 얻을 수 있는 가장 큰 숫자를 구하려 합니다.

예를 들어, 숫자 1924에서 수 두 개를 제거하면 [19, 12, 14, 92, 94, 24] 를 만들 수
있습니다. 이 중 가장 큰 숫자는 94 입니다.

문자열 형식으로 숫자 number와 제거할 수의 개수 k가 solution 함수의 매개변수로
주어집니다. number에서 k 개의 수를 제거했을 때 만들 수 있는 수 중 가장 큰 숫자를
문자열 형태로 return 하도록 solution 함수를 완성하세요.

제한 조건
number는 2자리 이상, 1,000,000자리 이하인 숫자입니다.
k는 1 이상 number의 자릿수 미만인 자연수입니다.
입출력 예
number	k	return
"1924"	2	"94"
"1231234"	3	"3234"
"4177252841"	4	"775841"
 * ----
 * 4177252841
 * expected no => number of char (10) - k (4) => 6
 * keep last 6 char -> 4177'252841'
 * if first is less then privious number, then remove it -> 417'752841'
 * if first is equal to privious numer, then make largest number -> 41'775841'
(sequencly remove min numbers from '7752841'. 775284, 775841, 775281, ...)
 * if privious numer is lessthn first, then remove it -> 4'775841'
 * if privious numer is lessthn first, then remove it -> '775841'
 * 4321 의 경우 처리 못함.
 *
 *
 * 4177252841
 * 177252841
 * 477252841
 * 417252841
 * 417252841
 * 417752841
 * 417722841
 * 417725841
 * 417725241
 * 417725281
 * 417725284
 *
 * 477252841
 * 77252841
 * 47252841
 * 47252841
 * 47752841
 * 47722841
 * 47725841
 * 47725241
 * 47725281
 *
 * 77252841
 * 7252841
 * 7252841
 * 7752841
 * 7722841
 * 7725841
 * 7725241
 * 7725284
 *
 * 7752841
 * 752841
 * 752841
 * 772841
 * 775841
 * 775241
 * 775281
 * 모든 경우의 수 (느림)
 * 
 * 4177252841 : 4
 * [4][1][7][7]252841 
 * [4][1][7]7[2]52841
 * // 안해봄

720378 : 2
20378
70378
72378
720/78
720/38
720/37

72378
2378
7378
72/78
72/38
72/37

4177252841 : 4
177252841
477252841
41/7252841
41/7252841
41/7752841
41/7722841
41/7725841
41/7725241
41/7725281
41/7725284

477252841
77252841
4/7252841
4/7252841
4/7752841
4/7722841
4/7725841
4/7725241
4/7725281

77252841
7252841
7252841
7752841
772/2841
772/5841
772/5241
772/5281

7752841
752841
752841
772841
775841
7752/41
7752/81
7752/84

3879781299 : 2
879781299
3/79781299
3/89781299
3/87781299
3/87981299
3/87971299
3/87978299
3/87978199
3/87978129
3/87978129

879781299
79781299
89781299
87/781299
87/981299
87/971299
87/978299
87/978199
87/978129
87/978129


느림

---------------- 가장 작은숫자 2개를 뺐을때 가장 작은 수 선택
4177252841 : 4
477252841 * //1, 2
417725284
417752841
417725841

47725284
47725841
47752841 * // 1, 2

4775284
4775841 * // 1, 2

477584
775841 * // 1, 4

-----------------
190000002 : 3

90000002 * // 0, 1
19000002
19000002
19000002
19000002
19000002
19000002

9000002
9000002
9000002
9000002
9000002
9000002 * // 0, 2
9000000

900002
900002
900002
900002
900002 * // 0, 2
900000

-------------------
3879781299 : 2
387978199
387978299 * // 1, 2

38797899
87978299 * // 2, 3	

89781299 를 만족하지 못함. invalid solution
**/

constexpr auto LOG_ON = true;
using namespace std;

string solution(string number, int k) {
	auto answer = number;
	while (k--) {
		answer.erase(0, 1);
		for (int i = 0; i < number.size(); ++i) {
			std::string compare = number;
			compare.erase(i, 1);
			if (LOG_ON) std::cout << "cmp : " << answer << std::endl;
			if (answer <= compare) {
				answer = std::move(compare);
			}
			else break;
		}
		number = answer;
		if (LOG_ON) std::cout << std::endl;
	}

	return answer;
}


int main(int argc, char const* argv[]) {
	std::cout << "result -> " << solution("190000002", 3) << " expected -> "
		<< "900002" << std::endl;
	std::cout << "result -> " << solution("4177252841", 4) << " expected -> "
		<< "775841" << std::endl;
	std::cout << "result -> " << solution("1924", 2) << " expected -> "
		<< "94" << std::endl;
	std::cout << "result -> " << solution("720378", 2) << " expected -> "
		<< "7378" << std::endl;
	std::cout << "result -> " << solution("1231234", 3) << " expected -> "
		<< "3234" << std::endl;
	std::cout << "result -> " << solution("3879781299", 2) << " expected -> "
		<< "89781299" << std::endl;
	std::cout << "result -> " << solution("4321", 1) << " expected -> "
		<< "432" << std::endl;


	return 0;
}
