/*
- Keep in mind that this benchmark is not very accurate
- It's not really fair for counting sort, since it only applies to small integers.
- My radix_sort algorithm is substantially faster than std::sort :)
- Implementations which are too slow are ommitted from the benchmark.

Benchmark for 50000 random 32-bit integers:
	sort():             0.003s
	bubble_sort():      3.573s
	counting_sort():    4.745s
	insertion_sort():   0.555s
	merge_sort():       0.013s
	quick_sort():       0.005s
	radix_sort():       0.001s
	selection_sort():   1.568s

Benchmark for 250000 random 32-bit integers:
	sort():             0.020s
	counting_sort():    3.997s
	merge_sort():       0.061s
	radix_sort():       0.005s

Benchmark for 1000000 random 32-bit integers:
	sort():             0.095s
	counting_sort():    3.590s
	merge_sort():       0.229s
	radix_sort():       0.022s

Benchmark for 10000000 random 32-bit integers:
	sort():             0.794s
	counting_sort():    4.234s
	merge_sort():       2.337s
	radix_sort():       0.182s

Benchmark for 10000000 random 32-bit integers:
	sort():             11.679s
	counting_sort():    13.454s
	merge_sort():       25.449s
	radix_sort():       1.814s
*/

#include "BubbleSort.hpp"
#include "CountingSort.hpp"
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
	test(merge_sort);
	test(quick_sort);
	test(radix_sort);
	test(shell_sort);

	return 0;
}
