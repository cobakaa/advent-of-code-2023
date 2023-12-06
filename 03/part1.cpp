#include <cctype>
#include <iostream>
#include <string.h>
#include <vector>

int main() {

    int64_t res = 0;
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
                if (!isdigit(lines[i - 1][k]) &&
                    lines[i - 1][k] != '.') {
                    res += (int64_t)std::stoi(num);
                    break;
                }
            }
            for (int k = j - num.length() - 1; k <= j; ++k) {
                if (!isdigit(lines[i+1][k]) &&
                    lines[i + 1][k] != '.') {
                    res += (int64_t)std::stoi(num);
                    break;
                }
            }
            if ((!isdigit(lines[i][j - num.length() - 1])) &&
                lines[i][j - num.length() - 1] != '.') {
                res += (int64_t)std::stoi(num);
            }

            if ((!isdigit(lines[i][j])) && lines[i][j] != '.') {
                res += (int64_t)std::stoi(num);
            }
        }
    }

    std::cout << res << std::endl;

    return 0;
}
