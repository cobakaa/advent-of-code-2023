#include <cstdint>
#include <iostream>
#include <sys/types.h>
#include <unordered_set>
#include <vector>

template <> struct std::hash<std::pair<int, int>> {
    size_t operator()(const std::pair<int, int> &p) const {
        return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
    }
};

std::pair<int, int> get_coords(int x, int y, int length, int height) {
    auto x1 = x;
    auto y1 = y;

    if (x >= length) {
        x1 = x % length;
    }

    if (y >= height) {
        y1 = y % height;
    }

    if (x < 0) {
        int mul = abs(x) % length;
        x1 = (length - mul) % length;
    }

    if (y < 0) {
        int mul = abs(y) % height;
        y1 = (height - mul) % height;
    }

    return std::make_pair(x1, y1);
}

int main() {

    std::string line;
    std::vector<std::string> input;
    std::unordered_set<std::pair<int, int>> os;

    while (std::getline(std::cin, line)) {
        input.push_back(line);
        for (size_t i = 0; i < line.length(); ++i) {
            if (line[i] == 'S') {
                os.insert(std::make_pair(i, input.size() - 1));
            }
        }
    }

    std::unordered_set<std::pair<int, int>> dirs = {
        {-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    std::vector<std::pair<int, int>> added;
    std::vector<std::pair<int, int>> removed;
    std::vector<u_int64_t> res;
    int d = 0;
    int d1;
    for (int i = 0; i < 26501365; ++i) {
        for (auto &[x, y] : os) {

            for (auto &[dx, dy] : dirs) {
                auto [x1, y1] =
                    get_coords(x + dx, y + dy, input[0].length(), input.size());
                if (input[y1][x1] != '#') {
                    added.push_back(std::make_pair(x + dx, y + dy));
                }
            }

            removed.push_back(std::make_pair(x, y));
        }

        for (auto &[x, y] : removed) {
            os.erase(std::make_pair(x, y));
        }

        for (auto &[x, y] : added) {
            os.insert(std::make_pair(x, y));
        }
        added.clear();
        removed.clear();

        if ((i + 1) % input.size() == 65) {
            d1 = os.size();
            res.push_back(d1 - d);
            uint64_t sum = 0;
            int j = input.size() + 65;
            if (res.size() == 3) {
                sum = (res[1] + (res[2] - res[1]) *
                                    ((26501365 - j) / input.size()) / 2) *
                          ((26501365 - j) / input.size() + 1) +
                      res[0];
                std::cout << sum << std::endl;
                return 0;
            }
            d = d1;
        }
    }

    std::cout << os.size() << std::endl;

    return 0;
}
