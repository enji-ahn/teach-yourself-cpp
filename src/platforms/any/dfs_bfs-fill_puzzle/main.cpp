#include <algorithm>
#include <any>
#include <cassert>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>

/**
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/84021
 * --내 풀이 ---
 * 0.0 부터 1 인 값이 있는 부분 탐색.
 * 발견시, 거기서부터 bfs 로 (4방이 연결된) 조각 모양 확인
 * 탐색된 조각 부분은 0 으로 초기화
 *
 * 조각들을 2차원 배열로 작성
 *
 * 얻은 각 블럭별 3회전 하여 0, 90, 180, 270 도 돌아간 모양을 획득
 *
 * 비교 진행
 */

using namespace std;

using x = int;
using y = int;
using number = int;

#define LOG_ON false

int solution(vector<vector<int>> game_board, vector<vector<int>> table) {
  //// on game board
  // 좌표(pair<y, x>)를 저장하고 있는 조각(vector<pair>)의
  // 목록(vector<vector<pair>>)
  auto board_pieces = std::vector<std::vector<std::pair<y, x>>>();

  for (auto &row : game_board) {
    for (auto &col : row) {
      if (col) {
        // TODO: bfs
      }
    }
  }

  // TODO: make pieces to 2d array(rectangle) list
  auto board_2d_pieces = std::vector<std::vector<std::vector<int>>>();

  //// on table
  auto table_pieces = std::vector<std::vector<std::pair<y, x>>>();
  for (auto &row : table) {
    for (auto &col : row) {
      if (col) {
        // TODO: bfs
      }
    }
  }

  // TODO: make pices to 2d array(rectangle) list with rotated
  // {0 : [2차원 배열, 90도 돌아간 2차원 배열, 180도 돌아간 2차원 배열, 270도
  // 돌아간 2차원 배열]}
  // ...
  auto table_2d_pieces =
      std::map<number, std::vector<std::vector<std::vector<int>>>>();

  //// find matching table_pieces to board_pieces
  auto number_of_matches = 0;
  for (auto &board_2d_piece : board_2d_pieces) {
    for (auto &table_2d_piece_map : table_2d_pieces) {
      auto found = false;

      for (auto &table_2d_piece : table_2d_piece_map.second) {

        if (board_2d_piece.size() == table_2d_piece.size() &&
            board_2d_piece[0].size() == table_2d_piece[0].size()) {

          auto matched = true;
          for (auto i = 0; i < board_2d_piece.size(); ++i) {
            auto equal = std::equal(
                std::begin(board_2d_piece[i]), std::end(board_2d_piece[i]),
                std::begin(table_2d_piece[i]), std::end(table_2d_piece[i]));

            if (!equal) {
              matched = false;
              break;
            }
          }

          if (matched) {
            found = true;
            break;
          }
        }
      }

      if (found) {
        table_2d_pieces.erase(table_2d_piece_map.first);
        number_of_matches++;
      }
    }
  }

  return (number_of_matches == 0) ? -1 : number_of_matches;
}

int main(int argc, char const *argv[]) {

  std::cout << "result -> " << std::endl
            << solution({{1, 1, 0, 0, 1, 0},
                         {0, 0, 1, 0, 1, 0},
                         {0, 1, 1, 0, 0, 1},
                         {1, 1, 0, 1, 1, 1},
                         {1, 0, 0, 0, 1, 0},
                         {0, 1, 1, 1, 0, 0}},
                        {{1, 0, 0, 1, 1, 0},
                         {1, 0, 1, 0, 1, 0},
                         {0, 1, 1, 0, 1, 1},
                         {0, 0, 1, 0, 0, 0},
                         {1, 1, 0, 1, 1, 0},
                         {0, 1, 0, 0, 0, 0}})
            << " expected " << 14 << std::endl;
  std::cout << "result -> " << std::endl
            << solution({{0, 0, 0}, {1, 1, 0}, {1, 1, 1}},
                        {{1, 1, 1}, {1, 0, 0}, {0, 0, 0}})
            << " expected " << 0 << std::endl;

  return 0;
}
