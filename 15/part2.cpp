#include <iostream>
#include <ranges>
#include <string>
#include <unordered_map>

struct string_hash {
    std::size_t operator()(const std::string &s) const {
        size_t cur = 0;
        for (auto c : s) {
            if (c == '=' || c == '-') {
                break;
            }
            cur += (int)c;
            cur *= 17;
            cur &= 255;
        }
        return cur;
    }
};

int main() {

    std::string line;
    std::unordered_map<std::string, int, string_hash> m;
    m.reserve(256);

    getline(std::cin, line);

    string_hash sh;

    for (const auto step : std::ranges::split_view(line, ',')) {
        std::string tmp = "";
        int num = -1;
        for (auto it = step.begin(); it != step.end(); ++it) {
            if (*it == '=') {
                num = *(++it) - '0';
                m[tmp] = num; 
            } else if (*it == '-') {
                m.erase(tmp);
            }
            tmp += *it;
        }
    }

    uint64_t res = 0;

    for (size_t i = 0; i < m.bucket_count(); ++i) {
        int cnt = m.bucket_size(i);
        for (auto it = m.begin(i); it != m.end(i); ++it) {
            res += (i + 1) * (cnt) * it->second;
            cnt--;
        }
    }

    std::cout << res << std::endl;

    return 0;
}
