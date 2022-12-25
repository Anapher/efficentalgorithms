#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

int main()
{
    int number_cases;
    cin >> number_cases;

    for (int i = 0; i < number_cases; i++)
    {
        int streets;
        int avenues;
        int friends_count;

        cin >> streets >> avenues >> friends_count;

        vector<pair<int, int>> streetPoints(friends_count);

        for (int i = 0; i < friends_count; ++i)
            cin >> streetPoints[i].first >> streetPoints[i].second;

        int j = (friends_count >> 1) - 1;

        if (friends_count & 1)
            ++j;

        sort(streetPoints.begin(), streetPoints.end(), [](pair<int, int> &a, pair<int, int> &b)
             { return a.first < b.first; });

        auto x = streetPoints[j].first;

        sort(streetPoints.begin(), streetPoints.end(), [](pair<int, int> &a, pair<int, int> &b)
             { return a.second < b.second; });

        auto y = streetPoints[j].second;

        cout << "(Street: " << x << ", Avenue: " << y << ")\n";
    }

    return 0;
};