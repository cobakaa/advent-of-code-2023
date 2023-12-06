#include <cctype>
#include <iostream>
#include <string.h>
#include <string>

int main() {

    std::string line;
    int res = 0;
    int red = 12;
    int green = 13;
    int blue = 14;
    while (getline(std::cin, line)) {
        int i = 0;
        while (!isdigit(line[i])) {
            i++;
        }
        std::string game = "";
        bool f = true;
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
                i += 3;
                break;
            case 'g':
                g = num;
                i += 5;
                break;
            case 'b':
                b = num;
                i += 4;
                break;
            }
            if (std::stoi(r) > red || std::stoi(g) > green ||
                std::stoi(b) > blue) {
                f = false;
                break;
            }
        }
        if (f) {
            res += std::stoi(game);
        }
    }

    std::cout << res << std::endl;

    return 0;
}
