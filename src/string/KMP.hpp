/*
	Knuth-Morris-Pratt for string searching
	Time complexity: O(M) init, O(N) search, search_all
	 where N and M are the sizes of the text and pattern, respectively
*/

#pragma once
#include <bits/stdc++.h>

template <const int MAXN, const int INDEXING>
struct KMP {
	int LPS[MAXN], pat[MAXN], plen; std::vector<int> matches;
	template <typename It> void init(It st, It en) {
		std::copy(st, en, pat); LPS[0] = -1, plen = en - st;
		for (int i = 0, j = -1; i < plen; i++, j++, LPS[i] = j) {
			while (j >= 0 && pat[i] != pat[j]) j = LPS[j];
		}
	}
	template <typename It> int search(It st, It en) {
		for (int i = 0, j = 0; i < en - st; i++, j++) {
			while (j >= 0 && *(st + i) != pat[j]) j = LPS[j];
			if (j == plen - 1) return abs(i - j + INDEXING);
		}
		return -1;
	}
	template <typename It> std::vector<int> search_all(It st, It en) {
		matches.clear();
		for (int i = 0, j = 0; i < en - st; i++, j++) {
			while (j >= 0 && *(st + i) != pat[j]) j = LPS[j];
			if (j == plen - 1) matches.push_back(abs(i - j + INDEXING));
		}
		return matches;
	}
};
