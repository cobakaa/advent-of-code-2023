#include <algorithm>
#include <iostream>
#include <vector>

int main() {

    std::string line;
    std::vector<int> hs;
    std::vector<int> ores;

    int cnt = 0;
    while (getline(std::cin, line)) {
        
        ores.push_back(0);

        if (cnt == 0) {
            hs.resize(line.length());
            std::fill(hs.begin(), hs.end(), -1);
        }

        for (size_t i = 0; i < line.length(); ++i) {

            if (line[i] == '#') {
                hs[i] = cnt;
            }

            if (line[i] == 'O') {
                int j = hs[i] + 1;
                ores[j]++;
                hs[i]++;
            }
        }

        cnt++;
    }

    uint64_t res = 0;
    for (size_t i = 0; i < ores.size(); ++i) {
        res += (ores.size() - i) * ores[i];
    }

    std::cout << res << std::endl;

    return 0;
}
