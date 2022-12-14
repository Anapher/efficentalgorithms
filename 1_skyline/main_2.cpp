#include <iostream>
#include <vector>
#include <set>
#include <tuple>

using std::cout;
using std::endl;
using namespace std;

struct building
{
    int left;
    int height;
    int right;
};

template <class ContainerT>
void tokenize(const std::string &str, ContainerT &tokens,
              const std::string &delimiters = " ", bool trimEmpty = false)
{
    std::string::size_type pos, lastPos = 0, length = str.length();

    using value_type = typename ContainerT::value_type;
    using size_type = typename ContainerT::size_type;

    while (lastPos < length + 1)
    {
        pos = str.find_first_of(delimiters, lastPos);
        if (pos == std::string::npos)
        {
            pos = length;
        }

        if (pos != lastPos || !trimEmpty)
            tokens.push_back(value_type(str.data() + lastPos,
                                        (size_type)pos - lastPos));

        lastPos = pos + 1;
    }
}

building parse_line(string &s)
{
    vector<string> result;
    tokenize(s, result, " ", true);

    if (result.size() != 3)
    {
        throw invalid_argument("Invalid amount of elements");
    }

    return {stoi(result[0]), stoi(result[1]), stoi(result[2])};
}

void print_entry(pair<int, int> &p)
{
    cout << p.first << " " << p.second << " ";
}

void solve_problem(vector<building> &input)
{
    auto cmp_right_asc = [](building a, building b)
    {
        if (a.right == b.right)
        {
            if (a.left == b.left)
            {
                return a.height < b.height;
            }

            return a.left < b.left;
        }

        return a.right < b.right;
    };

    auto cmp_height_desc = [](building a, building b)
    {
        if (a.height == b.height)
        {
            if (a.left == b.left)
            {
                return a.right > b.right;
            }

            return a.left > b.left;
        }

        return a.height > b.height;
    };

    // these two guys must always be synced and contain the exact same elements
    set<building, decltype(cmp_right_asc)> active_buildings_right(cmp_right_asc);
    set<building, decltype(cmp_height_desc)> active_buildings_height(cmp_height_desc);

    pair<int, int> last_point; // x, y
    int index = 0;

    while (!active_buildings_right.empty() || index < input.size())
    {
        int pos;

        if (active_buildings_right.empty())
        {
            auto &next = input[index++];

            pos = next.left;

            active_buildings_right.insert(next);
            active_buildings_height.insert(next);
        }
        else if (index == input.size())
        {
            auto &next = *active_buildings_right.begin();
            pos = next.right;

            active_buildings_right.erase(next);
            active_buildings_height.erase(next);
        }
        else
        {
            auto &next_right_building = *active_buildings_right.begin();

            if (input[index].left > next_right_building.right)
            {
                pos = next_right_building.right;

                active_buildings_right.erase(next_right_building);
                active_buildings_height.erase(next_right_building);
            }
            else if (input[index].left < next_right_building.right)
            {
                auto next = input[index++];
                pos = next.left;
                active_buildings_right.insert(next);
                active_buildings_height.insert(next);
            }
        }

        int height = active_buildings_height.empty() ? 0 : (*active_buildings_height.begin()).height;

        if (last_point.first == pos)
        {
            last_point.second = max(last_point.second, height);
        }
        else
        {

            if (!(last_point.first == 0 && last_point.second == 0))
            {
                if (last_point.second == height)
                {
                    continue;
                }

                print_entry(last_point);
            }

            last_point.first = pos;
            last_point.second = height;
        }
    }

    if (!(last_point.first == 0 && last_point.second == 0))
    {
        print_entry(last_point);
    }
}

int main()
{
    vector<building> buildings;

    string line;
    while (getline(cin, line))
    {
        auto t = parse_line(line);
        buildings.push_back(t);
    }

    solve_problem(buildings);
    return 0;
}
