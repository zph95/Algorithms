#include "RandUtils.h"
#include <cstdlib> 
#include <ctime>
#include<iostream>
#include <sstream>
#include<algorithm>
#include<thread>
#include<vector>
using namespace std;


void RandUtils::random2(int* nums, int begin, int end, int low, int high){
	std::thread::id tid = std::this_thread::get_id();
	cout << "thread id=" << tid << "start." << endl;

	srand((unsigned)time(NULL) + begin);

	for (int i = begin; i < end; i++) {
		nums[i] = rand() % (high - low + 1) + low;
	}

	cout << "thread id=" << tid << " end." << endl;
}
	
//生成范围在[low,high）的n个随机数
int* RandUtils::random(int n, int low, int high){
	int* nums = new int[n];
	srand(time(0));  //设置时间种子
	for (int i = 0; i < n; i++) {
		nums[i] = rand() % (high - low + 1) + low;//生成区间r~l的随机数 
	}
	return nums;
}

void RandUtils::print(int* a, int length)
{
	for (int i = 0; i < length; i++)
		cout << a[i] << " ";
	cout << endl;
}

int* RandUtils::parallelRandom(int n, int low, int hight, int threadNum) {
	vector<thread> vt;
	int t = threadNum;
	int* nums = new int[n];
	for (int i = 0; i < t; i++) {
		vt.push_back(thread(random2, nums, i * n / t, (i + 1) * n / t, low, hight));
	}
	for (int i = 0; i < vt.size(); i++) {
		vt[i].join();
	}
	return nums;
}

bool RandUtils::isSorted(int arr[], int length)
{
	for (int i = 0; i < length -1; i++) {
		if (arr[i] > arr[i + 1]) {
			return false;
		}
	}
	return true;
}

//int[] convert to string
string RandUtils::intArrToStr(int arr[], int length) {
	stringstream s_stream;
	for (int i = 0; i < length; i++) {
		s_stream << arr[i] << " ";
	}
	string string_temp = s_stream.str();
	s_stream.clear();
	//s_stream>>string_temp;  // 也可以实现
	return string_temp;
}


