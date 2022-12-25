// Unsere IMT Namen: vgriebel, skremer2, faez

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <cmath>

using namespace std;

// edge pairs are (node, weight)
int calculate_min_trips(vector<vector<pair<int, int>>> &edges, int S, int D, int T)
{
    unordered_set<int> visited_edges;

    auto pair_comparator = [](pair<int, int> &p1, pair<int, int> &p2)
    {
        return p1.first < p2.first;
    };

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(pair_comparator)> q(pair_comparator); // throughput, vertex pairs
    q.push({T, S});

    while (!q.empty())
    {
        auto node = q.top();
        q.pop();

        auto current_throughput = node.first;
        auto nodeId = node.second;

        // cout << "node: " << nodeId << " throughput " << current_throughput << endl;

        if (nodeId == D)
        {
            return ceil(T / (double)(current_throughput - 1));
        }

        for (auto &edge : edges[nodeId])
        {
            auto edge_hash = (edge.first + 239) * (nodeId + 239);

            if (visited_edges.count(edge_hash) > 0)
                continue;

            visited_edges.insert(edge_hash);

            auto new_throughput = min(edge.second, current_throughput);
            q.push({new_throughput, edge.first});
            // cout << "       has node: " << edge.first << " throughput " << new_throughput << endl;
        }
    }

    return -1;
}

int main()
{
    int N, R = 0;
    int scenario = 1;

    while (cin >> N >> R)
    {
        if (N == 0 && R == 0)
        {
            break;
        }

        vector<vector<pair<int, int>>> edges(N + 1);

        while (R--)
        {
            int c1, c2, p;
            cin >> c1 >> c2 >> p;

            edges[c1].push_back({c2, p});
            edges[c2].push_back({c1, p});
        }

        int S, D, T;
        cin >> S >> D >> T;

        auto result = calculate_min_trips(edges, S, D, T);

        cout << "Scenario #" << scenario++ << endl;
        cout << "Minimum Number of Trips = " << result << endl
             << endl;
    }

    return 0;
}
