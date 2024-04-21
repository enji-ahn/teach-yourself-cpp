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
using y_offset = int;
using x_offset = int;

#define LOG_ON false

std::vector<std::pair<y, x>> find_piece_bfs(
	std::vector<std::vector<int>>& game_board,
	y y_pos, x x_pos,
	int expect = 1)
{
	auto dirs = std::vector<std::pair<y_offset, x_offset>>{
	{-1, 0} , //t
	{0, -1}, {0, 1}, //l, r
	{1, 0}, //lb, b, rb
	};

	auto queue = std::queue<std::pair<y, x>>();
	queue.push({ y_pos, x_pos });

	std::vector<std::pair<y, x>> piece;

	while (!queue.empty()) {
		auto pos = queue.front(); queue.pop();

		for (auto& dir : dirs) {
			auto x_pos = pos.second + dir.second;
			auto y_pos = pos.first + dir.first;

			if (y_pos >= 0 && y_pos < game_board.size() &&
				x_pos >= 0 && x_pos < game_board[0].size() &&
				game_board[y_pos][x_pos] == expect) {
				queue.push({ y_pos, x_pos });
			}
		}

		game_board[pos.first][pos.second] = 9; // traversed
		piece.push_back({ pos.first, pos.second });
	}

	return piece;
}

std::vector<std::vector<std::vector<int>>> pieces_to_2d_map(
	std::vector<std::vector<std::pair<y, x>>> pieces
) {
	auto _2d_pieces = std::vector<std::vector<std::vector<int>>>();

	for (auto& piece : pieces) {
		auto min_y = 100, min_x = 100, max_y = 0, max_x = 0;
		for (auto& pos : piece) {
			min_y = (min_y > pos.first) ? pos.first : min_y;
			min_x = (min_x > pos.second) ? pos.second : min_x;
			max_y = (max_y < pos.first) ? pos.first : max_y;
			max_x = (max_x < pos.second) ? pos.second : max_x;
		}

		auto h = max_y - min_y + 1;
		auto w = max_x - min_x + 1;

		auto piece_map = std::vector<std::vector<int>>(h);
		for (auto i = 0; i < (h); ++i) {
			piece_map[i] = vector<int>(w);
		}

		for (auto& pos : piece) {
			auto x_pos = pos.second - min_x;
			auto y_pos = pos.first - min_y;
			piece_map[y_pos][x_pos] = 1;
		}

		if (LOG_ON) {
			for (auto& row : piece_map) {
				for (auto& col : row) {
					std::cout << col << " ";
				}
				std::cout << std::endl;
			}
			std::cout << "---------------" << std::endl;
		}

		_2d_pieces.push_back(piece_map);
	}

	return _2d_pieces;
}

std::vector<std::vector<int>> rotate(std::vector<std::vector<int>>const& piece) {
	auto to_w = piece.size();
	auto to_h = piece[0].size();
	auto piece_90 = std::vector<std::vector<int>>(to_h);
	for (auto i = 0; i < (to_h); ++i) {
		piece_90[i] = vector<int>(to_w);
	}

	for (auto y_pos = 0; y_pos < piece.size(); ++y_pos) {
		for (auto x_pos = 0; x_pos < piece[0].size(); ++x_pos) {
			piece_90[x_pos][to_w - 1 - y_pos] = piece[y_pos][x_pos];
		}
	}

	return piece_90;
}

