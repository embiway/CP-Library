/*
    A relatively fast prime-sieve algorithm using the Sieve of Eratosthenes.
    It uses a custom bitset to decrease the space complexity by a factor of 64.
    Submitting this to SPOJ - TDPRIMES gets accepted in 0.31s. TODO: learn wheel
    factorization.
    
    - CONSTRUCTION
        Time:  O(1)
        Space: O(N / 64)
    
    - void init()
        Time:  O(N * log log N)
        Space: O(1)
        
    - vector<int> get_primes()
        Time:  O(N)
        Space: O(N)
        
    - inline bool ifc(int x)
        Time:  O(1)
        Space: O(1)
        
    - inline bool isc(int x)
        Time:  O(1)
        Space: O(1)
*/

template <const int MAXN>
struct Sieve
{
    int is_prime[MAXN >> 6];
    
    void init()
    {
        memset(is_prime, 0, sizeof(is_prime));
        for (int i = 3; i * i <= MAXN; i += 2)
        {
            if (!ifc(i))
            {
                for (int j = i * i, k = i << 1; j <= MAXN; j += k) isc(j);
            }
        }
    }
    
    vector<int> get_primes()
    {
        vector<int> res;
        res.push_back(2);
        
        for (int i = 3; i <= MAXN; i += 2)
        {
            if (!ifc(i)) res.push_back(i);
        }
        return res;
    }
    
    inline bool ifc(int x) { return is_prime[x >> 6] & (1 << ((x >> 1) & 31)); }
    
    inline bool isc(int x) { return is_prime[x >> 6] |= (1 << ((x >> 1) & 31)); }
};
