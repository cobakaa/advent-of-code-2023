#include <iostream>
#include <string>
#include <unordered_map>

int main() {

    std::string line;
    int res = 0;
    std::unordered_map<int, int> t;
    t[1] = 1;
    int cnt = 0;
    while (getline(std::cin, line)) {
        int i = 5;
        int tmp = 0;
        cnt++;
        std::string card = "";
        while (line[i] == ' ') {
            i++;
        }
        while (isdigit(line[i])) {
            card += line[i];
            i++;
        }
        i++;
        std::unordered_map<std::string, int> m;
        while (line[i] != '|') {
            std::string num = "";
            while (line[i] == ' ') {
                ++i;
            }
            while (isdigit(line[i])) {
                num += line[i];
                ++i;
            }
            m[num] = 1;
        }
        i++;
        while (i < line.length()) {
            while (line[i] == ' ') {
                i++;
            }
            std::string num = "";
            while (line[i] >= '0' && line[i] <= '9') {
                num += line[i];
                i++;
            }
            if (m.count(num) != 0) {
                tmp++;
            }
        }
        t[cnt + 1]++;
        for (int j = 1; j <= tmp; ++j) {
            t[cnt + j] += t[cnt];
        }
    }
    t.erase(cnt+1);

    for (auto x : t) {
        res += x.second;
    }

    std::cout << res << std::endl;

    return 0;
}