int solution(vector<vector<int>> game_board, vector<vector<int>> table) {
	//// on game board
	// 좌표(pair<y, x>)를 저장하고 있는 조각(vector<pair>)의
	// 목록(vector<vector<pair>>)
	auto board_pieces = std::vector<std::vector<std::pair<y, x>>>();

	for (auto y_pos = 0; y_pos < game_board.size(); ++y_pos) {
		for (auto x_pos = 0; x_pos < game_board[0].size(); ++x_pos) {
			if (game_board[y_pos][x_pos] == 0) {
				board_pieces.push_back(find_piece_bfs(
					game_board,
					y_pos,
					x_pos,
					0));
			}
		}
	}

	// T/O/D/O: make pieces to 2d array(rectangle) list
	auto board_2d_pieces = pieces_to_2d_map(board_pieces);

	//// on table
	auto table_pieces = std::vector<std::vector<std::pair<y, x>>>();
	for (auto y_pos = 0; y_pos < table.size(); ++y_pos) {
		for (auto x_pos = 0; x_pos < table[0].size(); ++x_pos) {
			if (table[y_pos][x_pos] == 1) {
				table_pieces.push_back(find_piece_bfs(
					table,
					y_pos,
					x_pos,
					1));
			}
		}
	}

	// T/O/D/O: make pices to 2d array(rectangle) list with rotated
	// {0 : [2차원 배열, 90도 돌아간 2차원 배열, 180도 돌아간 2차원 배열, 270도
	// 돌아간 2차원 배열]}
	// ...
	auto table_2d_pieces = pieces_to_2d_map(table_pieces);
	auto table_2d_pieces_map = std::map<number, std::vector<std::vector<std::vector<int>>>>();
	auto index = 0;
	for (auto& piece : table_2d_pieces) {
		auto rotated_pieces = std::vector<std::vector<std::vector<int>>>();
		rotated_pieces.push_back(piece);

		// 90
		auto piece_90 = rotate(piece);
		rotated_pieces.push_back(piece_90);

		// 180
		auto piece_180 = rotate(piece_90);
		rotated_pieces.push_back(piece_180);

		// 270
		auto piece_270 = rotate(piece_180);
		rotated_pieces.push_back(piece_270);

		table_2d_pieces_map[index] = rotated_pieces;


		if (LOG_ON) {
			for (auto& rotated : rotated_pieces) {
				for (auto& row : rotated) {
					for (auto& col : row) {
						std::cout << col << " ";
					}
					std::cout << std::endl;
				}
				std::cout << "---------------" << std::endl;
			}
			std::cout << "TABLE---------------" << std::endl;
		}

		index++;
	}

	//// find matching table_pieces to board_pieces
	auto number_of_matches = 0;
	auto skip_number = std::vector<number>();
	for (auto& board_2d_piece : board_2d_pieces) {
		if (LOG_ON) {
			for (auto& row : board_2d_piece) {
				for (auto& col : row) {
					std::cout << col << " ";
				}
				std::cout << std::endl;
			}
			std::cout << "BOARD---------------" << std::endl;
		}

		for (auto& table_2d_piece_map : table_2d_pieces_map) {
			// if already searched piece, then skip it
			if (std::find(
				std::begin(skip_number),
				std::end(skip_number),
				table_2d_piece_map.first) != std::end(skip_number)) continue;

			auto found = false;

			for (auto& table_2d_piece : table_2d_piece_map.second) {

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
						for (auto& row : table_2d_piece) {
							for (auto& col : row) {
								if (col) number_of_matches++;
							}
						}
						break;
					}
				}
			}

			if (found) {
				skip_number.push_back(table_2d_piece_map.first);
				//number_of_matches++;
				break;
			}
		}
	}

	return number_of_matches;
}

int main(int argc, char const* argv[]) {

	std::cout << "result -> " << std::endl
		<< solution(
			{ {1, 1, 0, 0, 1, 0},
			{0, 0, 1, 0, 1, 0},
			{0, 1, 1, 0, 0, 1},
			{1, 1, 0, 1, 1, 1},
			{1, 0, 0, 0, 1, 0},
			{0, 1, 1, 1, 0, 0} },
			{ {1, 0, 0, 1, 1, 0},
			 {1, 0, 1, 0, 1, 0},
			 {0, 1, 1, 0, 1, 1},
			 {0, 0, 1, 0, 0, 0},
			 {1, 1, 0, 1, 1, 0},
			 {0, 1, 0, 0, 0, 0} })
		<< " expected " << 14 << std::endl;
	std::cout << "result -> " << std::endl
		<< solution({ {0, 0, 0}, {1, 1, 0}, {1, 1, 1} },
			{ {1, 1, 1}, {1, 0, 0}, {0, 0, 0} })
		<< " expected " << 0 << std::endl;

	return 0;
}
