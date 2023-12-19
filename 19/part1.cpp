#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

struct Part {
    int x;
    int m;
    int a;
    int s;
};

using Compare = bool (*)(int, int);

bool greater(int a, int b) { return a > b; }

bool less(int a, int b) { return a < b; }

std::string filter(const Part &part, const auto &instruction) {
    std::string res;

    for (const auto &comp : instruction) {
        
        if (comp.find('<') == std::string::npos && comp.find('>') == std::string::npos) {
            return comp;
        }

        Compare compare;
        int lhs;

        switch (comp[0]) {
        case 'x':
            lhs = part.x;
            break;
        case 'm':
            lhs = part.m;
            break;
        case 'a':
            lhs = part.a;
            break;
        case 's':
            lhs = part.s;
            break;
        }

        if (comp[1] == '>') {
            compare = greater;
        } else if (comp[1] == '<') {
            compare = less;
        }

        int i = 0;
        int rhs = 0;
        while (!isdigit(comp[i])) {
            ++i;
        }

        while (isdigit(comp[i])) {
            rhs = rhs * 10 + comp[i] - '0';
            ++i;
        }

        if (compare(lhs, rhs)) {
            res = comp.substr(++i);
            break;
        }
    }

    return res;
}

std::string solve(const Part &part, const auto &instructions) {
    std::string res = "in";

    while (res != "A" && res != "R") {
        res = filter(part, instructions.at(res));
    }

    return res;
}

int main() {

    std::string line;
    std::unordered_map<std::string, std::vector<std::string>> instructions;

    while (std::getline(std::cin, line)) {
        if (line == "") {
            break;
        }

        auto pos_open = line.find("{");
        auto key = line.substr(0, pos_open);

        auto pos_close = line.find("}");
        const auto value = line.substr(pos_open + 1, pos_close - pos_open - 1);

        for (const auto &v : std::ranges::split_view(value, ',')) {
            std::string tmp = "";
            for (auto it = v.begin(); it != v.end(); ++it) {
                tmp += *it;
            }
            instructions[key].push_back(tmp);
        }
    }

    std::vector<Part> parts;

    while (getline(std::cin, line)) {
        line = line.substr(1, line.length() - 2);

        Part part;
        int t[4];
        int cnt = 0;
        for (const auto &v : std::ranges::split_view(line, ',')) {
            std::string tmp = "";

            for (auto it = ++ ++v.begin(); it != v.end(); ++it) {
                tmp += *it;
            }
            t[cnt++] = std::stoi(tmp);
        }
        part.x = t[0];
        part.m = t[1];
        part.a = t[2];
        part.s = t[3];
        parts.push_back(part);
    }

    uint64_t sum = 0;

    for (const auto &part : parts) {
        if (solve(part, instructions) == "A") {
            sum += part.x + part.m + part.a + part.s;
        }
    }

    std::cout << sum << std::endl;

    return 0;
}
