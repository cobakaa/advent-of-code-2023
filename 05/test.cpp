#include <cstddef>
#include <iostream>
#include <limits.h>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

int main() {

    std::vector<std::pair<uint, bool>> source;
    std::string line;
    std::getline(std::cin, line);
    line = line.substr(6, line.length() - 6);
    std::stringstream ss(line);
    uint tmp;
    while (ss >> tmp) {
        source.push_back(std::pair<uint, bool>{tmp, false});
    }
    std::getline(std::cin, line);
    while (std::getline(std::cin, line)) {
        while (std::getline(std::cin, line) && line != "") {
            ss.clear();
            ss.str(line);
            uint dest, s, gap;
            ss >> dest;
            ss >> s;
            ss >> gap;
            for (size_t i = 0; i < source.size(); i += 2) {
                bool f = false;
                if (source[i].first >= s && source[i].first <= s + gap - 1 &&
                    !source[i].second) {
                    f = true;
                    int d = source[i].first + source[i + 1].first - s - gap;
                    if (source[i].first + source[i+1].first > s + gap) {
                        source.push_back(std::pair<uint, bool>(
                            source[i].first + source[i + 1].first - d, false));
                        source.push_back(std::pair<uint, bool>(d, false));
                        source[i + 1].first -= d;
                    }
                }

                if (source[i].first + source[i + 1].first - 1 >= s &&
                    source[i].first + source[i + 1].first <= s + gap &&
                    !source[i].second) {
                    f = true;
                    int d = source[i].first + source[i + 1].first - s;
                    if (source[i].first < s) {
                        source.push_back(
                            std::pair<uint, bool>(source[i].first, false));
                        source.push_back(std::pair<uint, bool>(
                            source[i + 1].first - d, false));
                        source[i + 1].first = d;
                        source[i].first = s;
                    }
                }
                if (f) {

                    source[i + 1].second = true;
                    source[i].first += dest - s;
                    source[i].second = true;
                }
            }
        }

        for (size_t i = 0; i < source.size(); ++i) {
            source[i].second = false;
            std::cout << source[i].first << " ";
        }
        std::cout << "\n------------------------------\n";
    }

    uint min = UINT_MAX;
    for (size_t i = 0; i < source.size(); i += 2) {
        min = std::min(min, source[i].first);
    }

    std::cout << min << std::endl;

    return 0;
}
