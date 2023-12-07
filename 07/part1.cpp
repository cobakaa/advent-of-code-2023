#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct Combination {
    std::string hand;
    int points;
    int comb_rank;
};

std::unordered_map<char, int> char_to_points = {
    {'T', 10}, {'J', 11}, {'Q', 12}, {'K', 13}, {'A', 14}};

int getCombRank(std::string h) {
    std::map<char, int> m;
    for (char c : h) {
        m[c]++;
    }
    if (m.begin()->second == 5) {
        return 7;
    }
    if (m.begin()->second == 4 || m.rbegin()->second == 4) {
        return 6;
    }
    if (m.size() == 2) {
        return 5;
    }
    if (m.size() == 3 && (m.begin()->second == 2 || m.rbegin()->second == 2)) {
        return 3;
    }
    if (m.size() == 3) {
        return 4;
    }
    if (m.size() == 4) {
        return 2;
    }
    return 1;
}

int main() {

    for (int i = 2; i < 10; ++i) {
        char_to_points[i + '0'] = i;
    }

    std::string line;
    std::stringstream ss;
    std::vector<Combination> v;

    while (getline(std::cin, line)) {
        ss.clear();
        ss.str(line);
        Combination comb;
        ss >> comb.hand;
        ss >> comb.points;
        comb.comb_rank = getCombRank(comb.hand);
        v.push_back(comb);
    }

    std::sort(v.begin(), v.end(), [](Combination &l, Combination &r) {
        if (l.comb_rank == r.comb_rank) {
            for (size_t i = 0; i < l.hand.length(); ++i) {
                if (char_to_points[l.hand[i]] == char_to_points[r.hand[i]]) {
                    continue;
                }
                return char_to_points[l.hand[i]] < char_to_points[r.hand[i]];
            }
        }
        return l.comb_rank < r.comb_rank;
    });

    uint64_t res = 0;

    for (size_t i = 0; i < v.size(); ++i) {
        res += v[i].points * (i + 1);
    }

    std::cout << res << std::endl;

    return 0;
}
