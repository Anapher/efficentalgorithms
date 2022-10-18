#include <cstdio>
#include <iostream>

using namespace std;

int skyline[10001];

int l;
int height;
int r;

int main()
{
    while (cin >> l >> height >> r)
    {
        for (int i = l; i < r; i++)
        {
            skyline[i] = max(skyline[i], height);
        }
    }

    bool first = true;
    for (int i = 0; i <= 10001; i++)
    {
        if (skyline[i - 1] != skyline[i])
        {
            if (first)
            {
                first = false;
            }
            else
            {
                cout << " ";
            }

            cout << i << " " << skyline[i];
        }
    }

    cout << endl;
    return 0;
};