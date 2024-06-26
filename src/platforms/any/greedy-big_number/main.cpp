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

--------------------
가져올 갯수만큼 앞에서 빼고, 그중에 가장 작은 숫자를 버려감.
4177252841 : 4
417725 => 1 삭제
47725+2
47752 => 2 삭제. 가장 작은 숫자가 2개 이상이라면 가장 앞의 숫자 삭제
47752+8
47758 => 2 삭제
47758+4
77584 => 4 삭제. 가장 작은 숫자가 2개 이상이라면 가장 앞의 숫자 삭제
77584+1
775841 => (더이상 뒤 값이 없으므로) result

3879781299 : 2
38797812 => 1 삭제, 9 추가
38797829
38797899 => 2 삭제, 9 추가

----------------------
4 //-1
1 //-4
41 //

47 //-1+7
17 //-4+7
41 //

47 //-1
477


4177252841 : 4
417725 => 에서 가장 큰 조합 확인
x17725 => 17725
4x7725 => 47725
41x725 => 41725 => 47.. 보다 작으니 볼 필요 없음
417x25 => 41725 => 47.. 보다 작으니 볼 필요 없음
4177x5 => 41775 => 47.. 보다 작으니 볼 필요 없음
41772x => 41772 => 47.. 보다 작으니 볼 필요 없음

47725+2 => 에서 가장 큰 조합 확인
x77252 => 77252
4x7252 => 47252 => 7.. 보다 작으니 볼 필요 없음
47x252 => 47252 => 7.. 보다 작으니 볼 필요 없음
477x52 => 47752 => 7.. 보다 작으니 볼 필요 없음
4772x2 => 47722 => 7.. 보다 작으니 볼 필요 없음
47725x => 47725 => 7.. 보다 작으니 볼 필요 없음

77252+8 => 에서 가장 큰 조합 확인

---------------------
4177252841 : 4
41 : 4
47 : 7
77 : 77
72 : 7
75 : 7
72 : 7

41 : 4 /1
47 : 7 /1
77 : - /0
772 vs 775 : 775 /1
52 : 5 /1
775841

3879781299 : 2
38 : 8
87 : 8
89781299

190000002 : 3
19 : 9
90 : 9
90 : 9
900002

1924 : 2
19 : 9
92 : 9
94

720378 : 2
72 : 7
70 : 7
7378

1231234 : 3
12 : 2
23 : 3
31 : 3
3234

4321 : 1
43 : 4
421 x

-----------

4177252841 : 4

41 : 4 (1 다음수가 1보다 크므로 stop)
47 : 7
77 : -
72 : 7 (2 다음수가 2보다 크므로 stop)
75 : 75 (5 다음수가 5보다 작으므로, 5 는 유지)
52 : 5 (2 다음수가 2보다 크므로 stop)
775841

4321 : 1
43/2 : 4 (3 다음수가 3보다 작으므로 3 은 유지)
32/1 : 3 (2 다음수가 2보다 작으므로 2 는 유지)
21/null : 2 (1 다음수는 없고, 삭제된 숫자가 없으므로 k 만큼 버림) 

720378 : 2
72/0 : 72
20/3 : 2 /3
23/7 : 3 / 2
7378

----------
앞 숫자가 작다면 버림
뒷 숫자가 작다면, 이어지는 숫자들중 커지는 숫자 바로 앞 숫자를 버림.
4321 이라면 1 을 버림 => 432
190000002 라면 2 바로 앞 0을 버림 => 19000002

190000002 : 3
1/9 : 90000002
9/0 : 9000002
9/0 : 900002

4177252841 : 4
41 : 477252841
47 : 77252841
772/5 : 7752841
52 : 
**/

constexpr auto LOG_ON = true;
using namespace std;

string solution(string number, int k) {
	size_t skip = 0;
	auto len = number.size() - k;
	while (k) {
		auto erased = false;
		auto src = number[skip];
		auto index = skip + 1;
		auto cmp = number[index];
		if (src < cmp) {
			number.erase(skip, 1);
			k--;
			erased = true;
		}
		else {
			while (number[++index]) {
				auto next = number[index];
				if (cmp < next) {
					number.erase(index - 1, 1);
					k--;
					erased = true;
					break;
				}
				else {
					cmp = next;
				}
			}
		}

		if (!erased) {
			number.erase(number.size() - 1, 1);
			k--;
		}
	}

	return string(std::begin(number), std::begin(number) + len);
}


int main(int argc, char const* argv[]) {
	std::cout << "result -> " << solution("4177252841", 4) << " expected -> "
		<< "775841" << std::endl;
	std::cout << "result -> " << solution("4321", 1) << " expected -> "
		<< "432" << std::endl;
	std::cout << "result -> " << solution("190000002", 3) << " expected -> "
		<< "900002" << std::endl;
	std::cout << "result -> " << solution("1924", 2) << " expected -> "
		<< "94" << std::endl;
	std::cout << "result -> " << solution("720378", 2) << " expected -> "
		<< "7378" << std::endl;
	std::cout << "result -> " << solution("1231234", 3) << " expected -> "
		<< "3234" << std::endl;
	std::cout << "result -> " << solution("3879781299", 2) << " expected -> "
		<< "89781299" << std::endl;

	return 0;
}
