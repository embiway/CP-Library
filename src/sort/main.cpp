/*
Note: The benchmark is not completely accurate, there is often a lot of variation

Benchmark for 50000 random 32-bit integers:
sort():             0.003s
bubble_sort():      3.379s
counting_sort():    3.841s
insertion_sort():   0.635s
merge_sort():       0.012s
quick_sort():       0.004s
radix_sort():       0.001s
shell_sort():       0.007s
selection_sort():   2.110s
Benchmark for 250000 random 32-bit integers:
sort():             0.020s
counting_sort():    5.545s
insertion_sort():   14.877s
merge_sort():       0.054s
quick_sort():       0.026s
radix_sort():       0.004s
shell_sort():       0.038s
Benchmark for 1000000 random 32-bit integers:
sort():             0.089s
counting_sort():    4.400s
merge_sort():       0.258s
quick_sort():       0.118s
radix_sort():       0.024s
shell_sort():       0.183s
Benchmark for 10000000 random 32-bit integers:
sort():             1.035s
counting_sort():    5.068s
merge_sort():       2.499s
quick_sort():       1.226s
radix_sort():       0.196s
shell_sort():       2.089s
Benchmark for 100000000 random 32-bit integers:
sort():             12.357s
counting_sort():    10.908s
merge_sort():       26.574s
quick_sort():       13.709s
radix_sort():       1.849s
shell_sort():       24.630s
*/

#include "BubbleSort.hpp"
#include "CountingSort.hpp"
#include "HeapSort.hpp"
#include "InsertionSort.hpp"
#include "MergeSort.hpp"
#include "ShellSort.hpp"
#include "QuickSort.hpp"
#include "RadixSort.hpp"
#include "SelectionSort.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

template <typename It>
void print(It st, It en) {
	for (It i = st; i != en; i++) cout << *i << ' ';
}

int main() {
	{
		int arr[] = {5, 36, 1, 98, 97, 34, 27, 33, 21};
		sort(arr, arr + 9);
		assert(is_sorted(arr, arr + 9));
	}

	{
		int arr[] = {5, 36, 1, 98, 97, 34, 27, 33, 21};
		bubble_sort(arr, arr + 9);
		assert(is_sorted(arr, arr + 9));
	}

	{
		int arr[] = {-5, -36, -1, -98, -97, 34, 27, 33, 21};
		counting_sort(arr, arr + 9);
		assert(is_sorted(arr, arr + 9));
	}

	{
		int arr[] = {5, 36, 1, 98, 97, 34, 27, 33, 21};
		counting_sort(arr, arr + 9);
		assert(is_sorted(arr, arr + 9));
	}

	{
		int arr[] = {5, 36, 1, 98, 97, 34, 27, 33, 21};
		heap_sort(arr, arr + 9);
		assert(is_sorted(arr, arr + 9));
	}

	{
		int arr[] = {5, 36, 1, 98, 97, 34, 27, 33, 21};
		insertion_sort(arr, arr + 9);
		assert(is_sorted(arr, arr + 9));
	}

	{
		int arr[] = {5, 36, 1, 98, 97, 34, 27, 33, 21};
		merge_sort(arr, arr + 9);
		assert(is_sorted(arr, arr + 9));
	}

	{
		int arr[] = {5, 36, 1, 98, 97, 34, 27, 33, 21};
		quick_sort(arr, arr + 9);
		assert(is_sorted(arr, arr + 9));
	}

	{
		int arr[] = {-5, -36, -1, -98, -97, 34, 27, 33, 21};
		radix_sort(arr, arr + 9);
		assert(is_sorted(arr, arr + 9));
	}

	{
		int arr[] = {5, 36, 1, 98, 97, 34, 27, 33, 21};
		shell_sort(arr, arr + 9);
		assert(is_sorted(arr, arr + 9));
	}

	{
		int arr[] = {5, 36, 1, 98, 97, 34, 27, 33, 21};
		radix_sort_unsigned(arr, arr + 9);
		assert(is_sorted(arr, arr + 9));
	}

	{
		int arr[] = {5, 36, 1, 98, 97, 34, 27, 33, 21};
		selection_sort(arr, arr + 9);
		assert(is_sorted(arr, arr + 9));
	}

#define test(sort_function) {                               \
	clock_t start = clock();                                \
	sort_function(v.begin(), v.end());                      \
	double t = (double) (clock() - start) / CLOCKS_PER_SEC; \
	cout << setw(20) << left << #sort_function "(): ";      \
	cout << fixed << t << "s" << endl;                      \
	assert(is_sorted(v.begin(), v.end()));                  \
	v = v2;                                                 \
}
	vector<int> v, v2;

	for (int i = 0; i < 50000; i++) v.push_back((rand() & 0x7fff) | ((rand() & 0x7fff) << 15));
	v2 = v;

	cout << "Benchmark for 50000 random 32-bit integers:" << endl;
	cout.precision(3);
	test(sort);
	test(bubble_sort);
	test(counting_sort);
	test(heap_sort);
	test(insertion_sort);
	test(merge_sort);
	test(quick_sort);
	test(radix_sort);
	test(shell_sort);
	test(selection_sort);

	v.clear(); v2.clear();
	for (int i = 0; i < 250000; i++) v.push_back((rand() & 0x7fff) | ((rand() & 0x7fff) << 15));
	v2 = v;
/**/
	cout << "Benchmark for 250000 random 32-bit integers:" << endl;
	cout.precision(3);
	test(sort);
	test(counting_sort);
	test(heap_sort);
	test(insertion_sort);
	test(merge_sort);
	test(quick_sort);
	test(radix_sort);
	test(shell_sort);

	v.clear(); v2.clear();
	for (int i = 0; i < 1000000; i++) v.push_back((rand() & 0x7fff) | ((rand() & 0x7fff) << 15));
	v2 = v;

	cout << "Benchmark for 1000000 random 32-bit integers:" << endl;
	cout.precision(3);
	test(sort);
	test(counting_sort);
	test(heap_sort);
	test(merge_sort);
	test(quick_sort);
	test(radix_sort);
	test(shell_sort);

	v.clear(); v2.clear();
	for (int i = 0; i < 10000000; i++) v.push_back((rand() & 0x7fff) | ((rand() & 0x7fff) << 15));
	v2 = v;

	cout << "Benchmark for 10000000 random 32-bit integers:" << endl;
	cout.precision(3);
	test(sort);
	test(counting_sort);
	test(heap_sort);
	test(merge_sort);
	test(quick_sort);
	test(radix_sort);
	test(shell_sort);

	v.clear(); v2.clear();
	for (int i = 0; i < 100000000; i++) v.push_back((rand() & 0x7fff) | ((rand() & 0x7fff) << 15));
	v2 = v;

	cout << "Benchmark for 100000000 random 32-bit integers:" << endl;
	cout.precision(3);
	test(sort);
	test(counting_sort);
	test(heap_sort);
	test(merge_sort);
	test(quick_sort);
	test(radix_sort);
	test(shell_sort);

	return 0;
}
