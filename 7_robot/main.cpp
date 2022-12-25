// Unsere IMT Namen: vgriebel, skremer2, faez

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>

using namespace std;

int orientation_to_int(string &orientation)
{
    if (orientation == "west")
        return 0;
    if (orientation == "north")
        return 1;
    if (orientation == "east")
        return 2;
    if (orientation == "south")
        return 3;

    return -1;
}

int get_shortest_path(vector<vector<bool>> &matrix, int startX, int startY, int destX, int destY, string &orientation)
{
    auto orientation_i = orientation_to_int(orientation);

    int dir_map[][2]{{-1, 0},
                     {0, -1},
                     {1, 0},
                     {0, 1}};

    set<tuple<int, int, int>> visited;
    visited.insert({startX, startY, orientation_i});

    queue<tuple<int, int, int, int>> q;
    q.push({startX, startY, orientation_i, 0});

    while (!q.empty())
    {
        auto next = q.front();
        q.pop();

        auto curr_x = get<0>(next);
        auto curr_y = get<1>(next);
        auto curr_dir = get<2>(next);
        auto curr_dist = get<3>(next);

        auto check_and_visit = [&](int x, int y, int dir)
        {
            if (visited.count({x, y, dir}))
                return;

            visited.insert({x, y, dir});

            q.push({x, y, dir, curr_dist + 1});
        };

        check_and_visit(curr_x, curr_y, (curr_dir + 1) % 4);
        check_and_visit(curr_x, curr_y, (curr_dir - 1) % 4);

        for (auto i = 1; i < 4; i++)
        {
            int newX = curr_x + dir_map[curr_dir][0] * i;
            int newY = curr_y + dir_map[curr_dir][1] * i;

            if (newX < 1 || newX >= matrix[0].size() - 1 || newY < 1 || newY >= matrix.size() - 1)
            {
                break;
            }

            if (matrix[newY][newX] || matrix[newY - 1][newX] || matrix[newY][newX - 1] || matrix[newY - 1][newX - 1])
            {
                break;
            }

            if (newX == destX && newY == destY)
            {
                return curr_dist + 1;
            }

            check_and_visit(newX, newY, curr_dir);
        }
    }

    return -1;
}

int main()
{
    int M, N = 0;

    while (cin >> M >> N)
    {
        if (M == 0 && N == 0)
            break;

        vector<vector<bool>> matrix(M, vector<bool>(N));

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                int occupied;
                cin >> occupied;

                matrix[i][j] = occupied;
            }
        }

        int startX, startY;
        cin >> startY >> startX;

        int destX, destY;
        cin >> destY >> destX;

        string orientation;
        cin >> orientation;

        auto result = get_shortest_path(matrix, startX, startY, destX, destY, orientation);
        cout << result << endl;
    }

    return 0;
}
