/*
	Implementation of Radix Sort sorting algorithm.
*/

#pragma once
#include <bits/stdc++.h>

using namespace std;

void radix_sort32(auto arr[], int N)
{

}

void radix_sort64(auto arr[], int N)
{

}

template <typename T>
void radix_sort(T arr[], int N)
{
	if (typeid(T) == typeid(int)) radix_sort32(arr, N);
	else						  radix_sort64(arr, N);
}
