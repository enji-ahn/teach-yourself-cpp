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

using power_number = int;

std::string connected_powers(std::set<power_number> numbers) {
	std::string r;
	for (auto& n : numbers) {
		r += std::to_string(n);
		r += ", ";
	}

	return r;
}

void connected_powers_to(
	vector<vector<power_number>> const& all_wires,
	std::vector<std::vector<power_number>>& wires,
	vector<power_number> const& wire,
	std::map < power_number, // 분리된 전력소스 시작번호
	std::pair<
	std::set<power_number>, // 현재 power 에 연결된 전력망 번호들
	std::vector<std::vector<power_number>>>>&powers,
	power_number key) {

	// 복사본 생성 (wire 와 매칭되는 경우는 복사본에서 제외)
	std::copy_if(std::begin(all_wires), std::end(all_wires),
		std::back_inserter(wires),
		[wire](std::vector<int> const& v) -> bool {
			return v != wire;
		});

	// 
	auto queue = std::queue<power_number>();
	queue.push(key);

	while (queue.size()) {
		auto start = queue.front(); queue.pop();
		auto itr = std::find_if(std::begin(wires), std::end(wires),
			[start](std::vector<int> const& v) -> bool {
				return start == v[0] || start == v[1];
			});

		powers[key].first.insert(start);
		if (itr != std::end(wires)) {
			powers[key].second.push_back(*itr);
			queue.push(itr->at(0));
			queue.push(itr->at(1));

			wires.erase(itr);
		}
	}

	if (SHOW_LOG) {
		std::cout << "cut " << wire[0] << " - " << wire[1]
			<< " connected to " << key
			<< " powers are " << connected_powers(powers[key].first)
			<< std::endl;
	}
}

int solution(int n, vector<vector<power_number>> all_wires) {
	int answer = 999;

	for (auto i = 0; i < n - 1; ++i) {
		auto const& wire = all_wires[i];
		auto wires = std::vector<std::vector<power_number>>();
		auto powers = std::map < power_number, // 분리된 전력소스 시작번호
			std::pair<
			std::set<power_number>, // 현재 power 에 연결된 전력망 번호들
			std::vector<std::vector<power_number>> // 전력망 배열
			>
		>();

		auto from = wire[0];
		connected_powers_to(
			all_wires,
			wires,
			wire,
			powers,
			from);

		auto to = wire[1];
		connected_powers_to(
			all_wires,
			wires,
			wire,
			powers,
			to);

		if (SHOW_LOG) {
			std::cout << "---------------" << std::endl;
		}

		int diff = powers[from].first.size() - powers[to].first.size();
		answer = std::min(answer, std::abs(diff));
	}
	return answer;
}

int main(int argc, char const* argv[]) {
	std::cout << "result -> " << solution(9, { {1, 3}, {2, 3}, {3, 4}, {4, 5},{4, 6},{4, 7},{7, 8},{7, 9} })
		<< " expected -> " << 3 << std::endl;
	std::cout << "result -> " << solution(4, { {1, 2}, {2, 3}, {3, 4} })
		<< " expected -> " << 0 << std::endl;
	std::cout << "result -> " << solution(7, { {1, 2}, {2, 7}, {3, 7},{3, 4},{4, 5},{6, 7} })
		<< " expected -> " << 1 << std::endl;

	return 0;
}
