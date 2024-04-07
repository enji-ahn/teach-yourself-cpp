#include <algorithm>
#include <any>
#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <set>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include <numeric>
#include <algorithm>

/**
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/43163
 * --내 풀이 ---
 * 재귀적으로 돌면서, target 이 만들어질때까지 들어간 step 중 가장 짧은 경우 확인
 */

using namespace std;

int find_step(string begin, string target, vector<string> words) {
    auto steps = std::vector<int>();

    if (begin == target) {
        return 1;
    }

    for (auto& word : words) {
        auto diffs = std::inner_product(std::begin(begin), std::end(begin),
            std::begin(word), size_t(0), std::plus<size_t>(), std::not_equal_to<char>());
        if (diffs == 1) {
            std::vector<string> new_words;
            std::copy_if(std::begin(words), std::end(words), std::back_inserter(new_words), [word](std::string& w) {
                return (word != w);
            });
            auto found = find_step(word, target, new_words);
            if (found > 0) {
                steps.push_back(found + 1);
            }
        }
    }

    if (steps.size() > 0) {
        return *std::min_element(std::begin(steps), std::end(steps));
    }

    return 0;
}

int solution(string begin, string target, vector<string> words) {
    auto answer = find_step(begin, target, words);
    return answer > 0 ? answer - 1 : 0;
}

int main(int argc, char const *argv[]) {
  std::cout << "result -> " << solution("hit", "cog", { "hot", "dot", "dog", "lot", "log", "cog" }) << " expected " << 4
            << std::endl;

  std::cout << "result -> " << solution("hit", "cog", { "hot", "dot", "dog", "lot", "log" }) << " expected " << 0
      << std::endl;

  return 0;
}
