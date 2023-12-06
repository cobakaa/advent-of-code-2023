#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void parseInput(std::vector<uint> &t, std::vector<uint> &d) {

    std::string line;
    std::stringstream ss;

    getline(std::cin, line);
    line = line.substr(9, line.length() - 9);
    ss.clear();
    ss.str(line);
    uint tmp;
    while (ss >> tmp) {
        t.push_back(tmp);
    }

    getline(std::cin, line);
    line = line.substr(9, line.length() - 9);
    ss.clear();
    ss.str(line);
    while (ss >> tmp) {
        d.push_back(tmp);
    }
}

bool isWinnable(uint tb, uint tr, uint d) { return (tr - tb) * tb > d; }

uint findL(uint t, uint d, uint l, uint r) {
    if (r <= l + 1) {
        return l;
    }

    uint m = (l + r) / 2;
    if (isWinnable(m, t, d)) {
        r = m;
    } else {
        l = m;
    }

    return findL(t, d, l, r);
}

int main() {

    std::vector<uint> times;
    std::vector<uint> dists;

    parseInput(times, dists);

    uint res = 1;
    for (size_t i = 0; i < times.size(); ++i) {
        uint l = findL(times[i], dists[i], 0, times[i] / 2);
        uint w = (times[i] / 2 - l) * 2;
        if (times[i] % 2 == 0) {
            w--;
        }
        res *= w;
    }

    std::cout << res << "\n";

    return 0;
}
