#include <cstdint>
#include <iostream>
#include <string>

int main() {

    std::string line;
    getline(std::cin, line);

    uint64_t res = 0;
    uint64_t cur = 0;
    
    for (auto c : line) {
        if (c == ',') {
            res += cur;
            cur = 0;
            continue;
        }

        cur += (int)c;
        cur *= 17;
        cur &= 255;
    }

    res += cur;

    std::cout << res << std::endl;


    return 0;
}
