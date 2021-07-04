#include "pch.h"
#include "CppUnitTest.h"
#include "../Algorithms/BigIntCalculate.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:

		TEST_METHOD(Add)//¼Ó
		{
			string a = "789546321", b = "15462897444";
			string exp ="16252443765";
			string ret = BigIntCalculate::add(a, b);
			Assert::AreEqual(exp, ret);
		}

		TEST_METHOD(Subtract)//¼õ
		{
			string a = "789546321", b = "15462897444";
			string exp = "-14673351123";
			string ret = BigIntCalculate::subtract(a, b);
			Assert::AreEqual(exp, ret);
		}

		TEST_METHOD(Multiply)//³Ë
		{
			string a = "789546321", b = "15462897444";
			string exp = "12208673788910503524";
			string ret = BigIntCalculate::multiply(a, b);
			Assert::AreEqual(exp, ret);
		}

		TEST_METHOD(Divide)//³ý
		{
			string a = "78954632178846432", b = "15462897444";
			string exp = "5106069";
			string ret = BigIntCalculate::divide(a, b);
			Assert::AreEqual(exp, ret);
		}
		TEST_METHOD(Mod)//ÇóÓà
		{
			string a = "78954632178846432", b = "15462897444";
			string exp = "10889858796";
			string ret = BigIntCalculate::mod(a, b);
			Assert::AreEqual(exp, ret);
		}
	};
}
