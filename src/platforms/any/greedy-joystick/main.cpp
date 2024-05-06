#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cassert>

/**
 * @brief 문제 :
 * 풀이 ----
 * 1. 왼쪽으로 움직이는 경우, 오른쪽으로 움직이는 경우 2가지로 확인
 * 2. 미지의 알파벳 x 가 a-> 부터 찾는게 빠른지, <- z 부터 찾는게 빠른지 확인
 *    (26 - (x - 'a'))
 *
 * a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z
 * 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
 * 0  25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9  8  7  6  5  4  3  2  1
 * 
 * LOAAAHAJAAFAEBAWO
 * L 11 + 0
 * O 12 + 1
 * O 12 + 2
 * W 4 + 1
 * B 1 + 2
 * E 4 + 1
 * F 5 + 2
 * J 9 + 3
 * H 7 + 2
 * 14
 * RCETAAAAVUEAETZAAAK
 * K 10 + 1
 * R 9 + 1
 * C 2 + 1
 * E 4 + 1
 * T 7 + 1
 * V 5 + 5
 * U 6 + 1
 * E 4 + 1
 * E 4 + 2
 * T 7 + 1
 * Z 1 + 1
 * 16
 * 
 * j => 9
 * e => 4
 * r => 17 / 9
 * o => 14 / 12
 * e => 4
 * n => 13 / 14
 * 
 * 첫 글자(0번 인덱스) 일때 및,연속되는 A 가 있을 경우, 좌/우 분기해서 탐색해 봐야 할듯.
 * AKAAWAKX
 * 01234567
 * 0->1
 *   1->2
 *     2->3
 *       3->4
 *         4->5
 *           5->6
 *             6->7
 *   1->0
 *     0->7
 *       7->6
 *         6->5
 *           5->4
 * 0->7
 *   7->6
 *     6->5
 *       5->4
 *         4->3
 *           3->2
 *             2->1
 *         4->5
 *           5->6
 *             6->7
 *               7->0
 *                 0->1
 */


#define LOG_ON false
using namespace std;

//int straight(string name) {
//  int answer = 0;
//  auto len = name.size();
//  auto from = std::string();
//
//  from.assign(len, 'A');
//
//  if (LOG_ON)
//      std::cout << "from " << from << std::endl;
//
//  auto reveresd = 0;
//
//  for (auto i = 0; i < len; ++i) {
//    if (from == name)
//      break;
//    auto x = name[i];
//    auto diff_from_a = x - 'A';
//    auto diff_from_z = 'Z' - x;
//    auto r =
//        (diff_from_a < diff_from_z) ? 'A' + diff_from_a : 'Z' - diff_from_z;
//    from[i] = r;
//
//    auto min = std::min(diff_from_a, diff_from_z + 1/*a->z step*/);
//    answer += min;
//    if (from == name)
//        break;
//    answer++;
//  }
//
//  if (LOG_ON)
//      std::cout << "changed " << from << std::endl;
//
//  return answer;
//}
//
//int reversed(string name) {
//  int answer = 0;
//  int len = name.size();
//  auto from = std::string();
//
//  from.assign(len, 'A');
//
//  if (LOG_ON)
//      std::cout << "from " << from << std::endl;
//
//  for (auto i = 0; i > (len * -1); --i) {
//    if (from == name) {
//        if (LOG_ON)
//            std::cout << "equal " << std::endl;
//      break;
//    }
//    if (LOG_ON)
//        std::cout << "i : " << i << " len " << len << std::endl;
//    auto index = (i < 0) ? len + i : i;
//    if (LOG_ON)
//        std::cout << "index " << index << std::endl;
//    auto x = name[index];
//    auto diff_from_a = x - 'A';
//    auto diff_from_z = 'Z' - x;
//    auto r =
//        (diff_from_a < diff_from_z) ? 'A' + diff_from_a : 'Z' - diff_from_z;
//    from[index] = r;
//
//    answer += std::min(diff_from_a, diff_from_z + 1/*a->z step*/);
//    if (from == name)
//        break;
//    answer++;
//  }
//
//  if (LOG_ON)
//      std::cout << "changed " << from << std::endl;
//
//  return answer;
//}

//int solution(string name) {
//    auto a = straight(name);
//    auto b = reversed(name);
//
//    return std::min(a, b);
//}

constexpr auto FORWARD = 0;
constexpr auto BACKWORD = 1;
using direction = int; // 0 => forward, 1 => backword

struct To {
    To(size_t len) : index(0), steps(0) {
        value.assign(len, 'A');
    }
    To(std::string const& name) : index(0), steps(0) {
        value = name;
    }
    To(const To& from) {
        index = from.index;
        steps = from.steps;
        value = from.value;
    }
    To(To&& from) noexcept {
        index = from.index;
        steps = from.steps;
        value = std::move(from.value);
    }

    int update(std::string const& name) {
        auto x = name[index];
        if (value[index] == x) return 0;

        auto diff_from_a = x - 'A';
        auto diff_from_z = 'Z' - x;
        auto r =
            (diff_from_a < diff_from_z) ? 'A' + diff_from_a : 'Z' - diff_from_z;
        value[index] = r;
        return std::min(diff_from_a, diff_from_z + 1/*a->z step*/);
    }

    bool isNexAA(direction dir, std::string const& name) {
        if (dir == FORWARD) {
            return index + 1 < name.size() && name[index] == 'A' && name[index + 1] == 'A';
        }
        else {
            return static_cast<int>(index) - 1 >= 0 && name[index] == 'A' && name[index - 1] == 'A';
        }
    }
    size_t index;
    string value;
    size_t steps;
};

