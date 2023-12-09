#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int64_t> stringSplit(std::string line) {
    std::vector<int64_t> res;
    std::stringstream ss(line);
    int t;
    while (ss >> t) {
        res.push_back(t);
    }
    return res;
}

bool isZeros(std::vector<int64_t> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] != 0) {
            return false;
        }
    }
    return true;
}

int main() {

    std::string line;
    int64_t res = 0;
    while (getline(std::cin, line)) {
        std::vector<int64_t> seq = stringSplit(line);

        int cnt = 0;
        while (!isZeros(seq)) {
            res += (cnt % 2 == 0) ? (seq[0]) : (-seq[0]);
            for (size_t i = 0; i < seq.size() - 1; ++i) {
                seq[i] = seq[i + 1] - seq[i];
            }
            seq.pop_back();
            cnt++;
        }
    }

    std::cout << res << std::endl;

    return 0;
}
