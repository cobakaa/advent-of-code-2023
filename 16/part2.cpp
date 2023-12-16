#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Mirror {
    int x;
    int y;
    char type;
    bool was_hit_left;
    bool was_hit_right;
};

enum Direction { UP, DOWN, LEFT, RIGHT };

const std::unordered_map<Direction, std::pair<int, int>> directions = {
    {UP, {0, -1}}, {DOWN, {0, 1}}, {LEFT, {-1, 0}}, {RIGHT, {1, 0}}};

template <> struct std::hash<Mirror> {
    std::size_t operator()(const Mirror &m) const {
        return std::hash<int>()(m.x) ^ std::hash<int>()(m.y);
    }
};

Direction rotate_right(Direction dir) {
    if (dir == UP) {
        return RIGHT;
    } else if (dir == DOWN) {
        return LEFT;
    } else if (dir == LEFT) {
        return UP;
    }
    return DOWN;
}

Direction rotate_left(Direction dir) {
    if (dir == UP) {
        return LEFT;
    } else if (dir == DOWN) {
        return RIGHT;
    } else if (dir == LEFT) {
        return DOWN;
    }
    return UP;
}

uint64_t calc_res(auto &lines, auto &mirrors, size_t x, size_t y,
                  Direction dir) {
    uint64_t res = 0;

    if (x < 0 || x >= lines[0].length() || y < 0 || y >= lines.size()) {
        return res;
    }

    char c = lines[y][x];
    if (c == '.') {
        res++;
        lines[y][x] = '#';
        res += calc_res(lines, mirrors, x + directions.at(dir).first,
                        y + directions.at(dir).second, dir);
    } else if (c == '#') {
        res += calc_res(lines, mirrors, x + directions.at(dir).first,
                        y + directions.at(dir).second, dir);
    }

    if (c == '/' || c == '\\') {
        if (c == '/') {
            if (dir == UP || dir == DOWN) {
                dir = rotate_right(dir);
            } else {
                dir = rotate_left(dir);
            }

            if (dir == UP || dir == LEFT) {
                if (mirrors[{x, y}].was_hit_right) {
                    return res;
                }
                mirrors[{x, y}].was_hit_right = true;
            } else {
                if (mirrors[{x, y}].was_hit_left) {
                    return res;
                }
                mirrors[{x, y}].was_hit_left = true;
            }

        } else {
            if (dir == UP || dir == RIGHT) {
                if (mirrors[{x, y}].was_hit_left) {
                    return res;
                }
                mirrors[{x, y}].was_hit_left = true;
            } else {
                if (mirrors[{x, y}].was_hit_right) {
                    return res;
                }
                mirrors[{x, y}].was_hit_right = true;
            }
            if (dir == UP || dir == DOWN) {
                dir = rotate_left(dir);
            } else {
                dir = rotate_right(dir);
            }
        }
        res += calc_res(lines, mirrors, x + directions.at(dir).first,
                        y + directions.at(dir).second, dir);
    } else if (c == '-' || c == '|') {
        bool f = false;
        if (c == '-') {
            if (dir == UP || dir == DOWN) {
                f = true;
                if (mirrors[{x, y}].was_hit_left) {
                    return res;
                }
                mirrors[{x, y}].was_hit_left = true;
            }
        } else {
            if (dir == LEFT || dir == RIGHT) {
                f = true;
                if (mirrors[{x, y}].was_hit_left) {
                    return res;
                }
                mirrors[{x, y}].was_hit_left = true;
            }
        }
        if (f) {
            res += calc_res(
                lines, mirrors, x + directions.at(rotate_right(dir)).first,
                y + directions.at(rotate_right(dir)).second, rotate_right(dir));
            res += calc_res(
                lines, mirrors, x + directions.at(rotate_left(dir)).first,
                y + directions.at(rotate_left(dir)).second, rotate_left(dir));
        } else {
            mirrors[{x, y}].was_hit_right = true;
            res += calc_res(lines, mirrors, x + directions.at(dir).first,
                            y + directions.at(dir).second, dir);
        }
    }

    return res;
}

uint64_t calc_max_res(auto &lines, auto &mirrors) {
    uint64_t max_res = 0;

    for (size_t i = 0; i < lines[0].length(); ++i) {
        std::vector<std::string> input(lines);
        for (auto &[k, v] : mirrors) {
            v.was_hit_left = false;
            v.was_hit_right = false;
        }

        size_t x = i;
        size_t y = 0;
        Direction dir = DOWN;
        uint64_t res = 0;
        res = calc_res(input, mirrors, x, y, dir);
        for (auto &[k, v] : mirrors) {
            if (v.was_hit_left || v.was_hit_right) {
                res++;
            }
        }
        max_res = std::max(max_res, res);
    }

    for (size_t i = 0; i < lines.size(); ++i) {
        std::vector<std::string> input(lines);
        for (auto &[k, v] : mirrors) {
            v.was_hit_left = false;
            v.was_hit_right = false;
        }

        size_t x = 0;
        size_t y = i;
        Direction dir = RIGHT;
        uint64_t res = 0;
        res = calc_res(input, mirrors, x, y, dir);
        for (auto &[k, v] : mirrors) {
            if (v.was_hit_left || v.was_hit_right) {
                res++;
            }
        }
        max_res = std::max(max_res, res);
    }

    for (size_t i = 0; i < lines[lines.size() - 1].length(); ++i) {
        std::vector<std::string> input(lines);
        for (auto &[k, v] : mirrors) {
            v.was_hit_left = false;
            v.was_hit_right = false;
        }

        size_t x = i;
        size_t y = lines.size() - 1;
        Direction dir = UP;
        uint64_t res = 0;
        res = calc_res(input, mirrors, x, y, dir);
        for (auto &[k, v] : mirrors) {
            if (v.was_hit_left || v.was_hit_right) {
                res++;
            }
        }
        max_res = std::max(max_res, res);
    }

    for (size_t i = 0; i < lines.size(); ++i) {
        std::vector<std::string> input(lines);
        for (auto &[k, v] : mirrors) {
            v.was_hit_left = false;
            v.was_hit_right = false;
        }

        size_t x = lines[0].length() - 1;
        size_t y = i;
        Direction dir = LEFT;
        uint64_t res = 0;
        res = calc_res(input, mirrors, x, y, dir);
        for (auto &[k, v] : mirrors) {
            if (v.was_hit_left || v.was_hit_right) {
                res++;
            }
        }
        max_res = std::max(max_res, res);
    }

    return max_res;
}

template <> struct std::hash<std::pair<int, int>> {
    std::size_t operator()(const std::pair<int, int> &p) const {
        return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
    }
};

int main() {

    std::string line;
    std::vector<std::string> lines;

    std::unordered_map<std::pair<int, int>, Mirror> mirrors;

    while (std::getline(std::cin, line)) {
        lines.push_back(line);
        for (size_t i = 0; i < line.size(); ++i) {
            char c = line[i];
            if (c == '/' || c == '\\' || c == '-' || c == '|') {
                Mirror m;
                m.x = i;
                m.y = lines.size() - 1;
                m.type = c;
                m.was_hit_left = false;
                m.was_hit_right = false;
                mirrors.insert({{m.x, m.y}, m});
            }
        }
    }

    uint64_t res = calc_max_res(lines, mirrors);
    std::cout << res << std::endl;
    return 0;
}
