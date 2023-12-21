#include <iostream>
#include <unordered_set>
#include <vector>

template <> struct std::hash<std::pair<int, int>> {
    size_t operator()(const std::pair<int, int> &p) const {
        return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
    }
};

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
    for (int i = 0; i < 64; ++i) {
        for (auto &[x, y] : os) {
            for (auto &[dx, dy] : dirs) {
                if ((x + dx >= 0 && x + dx < input[0].length()) &&
                    (y + dy >= 0 && y + dy < input.size()) &&
                    input[y + dy][x + dx] != '#') {
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
    }

    std::cout << os.size() << std::endl;

    return 0;
}
