#include <iostream>
#include <sstream>
#include <string>
#include <vector>

bool isWinnable(uint64_t tb, uint64_t tr, uint64_t d) {
    return (tr - tb) * tb > d;
}

uint64_t findL(uint64_t t, uint64_t d, uint64_t l, uint64_t r) {
    if (r <= l + 1) {
        return l;
    }

    uint64_t m = (l + r) / 2;
    if (isWinnable(m, t, d)) {
        r = m;
    } else {
        l = m;
    }

    return findL(t, d, l, r);
}

void parseInput(uint64_t &t, uint64_t &d) {

    std::string line;
    getline(std::cin, line);
    int i = 0;
    while (!isdigit(line[i])) {
        i++;
    }
    while (i < line.length()) {
        if (isdigit(line[i])) {
            t = t * 10 + (line[i] - '0');
        }
        i++;
    }
    getline(std::cin, line);
    i = 0;
    while (!isdigit(line[i])) {
        i++;
    }
    while (i < line.length()) {
        if (isdigit(line[i])) {
            d = d * 10 + (line[i] - '0');
        }
        i++;
    }
}

int main() {

    uint64_t t = 0;
    uint64_t d = 0;

    parseInput(t, d);

    uint64_t res = 1;
    uint64_t l = findL(t, d, 0, t / 2);
    uint64_t w = (t / 2 - l) * 2;
    if (t % 2 == 0) {
        w--;
    }
    res = w;

    std::cout << res << "\n";

    return 0;
}
