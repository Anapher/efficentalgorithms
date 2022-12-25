// Unsere IMT Namen: vgriebel, skremer2, faez

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <cmath>

using namespace std;

unordered_map<int, int> primeFactors(int n)
{
    unordered_map<int, int> result;

    while (n % 2 == 0)
    {
        result[2]++;
        n = n / 2;
    }

    for (int i = 3; i <= sqrt(n); i = i + 2)
    {
        while (n % i == 0)
        {
            result[i]++;
            n = n / i;
        }
    }

    if (n > 2)
        result[n]++;

    return result;
}

int main()
{
    int n, m = 0;

    while (cin >> n >> m)
    {
        auto primes_m = primeFactors(m);
        bool possible = true;

        for (auto pair : primes_m)
        {
            auto counter = pair.second;
            for (int i = pair.first; i <= n; i += pair.first)
            {
                auto n = i;
                while (n > 1)
                {
                    counter -= 1;

                    n /= pair.first;

                    if (n % pair.first != 0)
                        break;
                }

                if (counter <= 0)
                    break;
            }

            if (counter > 0)
            {
                possible = false;
            }
        }

        if (possible)
        {
            cout << m << " divides " << n << "!" << endl;
        }
        else
        {
            cout << m << " does not divide " << n << "!" << endl;
        }
    }

    return 0;
}
