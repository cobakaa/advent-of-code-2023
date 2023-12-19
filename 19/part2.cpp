#include <deque>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

struct Part {
    uint64_t x[2] = {1, 4000};
    uint64_t m[2] = {1, 4000};
    uint64_t a[2] = {1, 4000};
    uint64_t s[2] = {1, 4000};
};

using Compare = bool (*)(int, int);

bool greater(int a, int b) { return a > b; }

bool less(int a, int b) { return a < b; }

struct InstructionRes {
    std::string instruction;
    Part part1;
    Part part2;
    bool inst = false;
};

InstructionRes filter(Part part, const auto &instruction) {
    InstructionRes res = {instruction, part, part};

    if (instruction.find('<') == std::string::npos &&
        instruction.find('>') == std::string::npos) {
        return {instruction, part, part, false};
    }
    int i = 0;
    uint64_t rhs = 0;

    while (!isdigit(instruction[i])) {
        ++i;
    }

    while (isdigit(instruction[i])) {
        rhs = rhs * 10 + instruction[i] - '0';
        ++i;
    }

    if (instruction[1] == '>') {
        switch (instruction[0]) {
        case 'x':
            res.part1.x[0] = rhs + 1;
            res.part2.x[1] = rhs;
            break;
        case 'm':
            res.part1.m[0] = rhs + 1;
            res.part2.m[1] = rhs;
            break;
        case 'a':
            res.part1.a[0] = rhs + 1;
            res.part2.a[1] = rhs;
            break;
        case 's':
            res.part1.s[0] = rhs + 1;
            res.part2.s[1] = rhs;
            break;
        }

    } else if (instruction[1] == '<') {
        switch (instruction[0]) {
        case 'x':
            res.part1.x[1] = rhs - 1;
            res.part2.x[0] = rhs;
            break;
        case 'm':
            res.part1.m[1] = rhs - 1;
            res.part2.m[0] = rhs;
            break;
        case 'a':
            res.part1.a[1] = rhs - 1;
            res.part2.a[0] = rhs;
            break;
        case 's':
            res.part1.s[1] = rhs - 1;
            res.part2.s[0] = rhs;
            break;
        }
    }

    res.instruction = instruction.substr(++i);
    res.inst = true;
    return res;
}

struct dqType {
    std::string command;
    Part part;
    int coms_num;
};

uint64_t solve(auto &instructions) {

    uint64_t sum = 0;
    std::deque<dqType> dq;
    Part part;
    int coms_num = instructions.at("in").size();
    dq.push_front({"in", part, coms_num});
    while (!dq.empty()) {

        auto [command, part, cn] = dq.front();
        dq.pop_front();

        auto [new_command, part1, part2, changed] = filter(part, command);

        if (changed) {
            for (int i = 0; i < cn; ++i) {
                dq[i].part = part2;
            }
        }

        if (new_command == "A") {
            sum +=
                (part1.x[1] - part1.x[0] + 1) * (part1.m[1] - part1.m[0] + 1) *
                (part1.a[1] - part1.a[0] + 1) * (part1.s[1] - part1.s[0] + 1);
            continue;
        }

        if (new_command == "A" || new_command == "R") {
            continue;
        }

        int size = (int)instructions.at(new_command).size();
        for (int i = size - 1; i >= 0; --i) {
            std::string inst = instructions[new_command][i];
            dq.push_front({inst, part1, size - 1 - i});
        }
    }

    return sum;
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

    uint64_t sum = 0;

    sum = solve(instructions);

    std::cout << sum << std::endl;

    return 0;
}
