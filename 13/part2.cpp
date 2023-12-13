#include <iostream>
#include <string>
#include <vector>

int strs_diff(std::string &l, std::string &r) {
    int res = 0;
    for (size_t i = 0; i < l.size(); ++i) {
        if (l[i] != r[i]) {
            res++;
        }
    }

    return res;
}

uint64_t get_horizontal(auto &map, int &can_change) {
    uint64_t res = 0;

    for (size_t i = 0; i < map.size() - 1; ++i) {
        int diff = strs_diff(map[i], map[i + 1]);
        if (diff <= 1 && can_change) {
            int k = i + 1;
            int j = i;
            bool f = true;
            bool fc = false;
            while (j >= 0 && k < map.size()) {
                int d = strs_diff(map[j], map[k]);

                if (d == 1 && can_change) {
                    can_change--;
                    fc = true;
                    d--;
                }
                if (d != 0) {
                    f = false;
                    break;
                }

                --j;
                ++k;
            }
            if (fc) {
                if (f) {
                    return i + 1;
                } else {
                    can_change++;
                }
            }
        }
    }

    return res;
}

int main() {

    std::string line;
    uint64_t hres = 0;
    uint64_t vres = 0;

    while (getline(std::cin, line)) {
        std::vector<std::string> map;
        map.push_back(line);
        size_t ml = line.length();
        while (std::getline(std::cin, line)) {
            if (line == "") {
                break;
            }
            map.push_back(line);
        }

        int can_change = 1;
        hres += get_horizontal(map, can_change);
        if (can_change) {
            std::vector<std::string> rotated_map;
            for (size_t x = 0; x < ml; ++x) {
                std::string tmp = "";
                for (int y = map.size() - 1; y >= 0; --y) {

                    tmp.push_back(map[y][x]);
                }
                rotated_map.push_back(tmp);
            }

            vres += get_horizontal(rotated_map, can_change);
        }
    }

    std::cout << vres + 100 * hres << std::endl;

    return 0;
}
