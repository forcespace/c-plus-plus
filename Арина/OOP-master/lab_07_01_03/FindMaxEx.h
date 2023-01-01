#pragma once
#include <vector>
#include <algorithm>

template <typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	if (arr.empty())
	{
		return false;
	}

	//maxValue = *std::max_element(std::begin(arr), std::end(arr), less);

	/*maxValue = arr[0];
	for (const auto& el : arr)
		if (less(maxValue, el))
			maxValue = el;*/

	auto max = arr.begin();
	for (auto it = arr.cbegin(); it != arr.cend(); it++)
		if (less(*max, *it))
			max = it;

	maxValue = *max;


	return true;
}