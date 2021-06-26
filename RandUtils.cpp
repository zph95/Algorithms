#include "RandUtils.h"
#include <cstdlib> 
#include <ctime>
#include<iostream>
#include <sstream>
#include<algorithm>

using namespace std;

//生成范围在[low,high）的n个随机数
int* RandUtils::random(int n, int low, int high){
	int* nums = new int[n];
	srand(time(0));  //设置时间种子
	for (int i = 0; i < n; i++) {
		nums[i] = rand() % (high - low + 1) + low;//生成区间r~l的随机数 
	}
	return nums;
}

void RandUtils::print(int arr[], int length)
{
	for (int i = 0; i < length; i++)
		cout << arr[i] << " ";
	cout << endl;
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
