#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

template <> struct std::hash<std::pair<int, int>> {
    size_t operator()(const std::pair<int, int> &p) const {
        return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
    }
};

enum Direction { RIGHT, DOWN, LEFT, UP };

std::unordered_map<Direction, std::pair<int, int>> directions = {
    {UP, {0, -1}}, {DOWN, {0, 1}}, {LEFT, {-1, 0}}, {RIGHT, {1, 0}}};

int main() {

    std::string line;
    // std::unordered_set<std::pair<uint64_t, uint64_t>> picture;
    std::vector<std::pair<uint64_t, uint64_t>> picture;
    std::pair<uint64_t, uint64_t> pos = {0, 0};
    // picture.insert(pos);
    uint64_t perimeter = 0;

    while (std::getline(std::cin, line)) {
        uint64_t num = 0;
        Direction dir;

        uint64_t cnt = 0;
        while (line[cnt++] != '#') {
        }

        for (uint64_t i = 0; i < 5; ++i) {
            num *= 16;
            if (isdigit(line[cnt + i])) {
                num += line[cnt + i] - '0';
            } else {
                num += line[cnt + i] - 'a' + 10;
            }
        }

        dir = (Direction)(line[cnt + 5] - '0');

        pos.first += directions[dir].first * num;
        pos.second += directions[dir].second * num;
        // picture.insert(pos);
        picture.push_back(pos);
        perimeter += num;
    }

    uint64_t sum = 0;
    for (size_t i = 0; i < picture.size(); ++i) {
        uint64_t lhs =
            picture[i].first * picture[(i + 1) % picture.size()].second;
        uint64_t rhs =
            picture[(i + 1) % picture.size()].first * picture[i].second;
        sum += lhs - rhs;
    }


    std::cout << sum / 2 + perimeter / 2 + 1 << std::endl;

    return 0;
}
