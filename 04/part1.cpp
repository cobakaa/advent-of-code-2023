#include <iostream>
#include <string>
#include <unordered_map>

int main() {

    std::string line;
    int res = 0;
    while (getline(std::cin, line)) {
        int i = 0;
        int tmp = 0;
        while (line[i] != ':') {
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
            while (isdigit(line[i])) {
                num += line[i];
                i++;
            }
            if (m.count(num) != 0) {
                if (tmp == 0) {
                    tmp = 1;
                } else {
                    tmp <<= 1;
                }
            }
        }
                res += tmp;
    }

    std::cout << res << std::endl;

    return 0;
}
