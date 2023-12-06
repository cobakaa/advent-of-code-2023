#include <iostream>
#include <string>
#include <vector>

int isDigit(std::string line, int x) {
    const std::vector<std::string> digits = {
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine"
    };
    int res = -1;
    for (int i = 0; i < digits.size(); ++i) {
        int f = 1;
        for (int j = 0; j < digits[i].length(); ++j) {
            if (x + j >= line.length() || line[x + j] != digits[i][j]) {
                f = 0;
                break;
            }
        }
        if (f) {
            res = i + 1;
        }
    }

    return res;
}

int main() {

    int res = 0;
    std::string line = "";
    while (std::cin >> line) {
        int first, last;
        int f = 0;
        for (int i = 0; i < line.length(); ++i) {
            if (line[i] >= '0' && line[i] <= '9') {
                if (f == 0) {
                    first = line[i] - '0';
                    f = 1;
                }
                last = line[i] - '0';
            } else {
                int d = isDigit(line, i);
                if (d > 0) {
                    if (f == 0) {
                        first = d;
                        f = 1;
                    }
                    last = d;
                }
            }
        }
        res += first * 10 + last;
    }

    std::cout << res << std::endl;

    return 0;
}
