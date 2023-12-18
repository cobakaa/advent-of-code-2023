#include <cmath>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

template <> struct std::hash<std::pair<int, int>> {
    size_t operator()(const std::pair<int, int> &p) const {
        return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
    }
};

enum Direction { UP, DOWN, LEFT, RIGHT };

std::unordered_map<Direction, std::pair<int, int>> directions = {
    {UP, {0, -1}}, {DOWN, {0, 1}}, {LEFT, {-1, 0}}, {RIGHT, {1, 0}}};

int main() {

    std::string line;
    // std::unordered_set<std::pair<int, int>> picture;
    std::vector<std::pair<int, int>> picture;
    std::pair<int, int> pos = {0, 0};
    // picture.insert(pos);
    int perimeter = 0;
    while (std::getline(std::cin, line)) {
        int num = 0;
        Direction dir;
        char d = line[0];

        for (int i = 2; i < line.length(); i++) {
            if (line[i] == ' ') {
                break;
            }
            num *= 10;
            num += line[i] - '0';
        }

        switch (d) {
        case 'U':
            dir = UP;
            break;
        case 'D':
            dir = DOWN;
            break;
        case 'L':
            dir = LEFT;
            break;
        case 'R':
            dir = RIGHT;
            break;
        }

        pos.first += directions[dir].first * num;
        pos.second += directions[dir].second * num;
        // picture.insert(pos);
        picture.push_back(pos);
        perimeter += num;
    }

    int sum = 0;
    for (size_t i = 0; i < picture.size(); ++i) {
        sum += picture[i].first * picture[(i + 1) % picture.size()].second -
               picture[(i + 1) % picture.size()].first * picture[i].second;
    }

    std::cout << std::abs(sum) / 2 + perimeter / 2 + 1 << std::endl;

    return 0;
}