int solution(string name) {
	int answer = -1;

	auto queue = std::queue<std::pair<direction, To>>();
	queue.push(std::make_pair(FORWARD, To{ name.size()}));
	queue.push(std::make_pair(BACKWORD, To{ name.size()}));

	while (answer < 0 && !queue.empty()) {
		auto sibilings = queue.size();

		while (sibilings--) {
            std::pair<direction, To> elem = std::move(queue.front()); queue.pop();
			auto& to = elem.second;
            auto index = to.index;
			switch (elem.first) {
			case FORWARD: {
				auto step = to.update(name);
				to.steps += step;

                to.index = (index + 1 >= name.size()) ? 0 : index + 1;
				to.steps++;

                queue.push(elem);

                if (to.isNexAA(elem.first, name)) {
                    elem.first = BACKWORD;
                    to.index = (static_cast<int>(index) - 1 >= 0) ? index - 1 : name.size() - 1;

                    queue.push(elem);
                }
			} break;
            case BACKWORD: {
				auto step = to.update(name);
				to.steps += step;

				to.index = (static_cast<int>(index) - 1 >= 0) ? index - 1 : name.size() - 1;
				to.steps++;

                queue.push(elem);

                if (to.isNexAA(elem.first, name)) {
                    elem.first = FORWARD;
                    to.index = (index + 1 >= name.size()) ? 0 : index + 1;

                    queue.push(elem);
                }

			} break;
			default: assert(false);
			}

			if (to.value == name) {
				answer = to.steps - 1;
				break;
			}
		}
	}

	return answer;
}

int main(int argc, char const *argv[]) {

  std::cout << "result -> " << solution("JAZ") << " expected -> " << 11
            << std::endl;
  std::cout << "result -> " << solution("JEROEN") << " expected -> " << 56
            << std::endl;
  std::cout << "result -> " << solution("JAN") << " expected -> " << 23
            << std::endl;

  std::cout<<"result -> " << solution("LABLPAJM")<<" expected -> "<<61<<std::endl;
  std::cout<<"result -> " << solution("BMOABA")<<" expected -> "<<30<<std::endl;
  std::cout<<"result -> " << solution("LAABAA")<<" expected -> "<<15<<std::endl;
  std::cout<<"result -> " << solution("AAAAAAAAJAAAA")<<" expected -> "<<14<<std::endl;
  std::cout<<"result -> " << solution("SAAAAAARRM")<<" expected -> "<<41<<std::endl;
  std::cout<<"result -> " << solution("RABAMATAWADLAFAVAAE")<<" expected -> "<<78<<std::endl;
  std::cout<<"result -> " << solution("XAAAAAABA")<<" expected -> "<<6<<std::endl;
  std::cout<<"result -> " << solution("AYOZAAVADAY")<<" expected -> "<<35<<std::endl;
  std::cout<<"result -> " << solution("AAFEASAAVA")<<" expected -> "<<30<<std::endl;
  std::cout<<"result -> " << solution("UAGAAASAAFAFXZA")<<" expected -> "<<47<<std::endl;
  std::cout<<"result -> " << solution("AAAAZAATAEA")<<" expected -> "<<19<<std::endl;
  std::cout<<"result -> " << solution("AACALATLAHABAA")<<" expected -> "<<50<<std::endl;
  std::cout<<"result -> " << solution("FAWJAAAFV")<<" expected -> "<<35<<std::endl;
  std::cout<<"result -> " << solution("AACAVAAPSAAOAA")<<" expected -> "<<49<<std::endl;
  std::cout<<"result -> " << solution("AKAAWAKX")<<" expected -> "<<33<<std::endl;
  std::cout<<"result -> " << solution("LOAAAHAJAAFAEBAWO")<<" expected -> "<<79<<std::endl;
  std::cout<<"result -> " << solution("AWAWVAQVAAA")<<" expected -> "<<35<<std::endl;
  std::cout<<"result -> " << solution("RCETAAAAVUEAETZAAAK")<<" expected -> "<<75<<std::endl;
  std::cout<<"result -> " << solution("GTAASKKAE")<<" expected -> "<<52<<std::endl;
  std::cout<<"result -> " << solution("AAAABAAAAAAKSAIQ")<<" expected -> "<<49<<std::endl;
  std::cout<<"result -> " << solution("ADASAAAUAAAPAA")<<" expected -> "<<39<<std::endl;
  std::cout<<"result -> " << solution("AAAAADBAAELSPUAAAOA")<<" expected -> "<<70<<std::endl;
  std::cout<<"result -> " << solution("VJAAIAFNAAAAA")<<" expected -> "<<47<<std::endl;
  std::cout<<"result -> " << solution("AARUAUAAHTBJAAYS")<<" expected -> "<<69<<std::endl;
  std::cout<<"result -> " << solution("IASAGITUPHE")<<" expected -> "<<74<<std::endl;
  std::cout<<"result -> " << solution("AAALAAAAAA")<<" expected -> "<<14<<std::endl;
  std::cout<<"result -> " << solution("AAAEASAHQAYTAAAJ")<<" expected -> "<<60<<std::endl;
  std::cout<<"result -> " << solution("BAALEAAAPMAAAHSRAV")<<" expected -> "<<83<<std::endl;
  std::cout<<"result -> " << solution("ASWAAATDAJAXA")<<" expected -> "<<45<<std::endl;
  std::cout<<"result -> " << solution("DYAOAAAARQANAWA")<<" expected -> "<<66<<std::endl;
  std::cout << "result -> " << solution("AAIAPB") << " expected -> " << 24 << std::endl;

  return 0;
}
