#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
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

uint64_t dp[256][256][11][4];

void min_path_cost(std::vector<std::vector<uint64_t>> &cost, int n, int m) {

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < 11; k++)
                for (int l = 0; l < 4; l++)
                    dp[i][j][k][l] = UINT64_MAX;

    std::priority_queue<Cell, std::vector<Cell>, CellCompare> pq;

    for (auto &[k, v] : directions) {
        dp[0][0][0][k] = 0;
        pq.push({0, 0, dp[0][0][0][k], 0, k});
    }

    while (!pq.empty()) {
        Cell cell = pq.top();
        pq.pop();
        int x = cell.x;
        int y = cell.y;
        int in_row = cell.in_row;
        Direction k = cell.last_dir;
    
        if (cell.cost > dp[x][y][in_row][k])
            continue;


        Direction dir1 = rotate_by_90(k);
        Direction dir2 = rotate_by_270(k);
        Direction dir3 = k;

        if (in_row < 4) {
            dir1 = NONE;
            dir2 = NONE;
        }

        if (in_row >= 10) {
            dir3 = NONE;
        }

        for (auto &dir : {dir1, dir2, dir3}) {
            
            if (dir == NONE)
                continue;

            int next_x = x + directions[dir].first;
            int next_y = y + directions[dir].second;

            if (next_x < 0 || next_x >= n || next_y < 0 || next_y >= m)
                continue;

            int next_in_row = (dir == k) ? in_row + 1 : 1;
            if (dp[next_x][next_y][next_in_row][dir] >
                dp[x][y][in_row][k] + cost[next_x][next_y]) {
                dp[next_x][next_y][next_in_row][dir] =
                    dp[x][y][in_row][k] + cost[next_x][next_y];
                pq.push({next_x, next_y, dp[next_x][next_y][next_in_row][dir],
                         next_in_row, dir});
            }
        }
    }
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

    int n = cost.size();
    int m = cost[0].size();
    min_path_cost(cost, n, m);

    uint64_t res = UINT64_MAX;
    for (auto &[k, v] : directions) {
        for (int i = 4; i <= 10; i++) {
            res = std::min(res, dp[n - 1][m - 1][i][k]);
        }
    }

    std::cout << res << std::endl;

    return 0;
}
