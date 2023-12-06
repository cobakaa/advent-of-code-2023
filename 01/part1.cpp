#include <cctype>
#include <iostream>
#include <string.h>

int main() {

    int res = 0;
    std::string line = "";
    while (std::cin >> line) {
        int first, last;
        int f = 0;
        for (int i = 0; i < line.length(); ++i) {
            if (isdigit(line[i])) {
                if (f == 0) {
                    first = line[i] - '0';
                    f = 1;
                }
                last = line[i] - '0';
            }
        }
        res += first * 10 + last;
    }

    std::cout << res << std::endl;

    return 0;
}

