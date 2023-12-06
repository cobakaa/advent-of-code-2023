#include <iostream>
#include <limits.h>
#include <sstream>
#include <string>
#include <vector>

int main() {

    std::vector<std::pair<int64_t, bool>> source;
    std::string line;
    getline(std::cin, line);
    line = line.substr(6, line.length() - 6);
    std::stringstream ss(line);
    int64_t tmp;
    while (ss >> tmp) {
        source.push_back(std::pair<int64_t, bool>{tmp, false});
    }
    getline(std::cin, line);
    while (getline(std::cin, line)) {
        while (getline(std::cin, line) && line != "") {
            ss.clear();
            ss.str(line);
            int64_t dest, s, gap;
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
                        source.push_back(std::pair<int64_t, bool>(
                            source[i].first + source[i + 1].first - d, false));
                        source.push_back(std::pair<int64_t, bool>(d, false));
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
                            std::pair<int64_t, bool>(source[i].first, false));
                        source.push_back(std::pair<int64_t, bool>(
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
        }
    }

    int64_t min = INT64_MAX;
    for (size_t i = 0; i < source.size(); i += 2) {
        min = std::min(min, source[i].first);
    }

    std::cout << min << std::endl;

    return 0;
}
