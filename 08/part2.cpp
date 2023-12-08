#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

uint64_t GCD(uint64_t a, uint64_t b) {
    while (a > 0 && b > 0) {
        if (a > b) {
            a = a % b;
        } else {
            b = b % a;
        }
    }

    return (uint64_t)std::max(a, b);
}

int main() {

    std::string command;
    std::unordered_map<std::string, std::pair<std::string, std::string>> m;

    getline(std::cin, command);
    std::string line;
    std::getline(std::cin, line);

    std::vector<std::string> v;
    uint64_t res = 0;
    while (getline(std::cin, line)) {
        std::string b = line.substr(0, 3);
        std::string l = line.substr(7, 3);
        std::string r = line.substr(12, 3);

        m[b] = {l, r};
        if (b[2] == 'A') {
            v.push_back(b);
        }
    }

    int x = 0;
    std::vector<int> recs(v.size(), 0);
    while (true) {
        for (size_t i = 0; i < v.size(); ++i) {
            if (command[x] == 'L') {
                v[i] = m[v[i]].first;
            } else if (command[x] == 'R') {
                v[i] = m[v[i]].second;
            }
            if (v[i][2] == 'Z' && recs[i] == 0) {
                recs[i] = res + 1;
            }
        }

        bool t = true;
        for (int i = 0; i < recs.size(); ++i) {
            if (recs[i] == 0) {
                t = false;
                break;
            }
        }
        if (t)
            break;

        x = (x + 1) % command.length();
        res++;
    }

    res = recs[0];
    for (size_t i = 1; i < recs.size(); ++i) {
        res = uint64_t(res / GCD(res, recs[i])) * uint64_t(recs[i]);
    }

    std::cout << res << std::endl;

    return 0;
}
