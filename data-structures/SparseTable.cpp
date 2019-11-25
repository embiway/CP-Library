/*
    Sparse Table implementation on Range Minimum Query (can be modified
    for other query types).
    Also stores table of 'log2' for faster queries.
    
    - CONSTRUCTION
        Time:  O(1)
        Space: O(N * log N)
    
    - void init(auto& arr)
        Time:  O(N * log N)
        Space: O(1)
        
    - T query(int l, int r)
        Time:  O(1)
        Space: O(1)
*/

template <const int MAXN, typename T>
struct SparseTable
{
    static const int LG = 32 - __builtin_clz(MAXN);
    int lg[MAXN + 1];
    T st[MAXN][LG];
    
    void init(auto& arr)
    {
        for (int i = 0; i < MAXN; i++) st[i][0] = arr[i];
        lg[1] = 0;
        for (int i = 2; i <= MAXN; i++) lg[i] = lg[i >> 1] + 1;
        
        for (int j = 1; j <= LG; j++)
        {
            for (int i = 0; i + (1 << j) <= MAXN; i++)
            {
                st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    
    T query(int l, int r)
    {
        int k = lg[r - l + 1];
        return min(st[l][k], st[r - (1 << k) + 1][k]);
    }
};
