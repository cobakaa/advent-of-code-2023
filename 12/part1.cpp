#include <iostream>
#include <string>
#include <vector>

uint64_t dp(size_t i, size_t j, auto &str, auto &nums, auto &cache) {
    if (i >= str.length()) {
        if (j >= nums.size()) {
            return 1;
        }
        return 0;
    }

    if (cache[i][j] != -1) {
        return cache[i][j];
    }

    uint64_t res = 0;

    if (str[i] == '.') {
        res = dp(i + 1, j, str, nums, cache);
    } else {
        if (str[i] == '?') {
            res += dp(i + 1, j, str, nums, cache);
        }

        if (j < nums.size()) {
            int cnt = 0;
            for (size_t k = i; k < str.length(); ++k) {
                if ((cnt >= nums[j] && str[k] == '?') || str[k] == '.' ) {
                    break;
                }
                cnt++;
            }

            if (cnt == nums[j]) {
                if (i + cnt < str.length() && str[i + cnt] != '#') {
                    res += dp(i + cnt + 1, j + 1, str, nums, cache);
                } else {
                    res += dp(i + cnt, j + 1, str, nums, cache);
                }
            }
        }
    }
    cache[i][j] = res;
    return res;
}

uint64_t solve(std::string& str, std::vector<uint64_t>& nums) {

    std::vector<std::vector<uint64_t>> cache(
        str.length(), std::vector<uint64_t>(nums.size() + 1, -1));

    return dp(0, 0, str, nums, cache);
}

int main() {

    std::string line;
    uint64_t res = 0;
    while (getline(std::cin, line)) {
        std::string str;
        std::vector<uint64_t> v;
        uint64_t tmp = 0;
        
        size_t i = 0;
        while (line[i] != ' ') {
            i++;
        }

        str = line.substr(0, i);
        ++i;
        while (i < line.length()) {
            while (isdigit(line[i])) {
                tmp = tmp * 10 + (uint64_t)(line[i] - '0');
                i++;
            }
            v.push_back(tmp);
            tmp = 0;
            ++i;            
        }

       
        res += solve(str, v);
    }
    
    std::cout << res << std::endl;


    return 0;
}
