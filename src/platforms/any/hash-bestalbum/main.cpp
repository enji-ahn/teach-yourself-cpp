#include <any>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <vector>
#include <queue>
#include <numeric>

/**
 * 문제 : https://school.programmers.co.kr/learn/courses/30/lessons/42579
 * --내 풀이 ---
 * hash table 에 값 입력(value with index)
 *   * key with list (pair(plays with index))
 * priority queue 에 hash table 을 돌면서, 장르별 최대 재생 횟수 입력 (재생 횟수 priority with 장르명)
 *
 * priority queue 에서 한개씩 빼면서, 그 key 에 해당하는 hash table 에서 첫 2개 항목의 index 획득 (반복)
 */

using namespace std;

struct map_value_compare {
    bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) {
        return a.first > b.first;
    }
};

struct chart_compare {
    bool operator()(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second < b.second;
    }
};

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;

    auto albums = std::map<std::string/*장르*/, std::vector<std::pair<int/*plays*/, int/*index*/>>>();
    for (auto i = 0; i < genres.size(); ++i) {
        auto& album_key = genres[i];
        if (albums.find(album_key) == albums.end()) albums[album_key] = std::vector<std::pair<int, int>>();
        albums[album_key].push_back(std::pair<int, int>(plays[i], i));
    }

    auto chart = std::priority_queue<std::pair<std::string/*장르*/, int/*plays*/>, std::vector<std::pair<std::string, int>>, chart_compare>();
    for (auto& album : albums) {
        auto plays = 0;
        for (auto v = std::begin(album.second); v != std::end(album.second); ++v) {
            plays += v->first;
        }
        chart.push(std::pair<std::string, int>(album.first, plays));
    }

    while (chart.size() > 0) {
        auto item = chart.top();
        chart.pop();

        auto& album_key = item.first;

        std::sort(std::begin(albums[album_key]), std::end(albums[album_key]), [](const std::pair<int, int>& a, const std::pair<int, int>& b) { return a.first > b.first; });
        answer.push_back(albums[album_key][0].second);
        if (albums[album_key].size() > 1) {
            answer.push_back(albums[album_key][1].second);
        }
    }

    return answer;
}

int main(int argc, char const *argv[]) {

    auto r = solution({ "classic", "pop", "classic", "classic", "pop" }, { 500, 600, 150, 800, 2500 });
    std::cout << "result : ";
    for (auto& x: r) std::cout<< x << " ";
    std::cout << std::endl;

  return 0;
}
