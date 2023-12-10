#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct pair_hash {
    inline std::size_t operator()(const std::pair<int, int> &v) const {
        return v.first * 31 + v.second;
    }
};

enum DIR { UP, DOWN, RIGHT, LEFT };

struct Point {
    int x;
    int y;
    DIR dir_cur;
    DIR dir_to;
};

DIR rotateLeft(DIR d) {
    if (d == UP) {
        return LEFT;
    }
    if (d == DOWN) {
        return RIGHT;
    }
    if (d == LEFT) {
        return DOWN;
    }
    return UP;
}

int main() {

    std::unordered_map<char, std::pair<Point, Point>> m = {
        {'|', {{0, 1, DOWN, DOWN}, {0, -1, UP, UP}}},
        {'-', {{1, 0, RIGHT, RIGHT}, {-1, 0, LEFT, LEFT}}},
        {'L', {{0, -1, LEFT, UP}, {1, 0, DOWN, RIGHT}}},
        {'J', {{0, -1, RIGHT, UP}, {-1, 0, DOWN, LEFT}}},
        {'7', {{0, 1, RIGHT, DOWN}, {-1, 0, UP, LEFT}}},
        {'F', {{1, 0, UP, RIGHT}, {0, 1, LEFT, DOWN}}}};

    std::unordered_map<DIR, std::pair<int, int>> dm = {
        {LEFT, {-1, 0}}, {RIGHT, {1, 0}}, {UP, {0, -1}}, {DOWN, {0, 1}}};
    std::vector<std::string> input_map;
    std::string line;
    Point s = {-1, -1};
    while (std::getline(std::cin, line)) {
        if (input_map.size() == 0) {
            std::string str(line.size() + 2, '.');
            input_map.push_back(str);
        }
        if (s.x == -1 && s.y == -1) {
            for (size_t i = 0; i < line.length(); ++i) {
                if (line[i] == 'S') {
                    s.x = i + 1;
                    s.y = (int)input_map.size();
                }
            }
        }
        input_map.push_back("." + line + ".");
    }

    input_map.push_back(std::string(line.size() + 2, '.'));

    for (auto [d, c] : dm) {
        if (s.x + c.first >= 0 && s.x + c.first < input_map[s.x].size() &&
            s.y + c.second >= 0 && s.y + c.second < input_map.size()) {

            if (input_map[s.y + c.second][s.x + c.first] == '.') {
                continue;
            }

            if (m[input_map[s.y + c.second][s.x + c.first]].first.dir_cur ==
                    d ||
                m[input_map[s.y + c.second][s.x + c.first]].second.dir_cur ==
                    d) {
                s.dir_cur = d;
                s.dir_to = d;
                break;
            }
        }
    }

    Point cur = s;
    std::unordered_map<std::pair<int, int>, Point, pair_hash> loop;
    loop[{s.x, s.y}] = cur;
    while (true) {

        char cur_c = input_map[cur.y + dm[cur.dir_cur].second]
                              [cur.x + dm[cur.dir_cur].first];
        if (cur_c == 'S') {
            break;
        }

        cur.x = cur.x + dm[cur.dir_cur].first;
        cur.y = cur.y + dm[cur.dir_cur].second;
        if (m[cur_c].first.dir_cur == cur.dir_cur) {
            loop[{cur.x, cur.y}] = {cur.x, cur.y, cur.dir_cur,
                                    m[cur_c].first.dir_to};
            cur.dir_cur = m[cur_c].first.dir_to;
        }
        if (m[cur_c].second.dir_cur == cur.dir_cur) {
            loop[{cur.x, cur.y}] = {cur.x, cur.y, cur.dir_cur,
                                    m[cur_c].second.dir_to};
            cur.dir_cur = m[cur_c].second.dir_to;
        }
    }
    std::cout << loop.size() / 2 << "\n";
    std::unordered_set<std::pair<int, int>, pair_hash> inside;

    for (auto [k, v] : loop) {
        cur.x = k.first;
        cur.y = k.second;
        cur.dir_cur = rotateLeft(v.dir_cur);
        cur.dir_to = rotateLeft(v.dir_to);

        while (true) {
            cur.x = cur.x + dm[cur.dir_cur].first;
            cur.y = cur.y + dm[cur.dir_cur].second;

            if (loop.count({cur.x, cur.y}) != 0) {
                break;
            }
            if (cur.x < 0 || cur.x >= input_map[0].length() || cur.y < 0 ||
                cur.y >= input_map.size()) {
                break;
            }
            inside.insert({cur.x, cur.y});
        }
        cur.x = k.first;
        cur.y = k.second;

        while (true) {
            cur.x = cur.x + dm[cur.dir_to].first;
            cur.y = cur.y + dm[cur.dir_to].second;

            if (loop.count({cur.x, cur.y}) != 0) {
                break;
            }
            if (cur.x < 0 || cur.x >= input_map[0].length() || cur.y < 0 ||
                cur.y >= input_map.size()) {
                break;
            }
            inside.insert({cur.x, cur.y});
        }
    }

    std::cout << inside.size() << std::endl;

    return 0;
}
