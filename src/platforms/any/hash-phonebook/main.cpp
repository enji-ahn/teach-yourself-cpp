#include <algorithm>
#include <any>
#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

/**
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/42577
 * --내 풀이 ---
 *  항목의 length 별로 hash table 생성
 *    ("12", "123") 이라면 2글자 짜리, 3글자 짜리 2개의 table 을 만듦
 *  길이별로 table 에 추가
 */

using namespace std;

bool solution(vector<string> phone_book) {
  auto sizes = std::set<std::size_t>();
  std::map<std::size_t /*hash*/, std::vector<std::string /*value*/>> book;
  std::sort(std::begin(phone_book), std::end(phone_book),
            [](std::string a, std::string b) {
              return a.size() < b.size();
            }); // 오름차 순 정렬

  for (auto &number : phone_book) {
    auto hash = std::hash<std::string>{}(number);

    // 만약 등록된 키가 없다면, list 생성하고, length 를 size list 에 삽입
    if (book.find(hash) == std::end(book)) {
      book[hash] = std::vector<std::string>();
      // 키와 매칭되는 list 에 원본 값 삽입
      book[hash].push_back(number);
      sizes.insert(number.size());
    } else {
      assert(false);
    }

    // size list 에서 하나씩 빼면서 2개 이상의 항목이 있는 경우가 있는지 확인
    for (auto &size : sizes) {
      if (number.size() <= size) // substr 하지 못한다면, 처리하지 않음
        continue;

      // size 만큼 substr 된 문자열의 hash 값 획득
      auto alt_hash = std::hash<std::string>{}(number.substr(0, size));

      // 만약 등록된 키가 없다면, 동일 접두어를 갖는 전화번호는 아직 없다고 볼
      // 수 있음
      if (book.find(alt_hash) == std::end(book)) {
        continue;
      } else if (book[alt_hash].size() >= 1) {
        // 만약 동일 hash 가 있다면, 접두어가 동일한 전화번호가 있다고 볼 수
        // 있음.
        // (1개는 현재 바깥쪽 루프에서 삽입된 것)
        return false;
      }
    }
  }

  return true;
}

int main(int argc, char const *argv[]) {

  auto r1 = solution({"119", "97674223", "1195524421"});
  std::cout << "expected -> false. result -> " << r1 << std::endl;
  auto r2 = solution({"123", "456", "789"});
  std::cout << "expected -> true. result -> " << r2 << std::endl;
  auto r3 = solution({"12", "123", "1235", "567", "88"});
  std::cout << "expected -> false. result -> " << r3 << std::endl;
  auto r4 = solution({"123", "2345", "23467"});
  std::cout << "expected -> true. result -> " << r4 << std::endl;
  auto r5 = solution({"1195524421", "119", "97674223"});
  std::cout << "expected -> false. result -> " << r5 << std::endl;
  return 0;
}
