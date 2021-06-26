#pragma once
class Sorting
{
public:
	void quickSort(int  nums[],int length);

private:
	void quick_sort(int nums[], int low, int high);
	int partition(int nums[],  int low, int high);
};

