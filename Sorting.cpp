#include "Sorting.h"
#include "iostream"
#include "RandUtils.h"

using namespace std;



//快速排序
void Sorting :: quickSort(int nums[],int length) {
	//sizeof(nums)/sizeof(nums[0]); 如果是指针就不能用了，传入length
	quick_sort(nums, 0, length-1);
}

void Sorting :: quick_sort(int nums[], int low, int high) {

	if (low < high) {
		// 找寻基准数据的正确索引
		int mid = partition(nums, low, high);
		//std::string numsStr = RandUtils::intArrToStr(nums, 10);
		//RandUtils::print(nums, 10);
		quick_sort(nums, low, mid - 1);
		quick_sort(nums,  mid + 1, high);
	
	}
}

int Sorting::partition(int nums[], int low, int high) {
	// 基准数据
	int temp = nums[low];
	while (low < high) {
		// 当队尾的元素大于等于基准数据时,向前挪动high指针
		while (low < high && nums[high] >= temp) {
			high--;
		}
		// 如果队尾元素小于tmp了,需要将其赋值给low
		nums[low] = nums[high];
		// 当队首元素小于等于tmp时,向前挪动low指针
		while (low < high && nums[low] <= temp) {
			low++;
		}
		// 当队首元素大于tmp时,需要将其赋值给high
		nums[high] = nums[low];
	}
	// 跳出循环时low和high相等,此时的low或high就是tmp的正确索引位置
	// low位置的值并不是tmp,所以需要将tmp赋值给arr[low]
	nums[low] = temp;
	return low;
}