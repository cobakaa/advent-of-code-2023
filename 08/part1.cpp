#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int main() {

    std::string command;
    std::unordered_map<std::string, std::pair<std::string, std::string>> m;

    getline(std::cin, command);
    std::string line;
    std::getline(std::cin, line);

    uint64_t res = 0;
    while (getline(std::cin, line)) {
        std::string b = line.substr(0, 3);
        std::string l = line.substr(7, 3);
        std::string r = line.substr(12, 3);

        m[b] = {l, r};
    }

    int x = 0;
    std::string cur = "AAA";
    while (cur != "ZZZ") {
        if (command[x] == 'L') {
            cur = m[cur].first;
        } else if (command[x] == 'R') {
            cur = m[cur].second;
        }
        x = (x + 1) % command.length();
        res++;
    }

    std::cout << res << std::endl;

    return 0;
}
