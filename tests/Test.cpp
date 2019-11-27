#include "../src/data-structures/BITRange.hpp"
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 1024;
BITRange<MAXN, int> bit;

int main()
{
    cin.sync_with_stdio(0);
    cin.tie(0);

    int T, N, C, p, q, v, op;
    cin >> T;

    while (T--)
    {
    	cin >> N >> C;
    	while (C--)
    	{
    		cin >> op;
    		if (op == 0)
    		{
    			cin >> p >> q >> v;
    			bit.update(p, q, v);
    		}
    		else
    		{
    			cin >> p >> q;
    			cout << bit.query(p, q) << '\n';
    		}
    	}
    }
    return 0;
}
