#include <algorithm>
#include <cctype>
#include <cstdint>
#include <iostream>
#include <string>
#include <stdint.h>

int main() {

    std::string line;
    int res = 0;

    while (getline(std::cin, line)) {
        int red = 0;
        int green = 0;
        int blue = 0;
        int i = 5;
        std::string game = "";
        while (line[i] != ':') {
            game += line[i];
            ++i;
        }
        i += 2;
        while (i < line.length()) {
            std::string r = "0";
            std::string g = "0";
            std::string b = "0";
            std::string num = "";
            while (!isdigit(line[i])) {
                i++;
            }
            while (isdigit(line[i])) {
                num += line[i];
                ++i;
            }
            ++i;
            switch (line[i]) {
            case 'r':
                r = num;
                red = std::max(red, std::stoi(r));
                i += 3;
                break;
            case 'g':
                g = num;
                green = std::max(green, std::stoi(g));
                i += 5;
                break;
            case 'b':
                b = num;
                blue = std::max(blue, std::stoi(b));
                i += 4;
                break;
            }
        }
        res += red * green * blue;
    }

    std::cout << res << std::endl;

    return 0;
}
