#include <iostream>
#include <string.h>
#include <string>
#include <unordered_map>
#include <vector>

int main() {

    int64_t res = 0;
    std::unordered_map<int, std::vector<int>> m;
   std::vector<std::string> lines;
    std::string line;
    int cnt = 0;
    while (std::cin >> line) {
        if (cnt == 0) {
            std::string s(line.length() + 2, '.');
            cnt++;
            lines.push_back(s);
        }
        line = "." + line + ".";
        lines.push_back(line);
    }
    lines.push_back(std::string(line.length(), '.'));



    for (int i = 1; i < lines.size() + 1; ++i) {
        for (int j = 1; j < lines[i].length() + 1; ++j) {

            if (!isdigit(lines[i][j])) {
                continue;
            }
            std::string num = "";
            while (isdigit(lines[i][j])) {
                num += lines[i][j];
                j++;
            }
            for (int k = j - num.length() - 1; k <= j; ++k) {
                if (lines[i - 1][k] == '*') {
                    m[lines[i - 1].length() * (i - 1) + k].push_back(
                        std::stoi(num));
                    break;
                }
            }
            for (int k = j - num.length() - 1; k <= j; ++k) {
                if (lines[i + 1][k] == '*') {
                    m[lines[i + 1].length() * (i + 1) + k].push_back(
                        std::stoi(num));
                    break;
                }
            }
            if (lines[i][j - num.length() - 1] == '*') {
                m[lines[i].length() * i + j - num.length() - 1]
                    .push_back(std::stoi(num));
            }

            if (lines[i][j] == '*') {
                m[lines[i].length() * i + j].push_back(
                    std::stoi(num));
            }
        }
    }

    for (auto x : m) {
        if (x.second.size() == 2) {
            res += (int64_t)x.second[0] * (int64_t)x.second[1];
        }
    }

    std::cout << res << std::endl;

    return 0;
}
