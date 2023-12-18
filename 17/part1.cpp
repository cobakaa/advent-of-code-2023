#include <cstddef>
#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <> struct std::hash<std::pair<int, int>> {
    std::size_t operator()(const std::pair<int, int> &p) const {
        return std::hash<int>()(p.first) ^ std::hash<int>()(p.second);
    }
};

enum Direction { RIGHT, DOWN, LEFT, UP, NONE };

Direction rotate_by_180(Direction dir) {
    switch (dir) {
    case RIGHT:
        return LEFT;
    case DOWN:
        return UP;
    case LEFT:
        return RIGHT;
    case UP:
        return DOWN;
    }
    return NONE;
}

Direction rotate_by_90(Direction dir) {
    switch (dir) {
    case RIGHT:
        return DOWN;
    case DOWN:
        return LEFT;
    case LEFT:
        return UP;

    case UP:
        return RIGHT;
    }
    return NONE;
}

Direction rotate_by_270(Direction dir) {
    switch (dir) {
    case RIGHT:
        return UP;
    case DOWN:
        return RIGHT;
    case LEFT:
        return DOWN;
    case UP:
        return LEFT;
    }
    return NONE;
}

std::unordered_map<Direction, std::pair<int, int>> directions = {
    {RIGHT, {0, 1}}, {DOWN, {1, 0}}, {LEFT, {0, -1}}, {UP, {-1, 0}}};

struct Cell {
    int x;
    int y;
    uint64_t cost;
    int in_row;
    Direction last_dir;
};

struct CellCompare {
    bool operator()(const Cell &lhs, const Cell &rhs) const {
        return lhs.cost > rhs.cost;
    }
};

uint64_t min_path_cost(std::vector<std::vector<uint64_t>> &cost, int n, int m) {
    uint64_t dp[n][m];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            dp[i][j] = UINT64_MAX;

    std::priority_queue<Cell, std::vector<Cell>, CellCompare> pq;
    dp[0][0] = cost[0][0];
    pq.push({0, 0, dp[0][0], 0, RIGHT});
    pq.push({0, 0, dp[0][0], 0, DOWN});

    while (!pq.empty()) {
        Cell cell = pq.top();
        pq.pop();
        int x = cell.x;
        int y = cell.y;
        int in_row = cell.in_row;
        Direction k = cell.last_dir;

        Direction dir1 = rotate_by_90(k);
        Direction dir2 = rotate_by_270(k);
        Direction dir3 = NONE;
        if (in_row < 3) {
            dir3 = k;
        }

        for (auto &dir : {dir1, dir2, dir3}) {
            if (dir == NONE)
                continue;

            int next_x = x + directions[dir].first;
            int next_y = y + directions[dir].second;

            if (next_x < 0 || next_x >= n || next_y < 0 || next_y >= m)
                continue;

            if (dp[next_x][next_y] > dp[x][y] + cost[next_x][next_y]) {
                dp[next_x][next_y] = dp[x][y] + cost[next_x][next_y];
                pq.push({next_x, next_y, dp[next_x][next_y],
                         (dir == k) ? in_row + 1 : 0, dir});
            }
        }
    }

    return dp[n - 1][m - 1];
}

int main() {

    std::string line;
    std::vector<std::vector<uint64_t>> cost;

    while (std::getline(std::cin, line)) {
        cost.push_back(std::vector<uint64_t>());
        for (size_t i = 0; i < line.length(); i++) {
            cost[cost.size() - 1].push_back(line[i] - '0');
        }
    }

    uint64_t res = 0;

    res = min_path_cost(cost, cost.size(), cost[0].size());

    std::cout << res << std::endl;

    return 0;
}
