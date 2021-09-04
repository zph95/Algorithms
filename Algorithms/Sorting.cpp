#include "Sorting.h"
#include "iostream"
#include "RandUtils.h"
#include <thread>
#include<vector>
using namespace std;

//快速排序
void Sorting::quickSort(int nums[], int length) {
	//sizeof(nums)/sizeof(nums[0]); 如果是指针就不能用了，传入length
	quick_sort(nums, 0, length - 1);
}

void Sorting::quick_sort(int nums[], int low, int high) {

	if (low < high) {
		// 找寻基准数据的正确索引
		int mid = partition(nums, low, high);
		//std::string numsStr = RandUtils::intArrToStr(nums, 10);
		//RandUtils::print(nums, 10);
		quick_sort(nums, low, mid - 1);
		quick_sort(nums, mid + 1, high);

	}
}


void Sorting::parallelQuickSort(int nums[], int length, int threadNum)
{
	parallel_quick_sort(nums, 0, length - 1, 0, threadNum);
}

void Sorting::parallel_quick_sort(int* nums, int low, int high, int threadDeepth, int maxNum) {
	std::thread::id tid = std::this_thread::get_id();
	cout << "thread id=" << tid << "start." <<"thread_deepth =" <<threadDeepth<< endl;
	if (low < high) {
		// 找寻基准数据的正确索引
		int mid = partition(nums, low, high);
		//std::string numsStr = RandUtils::intArrToStr(nums, 10);
		//RandUtils::print(nums, 10);
		if (threadDeepth < maxNum) {
			//最大线程数
			vector<thread> vt;
			vt.push_back(thread(&Sorting::parallel_quick_sort,this, nums, low, mid - 1, threadDeepth + 1, maxNum));
			vt.push_back(thread(&Sorting::parallel_quick_sort,this, nums, mid + 1, high, threadDeepth + 1, maxNum));
			for (int i = 0; i < vt.size(); i++) {
				vt[i].join();
			}
		}
		else {
			quick_sort(nums, low, mid - 1);
			quick_sort(nums, mid + 1, high);
		}
	}
	cout << "thread id=" << tid << " end." << endl;
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

void Sorting::heapAdjust(int* a, int i, int size)  //调整堆 
{
	int lchild = 2 * i + 1;       //i的左孩子节点序号  
	int rchild = 2 * i + 2;     //i的右孩子节点序号 
	int max = i;            //临时变量 ,最大堆
	if (i <= size / 2)          //如果i不是叶节点就不用进行调整    
	{
		if (lchild <= size && a[lchild] > a[max])
		{
			max = lchild;
		}
		if (rchild <= size && a[rchild] > a[max])
		{
			max = rchild;
		}
		if (max != i)
		{
			swap(a[i], a[max]);
			heapAdjust(a, max, size);    //避免调整之后以max为父节点的子树不是堆        
		}
	}
}

void Sorting::buildHeap(int* a, int size)    //建立堆
{
	for (int i= size / 2; i >= 0; i--)    //非叶节点最大序号值为size/2    
	{
		heapAdjust(a, i, size);
	}
}

//堆排序
void Sorting::heapSort(int* a, int length)    
{
	buildHeap(a, length-1);
	for (int i = length -1; i >= 1; i--)
	{
		//cout<<a[0]<<" ";        
		swap(a[0], a[i]);           //交换堆顶和最后一个元素，即每次将剩余元素中的最大者放到最后面 
		buildHeap(a, i - 1);        //将余下元素重新建立为大顶堆         
		heapAdjust(a, 0, i - 1);      //重新调整堆顶节点成为大顶堆   
	}
}

