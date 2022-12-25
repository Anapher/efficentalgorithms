#include <cstdio>
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>

using namespace std;

const int prime_factors[] = {2, 3, 5, 7};
const int MAX_VAL = 2000000000;

vector<int> compute_humble_numbers(int max)
{
    vector<int> result;
    result.push_back(1);

    vector<long> q;
    for (auto n : prime_factors)
    {
        q.push_back(n);
    }

    make_heap(q.begin(), q.end(), greater<long>());

    while (result.size() < max)
    {
        pop_heap(q.begin(), q.end(), greater<long>());
        auto top = q.back();
        q.pop_back();

        result.push_back(top);

        for (auto factor : prime_factors)
        {
            auto val = top * factor;

            if (val > MAX_VAL)
                continue;

            if (find(q.begin(), q.end(), val) != q.end())
            {
                continue;
            }

            q.push_back(val);
            push_heap(q.begin(), q.end(), greater<int>());
        }
    }

    return result;
}

string get_number_suffix(int number)
{
    auto x = number % 10;
    auto y = number % 100;

    if (x == 1 && y != 11)
        return "st";
    if (x == 2 && y != 12)
        return "nd";
    if (x == 3 && y != 13)
        return "rd";
    return "th";
}

void print_number(int index, int number)
{
    cout << "The " << index << get_number_suffix(index) << " humble number is " << number << "." << endl;
}

int main()
{
    auto humble_numbers = compute_humble_numbers(5842);

    int index = 0;
    while (cin >> index)
    {
        if (index == 0)
            break;
        print_number(index, humble_numbers[index - 1]);
    }

    return 0;
};