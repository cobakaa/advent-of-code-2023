#include <iostream>
#include <string>
#include <vector>

uint64_t get_horizontal(auto &map) {
    uint64_t res = 0;

    for (size_t i = 0; i < map.size() - 1; ++i) {
        if (map[i] == map[i + 1]) {
            int k = i + 2;
            int j = i - 1;
            bool f = true;
            while (j >= 0 && k < map.size()) {
                if (map[j] != map[k]) {
                    f = false;
                    break;
                }
                --j;
                ++k;
            }
            if (f) {
                return i + 1;
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

        uint64_t h = get_horizontal(map);
        hres += h;
        if (h == 0) {
            std::vector<std::string> rotated_map;
            for (size_t x = 0; x < ml; ++x) {
                std::string tmp = "";
                for (int y = map.size() - 1; y >= 0; --y) {

                    tmp.push_back(map[y][x]);
                }
                rotated_map.push_back(tmp);
            }

            vres += get_horizontal(rotated_map);
        }
    }

    std::cout << vres + 100 * hres << std::endl;

    return 0;
}
