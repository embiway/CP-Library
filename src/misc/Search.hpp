/*
	A collection of different searching methods, using binary search.
	The lower_bound() and upper_bound() methods are implemented using
	binary search. TODO: Interpolation Search, Jump Search, Ternary Search.
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

namespace Search
{
	template <typename T, typename F>
	T binary_search(T lo, T hi, F f)
	{
		T mid;
		while (lo < hi)
		{
			mid = lo + (hi - lo) / 2;
			auto temp = f(mid);

			if (temp < 0) lo = mid + 1;
			else if (temp > 0) hi = mid - 1;
			else return mid;
		}
		return -1;
	}

	template <typename T, typename F>
	T lower_bound(T lo, T hi, F f)
	{
		T mid;
		while (lo < hi)
		{
			mid = lo + (hi - lo) / 2;
			if (f(mid)) hi = mid;
			else        lo = mid + 1;
		}
		return lo;
	}

	template <typename T, typename F>
	T upper_bound(T lo, T hi, F f)
	{
		T mid;
		while (lo < hi)
		{
			mid = lo + (hi - lo) / 2;
			if (f(mid)) lo = mid + 1;
			else        hi = mid;
		}
	}
}
