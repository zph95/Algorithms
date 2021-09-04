#pragma once
class Sorting
{
public:
	void quickSort(int  nums[],int length);
	void parallelQuickSort(int nums[], int length, int threadNum);
	void heapSort(int* a, int size);
private:
	void quick_sort(int nums[], int low, int high);
	void parallel_quick_sort(int* nums, int low, int high, int threadDeep, int maxNum);
	int partition(int nums[],  int low, int high);
	void buildHeap(int* a, int size);
	void heapAdjust(int* a, int i, int size);
};

