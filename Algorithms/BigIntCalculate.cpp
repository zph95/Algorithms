#include "BigIntCalculate.h"

string BigIntCalculate::add(string num1, string num2)
{
    string str;
    int cur = 0, i = num1.size() - 1, j = num2.size() - 1;
    while (i >= 0 || j >= 0 || cur != 0) {
        if (i >= 0) {
            cur += num1[i] - '0';
            i--;
        }
        if (j >= 0) {
            cur += num2[j] - '0';
            j--;
        }
        str += to_string(cur % 10);
        cur /= 10;
    }
    reverse(str.begin(), str.end());
    return str;
}

string BigIntCalculate::subtract(string num1, string num2)
{
	if (num1.size() < num2.size())
	{
		return "-" + subtract(num2, num1);
	}
	if (num1.size() == num2.size())
	{
		int i = 0;
		while (i < num1.size() && num1[i] == num2[i]) {
			i++;
			if (num1[i] < num2[i])
			{
				return "-" + subtract(num2, num1);
			}
		}
	}
	string res(num1.size(), '0');
	int i = num1.size() - 1, j = num2.size() - 1;
	int k = i;
	int borrow = 0;
	while (i >= 0 && j >= 0)
	{
		int sum = (num1[i] - '0') - borrow - (num2[j] - '0');
		//cout<<sum<<endl;
		if (sum < 0)
		{
			borrow = 1;
			sum += 10;
			res[k] = sum + '0';
		}
		else {
			borrow = 0;
			res[k] = sum + '0';
		}
		i--;
		j--;
		k--;
	}
	while (i >= 0)
	{
		int sum = num1[i--] - '0' - borrow;
		if (sum < 0)
		{
			borrow = 1;
			sum += 10;
			res[k--] = sum + '0';
		}
		else {
			borrow = 0;
			res[k--] = sum + '0';
		}
	}
	for (int index = 0; index < res.size(); index++)
		if (res[index] != '0') return res.substr(index); //去除前导0
	return "0";
}

string BigIntCalculate::multiply(string num1, string num2)
{
    int m = num1.size(), n = num2.size();
    string s(m + n, '0');       //初始化大小m+n
    for (int i = m - 1; i >= 0; --i)     //从后向前
        for (int j = n - 1; j >= 0; --j)
        {
            int cur = (num1[i] - '0') * (num2[j] - '0') + (s[i + j + 1] - '0'); //注意累加之前的结果
            s[i + j + 1] = cur % 10 + '0';  //这里是=字符
            s[i + j] += cur / 10;     //注意这里是+=数字
        }
    for (int i = 0; i < m + n; i++)
        if (s[i] != '0') return s.substr(i); //去除前导0
    return "0";
}

string BigIntCalculate::divide(string num1, string num2)
{
	return string();
}

string BigIntCalculate::mod(string num1, string num2)
{
	return string();
}
