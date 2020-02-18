/*
	BitArray for memory and speed efficient bit operations in an array
	Functions mimic std::bitset, with some extra functionality
	Time complexity: O(1) or O(N/64), depending on which function
	 where N is the number of bits (size of the array)
*/

#pragma once
#include <bits/stdc++.h>

template <const int N>
struct BitArray {
	static const int SZ = (N >> 6) + 1; uint64_t bits[SZ]; static const uint64_t ALL_ONES = 18446744073709551615ULL;
	BitArray() { std::fill(bits, bits + SZ, 0); }
	BitArray(const BitArray<N> &b) { for (int i = 0; i < SZ; i++) bits[i] = b.bits[i]; }
	BitArray(const uint64_t val) { std::fill(bits, bits + SZ, 0); for (int i = 0, j = 63 - __builtin_clzll(val); i < 64; i++, j--) if (val & (1ULL << j)) bits[0] |= (1ULL << i); }
	BitArray(const std::string &s) {
		std::fill(bits, bits + SZ, 0);
		for (int i = 0; i < int(s.size()); i++) if (s[i] == '1') bits[i >> 6] |= (1ULL << (i & 63));
	}
	bool operator[] (int i) const { return bits[i >> 6] & (1ULL << (i & 63)); }
	BitArray operator& (const BitArray &b) const { return BitArray(*this) &= b; }
	BitArray &operator&= (const BitArray &b) { for (int i = 0; i < SZ; i++) bits[i] &= b.bits[i]; return *this; }
	BitArray operator| (const BitArray &b) const { return BitArray(*this) |= b; }
	BitArray &operator|= (const BitArray &b) { for (int i = 0; i < SZ; i++) bits[i] |= b.bits[i]; return *this; }
	BitArray operator^ (const BitArray &b) const { return BitArray(*this) ^= b; }
	BitArray &operator^= (const BitArray &b) { for (int i = 0; i < SZ; i++) bits[i] ^= b.bits[i]; return *this; }
	BitArray operator<< (int i) const { return BitArray(*this) <<= i; }
	BitArray &operator<<= (int i) {
		int idx = i >> 6, off = i & 63, lim = SZ - idx - 1;
		for (int j = 0; j < lim; j++) bits[j] = (bits[j + idx] >> off) | (bits[j + idx + 1] << (63 - off));
		bits[lim] = bits[SZ - 1] >> off; std::fill(bits + lim + 1, bits + SZ, 0);
		return *this;
	}
	BitArray operator>> (int i) const { return BitArray(*this) >>= i; }
	BitArray &operator>>= (int i) {
		int idx = i >> 6, off = i & 63;
		for (int j = SZ - 1; j > idx; j--) bits[j] = (bits[j - idx] << off) | (bits[j - idx - 1] >> (63 - off));
		bits[idx] = bits[0] << off; std::fill(bits, bits + idx, 0);
		return *this;
	}
	BitArray operator~ () const { return BitArray(*this).flip(); }
	bool operator== (const BitArray& b) { for (int i = 0; i < SZ; i++) if (bits[i] != b.bits[i]) return false; return true; }
	bool operator!= (const BitArray& b) { for (int i = 0; i < SZ; i++) if (bits[i] != b.bits[i]) return true; return false; }
	bool all() { for (int i = 0; i < SZ; i++) if (bits[i] != ALL_ONES) return false; return true; }
	bool any() { for (int i = 0; i < SZ; i++) if (bits[i] != 0) return true; return false; }
	int count() { int cnt = 0; for (int i = 0; i < SZ; i++) cnt += __builtin_popcountll(bits[i]); return cnt; }
	BitArray flip() { for (int i = 0; i < SZ; i++) bits[i] = ~bits[i]; return *this; }
	BitArray flip(int i) { bits[i >> 6] ^= (1ULL << (i & 63)); return *this; }
	BitArray flip(int l, int r) {
		int lidx = l >> 6, ridx = r >> 6, loff = l & 63, roff = r & 63;
		if (lidx == ridx) bits[lidx] ^= ((1ULL << (r - l + 1)) - 1) << loff;
		else {
			bits[lidx] ^= ~((1ULL << loff) - 1);
			for (int i = lidx + 1; i < ridx; i++) bits[i] |= ALL_ONES;
			bits[ridx] ^= ((1ULL << (roff + 1)) - 1);
		}
		return *this;
	}
	bool none() { for (int i = 0; i < SZ; i++) if (bits[i] != 0) return false; return true; }
	BitArray reset() { for (int i = 0; i < SZ; i++) bits[i] = 0; return *this; }
	BitArray reset(int i) { bits[i >> 6] &= ((1ULL << (i & 63)) - 1); return *this; }
	BitArray reset(int l, int r) {
		int lidx = l >> 6, ridx = r >> 6, loff = l & 63, roff = r & 63;
		if (lidx == ridx) bits[lidx] &= ~(((1ULL << (r - l + 1)) - 1) << loff);
		else {
			bits[lidx] &= ((1ULL << loff) - 1);
			for (int i = lidx + 1; i < ridx; i++) bits[i] |= ALL_ONES;
			bits[ridx] &= ~((1ULL << (roff + 1)) - 1);
		}
		return *this;
	}
	BitArray set() { for (int i = 0; i < SZ; i++) bits[i] = ALL_ONES; return *this; }
	BitArray set(int i) { bits[i >> 6] |= (1ULL << (i & 63)); return *this; }
	BitArray set(int l, int r) {
		int lidx = l >> 6, ridx = r >> 6, loff = l & 63, roff = r & 63;
		if (lidx == ridx) bits[lidx] |= ((1ULL << (r - l + 1)) - 1) << loff;
		else {
			bits[lidx] |= ~((1ULL << loff) - 1);
			for (int i = lidx + 1; i < ridx; i++) bits[i] |= ALL_ONES;
			bits[ridx] |= ((1ULL << (roff + 1)) - 1);
		}
		return *this;
	}
	int size() { return N; }
	bool test(int i) { return (*this)[i]; }
	std::string to_string() const { std::string res = ""; for (int i = 0; i < N; i++) res.push_back((*this)[i] + '0'); return res; }
	uint64_t to_ullong() { return bits[0] & ((1 << N) - 1); }
	friend std::istream &operator>> (std::istream &is, const BitArray<N> &b) { std::string s; is >> s; b = BitArray<N>(s); return is; }
	friend std::ostream &operator<< (std::ostream &os, const BitArray<N> &b) { return os << b.to_string(); }
};
