#include <iostream>

#include <bits/stdc++.h>
using namespace std;

int main()
{
    map<char, int> test;
    vector<char> help;
    string a;

    cin >> a;
    int i = 0;
    while (i < a.length())
    {
        if (test.find(a[i]) != test.end())
        {
            test[a[i]]++;
        }
        else
        {
            test.insert({a[i], 1});
            help.push_back(a[i]);
        }
        i++;
    };
    for (auto i = 0; i < help.size(); ++i)
    {
        cout << help[i] << " " << test[help[i]] << " ";
    }

    cout << "\n";
    cin >> i;
    int u;
    vector<int> x;
    for (int j = 0; j < i; j++)
    {

        cin >> u;
        x.push_back(u);
    }

    for (int j = 0; j < i; j++)
    {

        vector<int> y;

        for (auto i = 0; i < help.size(); ++i)
        {
            if (test[help[i]] == x[j])
            {
                y.push_back(i);
            }
        }

        for (int z = 0; z < y.size() - 1; z++)
        {
            int i = y[z] + 1;
            while (i < y[z + 1])
            {
                // cout<<"working";
                if (test[help[i]] > x[j])
                {
                    help.push_back(help[i]);
                    help.erase(i + help.begin());

                    if (y.size() > 2)
                    {
                        for (int k = z + 1; k < y.size(); k++)
                        {
                            y[k]--;
                        }
                    }
                    else
                    {
                        y[z + 1]--;
                    }
                }
                else
                {
                    help.insert(help.begin(), help[i]);
                    help.erase(i + 1 + help.begin());
                    i++;
                }
            }
        }

        for (auto i = 0; i < help.size(); ++i)
        {
            cout << help[i] << " " << test[help[i]] << " ";
        }
        cout << "\n";
    }

    return 0;
}