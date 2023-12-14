#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

void tilt_N(std::vector<std::string> &data) {
    std::vector<int> hn;

    hn.resize(data[0].length());
    std::fill(hn.begin(), hn.end(), -1);

    for (size_t i = 0; i < data.size(); ++i) {

        for (size_t j = 0; j < data[i].length(); ++j) {

            if (data[i][j] == '#') {
                hn[j] = i;
            }

            if (data[i][j] == 'O') {
                int k = hn[j] + 1;
                hn[j]++;
                data[k][j] = 'O';
                if (k != i) {
                    data[i][j] = '.';
                }
            }
        }
    }
}

void tilt_W(std::vector<std::string> &data) {
    std::vector<int> hw;

    hw.resize(data.size());
    std::fill(hw.begin(), hw.end(), -1);

    for (size_t i = 0; i < data[0].length(); ++i) {

        for (size_t j = 0; j < data.size(); ++j) {

            if (data[j][i] == '#') {
                hw[j] = i;
            }

            if (data[j][i] == 'O') {
                int k = hw[j] + 1;
                hw[j]++;
                data[j][k] = 'O';
                if (k != i) {
                    data[j][i] = '.';
                }
            }
        }
    }
}

void tilt_S(std::vector<std::string> &data) {
    std::vector<int> hs;

    hs.resize(data[0].length());
    std::fill(hs.begin(), hs.end(), data.size());

    for (int i = data.size() - 1; i >= 0; --i) {

        for (size_t j = 0; j < data[i].length(); ++j) {

            if (data[i][j] == '#') {
                hs[j] = i;
            }

            if (data[i][j] == 'O') {
                int k = hs[j] - 1;
                hs[j]--;
                data[k][j] = 'O';
                if (k != i) {
                    data[i][j] = '.';
                }
            }
        }
    }
}

void tilt_E(std::vector<std::string> &data) {
    std::vector<int> he;

    he.resize(data.size());
    std::fill(he.begin(), he.end(), data[0].length());

    for (int i = data[0].length() - 1; i >= 0; --i) {

        for (size_t j = 0; j < data.size(); ++j) {

            if (data[j][i] == '#') {
                he[j] = i;
            }

            if (data[j][i] == 'O') {
                int k = he[j] - 1;
                he[j]--;
                data[j][k] = 'O';
                if (k != i) {
                    data[j][i] = '.';
                }
            }
        }
    }
}

void cycle(std::vector<std::string> &data) {
    tilt_N(data);
    tilt_W(data);
    tilt_S(data);
    tilt_E(data);
}

struct vs_hash {
    inline std::size_t operator()(const std::vector<std::string> &v) const {

        std::hash<std::string> hash_s;
        std::vector<int> vs(v.size());

        for (size_t i = 0; i < v.size(); ++i) {
            vs[i] = hash_s(v[i]);
        }

        std::size_t seed = vs.size();
        for (auto &i : vs) {
            seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

uint64_t calc_load(std::vector<std::string> &data) {
    uint64_t res = 0;

    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[i].length(); ++j) {
            if (data[i][j] == 'O') {
                res += data.size() - i;
            }
        }
    }

    return res;
}

#define CYCLES_NUM 1'000'000'000

int main() {

    std::string line;
    std::vector<std::string> data;
    std::unordered_map<std::vector<std::string>, int, vs_hash> m;

    while (getline(std::cin, line)) {
        data.push_back(line);
    }

    m[data] = 0;

    int loop = 0;
    for (int i = 0; i < CYCLES_NUM; ++i) {
        cycle(data);
        if (!m.contains(data)) {
            m[data] = i;
        } else {
            int loop = i - m[data];
            for (int j = 0; j < (CYCLES_NUM - (i + 1 - loop)) % loop; ++j) {
                cycle(data);
            }
            std::cout << calc_load(data) << "\n";
            return 0;

        }
    }

return 0;
}
