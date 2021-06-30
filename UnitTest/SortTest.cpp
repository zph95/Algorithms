#include "pch.h"
#include "CppUnitTest.h"
#include "../Algorithms/Sorting.h"
#include "../Algorithms/RandUtils.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SortTest
{
	TEST_CLASS(SortTest)
	{
	public:
		TEST_METHOD(quickSort)//快速排序
		{
			Sorting sort;
			int length = 10;
			int*  nums = RandUtils::random(length,1,100);
			std::string numsBegin = "数据开始：" + RandUtils::intArrToStr(nums, length);
			Logger::WriteMessage(numsBegin.c_str());
			sort.quickSort(nums, length);
			std::string numsEnd = "排序结果："+ RandUtils::intArrToStr(nums, length);
			Logger::WriteMessage(numsEnd.c_str());
			Assert::IsTrue(RandUtils::isSorted(nums, length));
			delete nums;
		}

		TEST_METHOD(heapSort)//堆排序
		{
			Sorting sort;
			int length = 100;
			int* nums = RandUtils::random(length, 1, 100);
			std::string numsBegin = "数据开始：" + RandUtils::intArrToStr(nums, length);
			Logger::WriteMessage(numsBegin.c_str());
			sort.heapSort(nums, length);
			std::string numsEnd = "排序结果：" + RandUtils::intArrToStr(nums, length);
			Logger::WriteMessage(numsEnd.c_str());
			Assert::IsTrue(RandUtils::isSorted(nums, length));
			delete nums;
		}
	};
}