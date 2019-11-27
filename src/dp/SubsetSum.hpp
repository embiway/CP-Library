/*
    Implementations for variations on the Subset Sum problem.
    The sums() function returns all possible subset sums, which uses inplace_merge if array must 
    be sorted. The check() function returns whether a subset sum exists which equals 'sum', as 
    well as std::bitset to test for sums below 'sum' (for queries). Note the default bitset size 
    is 1000000, which can be modified in the code. The count() function counts the number of subset 
    sums which sum to k, using gp_hash_table (a.k.a. hash map).
    
    - vector<T> sums(const auto& a, const int sz, const bool sorted)
        Time:  O(N * 2 ^ N)
        Space: O(2 ^ N)
        
    - pair<bool, bitset<MAXSUM>> check(const auto& a, const int sz, const T sum)
        Time:  O(N * MAXSUM / 32)
        Space: O(1)
        
    - long long count(const auto& a, const int sz, const T sum)
        Time:  O(N * 2 ^ N)
        Space: O(2 ^ N)
*/

#pragma once
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;

namespace SubsetSum
{
    static const int MAXSUM = 1000000;  // change this value if needed
    static bitset<MAXSUM> bit;
    
    template <typename T>
    vector<T> sums(const auto& a, const int sz, const bool sorted)
    {
        vector<T> res(1 << sz);
        for (int i = 0, curr = 1; i < sz; i++)
        {
            for (int j = 0; j < curr; j++)         res[j + curr] = res[j];
            for (int j = curr; j < curr << 1; j++) res[j] += a[i];
            
            if (sorted) inplace_merge(res.begin(), res.begin() + curr, res.begin() + (curr << 1));
            curr <<= 1;
        }
        return res;
    }
    
    template <typename T>
    pair<bool, bitset<MAXSUM>> check(const auto& a, const int sz, const T sum)
    {
        bit.reset();
        bit[0] = 1;
        
        for (int i = 0; i < sz; i++) bit |= bit << a[i];
        return make_pair(bit[sum], bit);
    }
    
    template <typename T>
    long long count(const auto& a, const int sz, const T sum)
    {
        __gnu_pbds::gp_hash_table<T, long long> left, right;
        left[0] = 1, right[0] = 1;
        
        for (int i = 0; i < sz >> 1; i++)
        {
            auto L = left;
            for (const auto& l : L) left[l.first + a[i]] += l.second;
        }
        
        for (int i = sz >> 1; i < sz; i++)
        {
            auto R = right;
            for (const auto& r : R) right[r.first + a[i]] += r.second;
        }
        
        long long res = 0;
        for (const auto& l : left)
        {
            if (right.find(sum - l.first) != right.end()) res += l.second * right[sum - l.first];
        }
        return res;
    }
};
