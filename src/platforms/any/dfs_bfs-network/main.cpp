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

/**
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/43162
 * --내 풀이 ---
 * 가리키는 index 에 해당하는 배열([row,column]) 값을 0 으로 만들고, 
     element 로 가서, 해당 row 에 1인 항목이 있다면, 해당하는 배열... 반복
     더이상, 연결된 항목이 없다면 반환. (network count 는 ++ 처리)
 *
 * [*1  1  0] => 1<->1, 1<->2
 * [ 1 *1  0] => 2<->1, 2<->2
 * [ 0  0 *1] => 3<->3
 */

using namespace std;
using name = int;

void dfs_search(int i, int ii, vector<vector<int>>& computers) {
    for (auto j = 0; j < computers[i].size(); ++j) {
        if (i == j || i == ii) {
            computers[i][j] = 0;
            continue;
        }
        else if (computers[i][j]) {
            computers[i][j] = 0;
            dfs_search(j, i, computers);
        }
    }
}

int solution(int n, vector<vector<int>> computers) {
    auto count = 0;

    for (auto i = 0; i < computers.size(); ++i) {
        auto flag = false;
        for (auto j = 0; j < computers[0].size(); ++j) {
            if (i == j && computers[i][j]) {
                computers[i][j] = 0;
                flag = true;
                continue;
            }
            else if (computers[i][j]) {
                computers[i][j] = 0;
                dfs_search(j, i, computers);
                flag = true;
            }
        }
        if (flag) count++;
    }

    return count;
}

int main(int argc, char const *argv[]) {
  std::cout << "result -> " << solution(3, {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}}) << " expected " << 2
            << std::endl;

  std::cout << "result -> " << solution(3, { {1, 1, 0}, {1, 1, 1}, {0, 1, 1} }) << " expected " << 1
      << std::endl;

  return 0;
}
