#include <iostream>
#include <vector>
#include <queue>
#include "memory"

using namespace std;

#define DIST_PLACEHOLDER 0x3f3f3f3f

using Point = pair<int, int>; // x, y

// https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=865&page=show_problem&problem=4787

int directions[] {0, 1, 0, -1, 0};

bool is_valid_pos(int x, int y, size_t width, size_t height) {
    return !(x < 0 || x >= width || y < 0 || y >= height);
}

struct branch_info {
    branch_info(int distance, const Point &position) : distance(distance), position(position) {}

    bool operator<(const branch_info &rhs) const {
        if (distance<rhs.distance)
            return true;
        if (rhs.distance < distance)
            return false;
        return position < rhs.position;
    }

    bool operator>(const branch_info &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const branch_info &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const branch_info &rhs) const {
        return !(*this < rhs);
    }

    int distance;
    Point position;
};

struct key_navigation_info {
    Point destinations[4];
};

vector<key_navigation_info> create_key_navigation_info(const vector<string> &keyboard) {
    auto height = keyboard.size();
    auto width = keyboard[0].size();

    vector<key_navigation_info> result (height * width);

    auto index = [width](int x, int y) {
        return y * width + x;
    };

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            auto current_key = keyboard[y][x];

            for (int j = 0; j < 4; j++) {
                auto next_x = x;
                auto next_y = y;

                while (is_valid_pos(next_x, next_y, width, height) && keyboard[next_y][next_x] == current_key) {
                    next_x += directions[j];
                    next_y += directions[j + 1];
                }

                if (is_valid_pos(next_x, next_y, width, height)) {
                    result[index(x, y)].destinations[j] = {next_x, next_y};
                } else {
                    result[index(x, y)].destinations[j] = {-1, -1};
                }
            }
        }
    }

    return result;
}

int solve_problem(const vector<string> &keyboard, const string &text) {
    auto height = keyboard.size();
    auto width = keyboard[0].size();

    auto index = [width](int x, int y) {
        return y * width + x;
    };

    auto indexp = [&index](pair<int, int>& p) {
        return index(p.first, p.second);
    };

    auto key_navigation_info = create_key_navigation_info(keyboard);

    priority_queue<branch_info, vector<branch_info>, std::greater<branch_info>> branches;
    branch_info default_branch {0, {0, 0}};
    branches.emplace(default_branch);

    vector<int> distances (width * height, DIST_PLACEHOLDER);
    distances[index(0, 0)] = 0;

    for (int i = 0; i < text.size() + 1; ++i) {
        auto current_key = i == text.size() ? '*' : text[i];

        // bfs from all origin keys
        while (!branches.empty()) {
            auto branch = branches.top();
            branches.pop();

            for (int j = 0; j < 4; j++) {
                auto &p = key_navigation_info[indexp(branch.position)].destinations[j];

                if (p.first == -1) continue;

                if (distances[indexp(p)] > branch.distance + 1) {
                    distances[indexp(p)] = branch.distance + 1;
                    branches.emplace(branch.distance + 1, p);
                }
            }
        }

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                if (current_key == keyboard[y][x]) {
                    distances[index(x, y)]++; // press the key

                    pair<int, int> p {x, y};
                    branches.emplace(distances[index(x, y)], p);
                } else {
                    distances[index(x, y)] = DIST_PLACEHOLDER;
                }
            }
        }
    }

    auto result = DIST_PLACEHOLDER;
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (keyboard[y][x] == '*') {
                result = min(result, distances[index(x, y)]);
            }
        }
    }

    return result;
}

int main() {
    int r; // rows
    int c; // columns

    while (cin >> r >> c) {
        string line;

        vector<string> keyboard;
        while (r--) {
            cin >> line;
            keyboard.push_back(std::move(line));
        }

        cin >> line;
        auto result = solve_problem(keyboard, line);
        cout << result << endl;
    }

    return 0;
}
