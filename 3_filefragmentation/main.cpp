#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int compute_result_len(vector<string> &fragments)
{
    int sum = 0;
    for (auto i = 0; i < fragments.size(); i++)
    {
        sum += fragments[i].size();
    }

    return (sum * 2 / fragments.size());
}

bool is_solution_valid(vector<vector<string>> &buckets, string &solution)
{
    for (int i = 1; i < solution.size(); i++)
    {
        vector<int> taken;

        int counter_bucket_index = solution.size() - i;
        auto &counter_bucket = buckets[counter_bucket_index];

        for (auto &fragment : buckets[i])
        {
            bool found = false;

            for (int j = 0; j < counter_bucket.size(); j++)
            {
                if (find(taken.begin(), taken.end(), j) == taken.end())
                {
                    if (counter_bucket[j] + fragment == solution || fragment + counter_bucket[j] == solution)
                    {
                        found = true;
                        taken.push_back(j);
                        break;
                    }
                }
            }

            if (!found)
            {
                return false;
            }
        }
    }
    return true;
}

vector<vector<string>> create_size_buckets(vector<string> &fragments, int result_len)
{
    vector<vector<string>> buckets(result_len + 1);

    for (string &fragment : fragments)
    {
        auto &bucket = buckets[fragment.size()];
        bucket.push_back(fragment);
    }

    return buckets;
}

string solve_fragmentation(vector<string> &fragments)
{
    auto result_len = compute_result_len(fragments);
    auto buckets = create_size_buckets(fragments, result_len);

    auto first_piece = fragments[0];

    for (auto const &second_piece : buckets[result_len - first_piece.size()])
    {
        auto solution1 = first_piece + second_piece;
        if (is_solution_valid(buckets, solution1))
        {
            return solution1;
        }

        auto solution2 = second_piece + first_piece;
        if (is_solution_valid(buckets, solution2))
        {
            return solution2;
        }
    }

    throw std::invalid_argument("no solution possible");
}

int main()
{
    string line;
    getline(cin, line);
    auto first = true;

    int number_cases = stoi(line);

    getline(cin, line); // skip blank line

    for (int i = 0; i < number_cases; i++)
    {
        vector<string> fragments;

        while (getline(cin, line))
        {
            if (line.empty())
                break;

            fragments.push_back(line);
        }

        auto result = solve_fragmentation(fragments);

        if (first)
        {
            first = false;
        }
        else
        {
            cout << "\n\n";
        }
        cout << result;
    }

    return 0;
};