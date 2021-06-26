#pragma once
#include<string>

class RandUtils
{
public:
	static int* random(int n, int low, int high);//生成范围在[low,high）的n个随机数
	static void print(int* a, int length);
	static bool isSorted(int arr[], int length);
	static std::string intArrToStr(int arr[], int length);
};

