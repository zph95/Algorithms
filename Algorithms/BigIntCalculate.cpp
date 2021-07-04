#include "BigIntCalculate.h"
#include<iostream>
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
		for (int i = 0; i < num1.size(); i++) {
			int a = num1[i] + '0';
			int b = num2[i] + '0';
			if (a < b) {
				return "-" + subtract(num2, num1);
			}
			else if (a > b) {
				break;
			}
		}
	}
	string str;
	int i = num1.size() - 1, j = num2.size() - 1;
	int cur = 0;
	while (i >= 0 )
	{
		if (j >= 0) {
			cur += (num1[i] - '0') - (num2[j] - '0');
		}
		else {
			cur += num1[i] - '0';
		}
		i--;
		j--;

		if (cur < 0)
		{
			str += to_string(cur+10);
			cur = -1;
		}
		else {
			str += to_string(cur);
			cur = 0;
		}
	}
	reverse(str.begin(), str.end());
	for (int i = 0; i < str.size(); i++)
		if (str[i] != '0') return str.substr(i); //去除前导0
	return "0";
}
//大整数乘法的快速算法还可以用（快速傅立叶变换FFT）
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
	int m = num1.size(), n = num2.size();

	if (m < n) {
		return "0";
	}
	if (num2 == "0") {
		return "error";
	}

	int t = m - n;//位数之差
	string div_result(t+1, '0');
	string tmp_num2(n + t, '0');
	for (int i = 0; i < n; i++) {//将除数扩大10^t倍
		tmp_num2[i] = num2[i];
	}
	string mod_result = num1;
	for (int i = 0; i < t + 1; i++) {
		int count = 0;
		string sub_result = mod_result;
		while(true){
			string tmp = tmp_num2.substr(0, n + t - i);
			//cout << "i = " << i << " tmp = " << tmp << " sub_result = " << sub_result << endl;
			sub_result = subtract(sub_result, tmp);
			if ( sub_result[0] != '-') {
				count++;
				mod_result = sub_result;
			}
			else  {
				break;
			}
		}
		div_result[i] = '0' + count;
	}
	if (div_result[0] == '0') {
		return div_result.substr(1); //去除前导0
	}
	else {
		return div_result;
	}
}

string BigIntCalculate::mod(string num1, string num2)
{

	int m = num1.size(), n = num2.size();

	if (m < n) {
		return num1;
	}
	int t = m - n;//位数之差
	string div_result(t + 1, '0');
	string tmp_num2(n + t, '0');
	for (int i = 0; i < n; i++) {//将除数扩大10^t倍
		tmp_num2[i] = num2[i];
	}
	string mod_result = num1;
	for (int i = 0; i < t + 1; i++) {
		int count = 0;
		string sub_result = mod_result;
		while (true) {
			string tmp = tmp_num2.substr(0, n + t - i);
			//cout << "i = " << i << " tmp = " << tmp << " sub_result = " << sub_result << endl;
			sub_result = subtract(sub_result, tmp);
			if (sub_result[0] != '-') {
				count++;
				mod_result = sub_result;
			}
			else {
				break;
			}
		}
		div_result[i] = '0' + count;
	}
	return mod_result;
}
