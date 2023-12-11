#include <iostream>
#include <unordered_map>
#include <vector>

#define F_TIMES 1'000'000

uint64_t diff_in_one_dir(const auto &v, size_t size, uint64_t h_in_data) {
    uint64_t res = 0;

    uint64_t h_sum = h_in_data;

    for (size_t i = 0; i < size - 1;) {
        uint64_t d = 0;
        for (size_t j = i + 1; j < size; ++j) {
            if (v[j] != 0) {
                break;
            }
            d++;
        }

        if (d > 0) {
            d *= F_TIMES;
        }

        h_in_data -= v[i];
        res += (d + 1) * h_in_data * (h_sum - h_in_data);

        i += d / F_TIMES + 1;
    }

    return res;
}

int main() {

    std::string line;
    std::vector<uint64_t> h_in_cols(256, 0);
    std::vector<uint64_t> h_in_rows(256, 0);
    uint64_t rows = 0;
    uint64_t cols = 0;
    uint64_t h_sum = 0;
    while (getline(std::cin, line)) {
        if (cols == 0) {
            cols = line.length();
        }
        for (size_t i = 0; i < line.length(); ++i) {
            if (line[i] == '#') {
                h_in_rows[rows]++;
                h_in_cols[i]++;
                h_sum++;
            }
        }
        rows++;
    }

    std::cout << diff_in_one_dir(h_in_rows, rows, h_sum) +
                     diff_in_one_dir(h_in_cols, cols, h_sum)
              << std::endl;
    return 0;
}
