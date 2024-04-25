#include <algorithm>
#include <any>
#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

using namespace std;

#define SHOW_LOG false

using score = int;
using name = int;
using USER_ANSWER_TYPE = std::pair<score, std::queue<int>>;
using USER_ANSWER_MAP_TYPE = std::map<name, USER_ANSWER_TYPE>;

vector<int> solution(vector<int> answers) {
  auto user_answers = USER_ANSWER_MAP_TYPE();

  user_answers[0] =
      std::pair<score, std::queue<int>>(0, std::deque<int>{1, 2, 3, 4, 5});
  user_answers[1] = std::pair<score, std::queue<int>>(
      0, std::deque<int>{2, 1, 2, 3, 2, 4, 2, 5});
  user_answers[2] = std::pair<score, std::queue<int>>(
      0, std::deque<int>{3, 3, 1, 1, 2, 2, 4, 4, 5, 5});

  for (auto i = 0; i < answers.size(); ++i) {
    for (auto &element : user_answers) {
      auto &user = element.second;
      auto &my_answers = user.second;
      auto &my_answer = my_answers.front();
      my_answers.pop();

      if (answers[i] == my_answer)
        user.first++; // score
      if (SHOW_LOG) {
        std::cout << "found answer" << std::endl;
      }

      my_answers.push(my_answer);
    }
  }

  // https://0xd00d00.github.io/2021/08/22/map_value_reverse.html
  auto map_vec = vector<pair<name, USER_ANSWER_TYPE>>();
  for (auto &it : user_answers) {
    if (SHOW_LOG) {
      std::cout << "user id " << it.first << ", score " << it.second.first
                << std::endl;
    }
    map_vec.emplace_back(it);
  }

  std::sort(std::begin(map_vec), std::end(map_vec),
            [](std::pair<name, USER_ANSWER_TYPE> const &a,
               std::pair<name, USER_ANSWER_TYPE> const &b) -> bool {
              return a.second.first >
                     b.second.first; // compare scores with 내림차순 정렬
            });

  // 맨 앞의 값을 입력하고, 루프를 돌면서 이전 값보다 작다면, 무시, 값과 같다면,
  // list 에 입력
  auto results = std::vector<int>();
  auto top = std::begin(map_vec)->second.first;
  for (auto itr = std::begin(map_vec); itr != std::end(map_vec); ++itr) {
    if (top == itr->second.first) {
      if (SHOW_LOG) {
        std::cout << "top -> " << top << ", value -> " << itr->second.first
                  << std::endl;
      }
      results.push_back(itr->first + 1 /*1 based index*/);
    }
  }

  return results;
}

std::string join(std::vector<int> results) {
  auto r = std::string();
  for (auto &result : results) {
    r += std::to_string(result);
    r += ", ";
  }
  return r;
}

int main(int argc, char const *argv[]) {
  std::cout << "result -> " << join(solution({1, 2, 3, 4, 5}))
            << " expected -> " << join({1}) << std::endl;
  std::cout << "result -> " << join(solution({1, 3, 2, 4, 2}))
            << " expected -> " << join({1, 2, 3}) << std::endl;

  return 0;
}
