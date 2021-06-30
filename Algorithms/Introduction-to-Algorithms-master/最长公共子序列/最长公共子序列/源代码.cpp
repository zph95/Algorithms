#include<iostream>

#include<time.h>
#include<windows.h>
#include<fstream>

#include <string>  
#define MAX 110
using namespace std;

int M, N;
char *b[MAX][MAX] = {NULL };
int c[MAX][MAX] = { 0 };
void Lcs_Length(char *x, char *y)
{   
	/*
	for (int i = 1; i<= M; i++)  //已在函数外初始化为0
	{
		c[i][0] = 0;
	}
	for (int j= 0; j<= N; j++)
	{
		c[0][j] = 0;
	}
	*/
	for (int i = 1; i <= M; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (x[i] == y[j])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = "↖";
			}
			else
			{
				if (c[i - 1][j] >= c[i][j - 1])
				{
					c[i][j] = c[i - 1][j];
					b[i][j] = "↑";
				}
				else
				{
					c[i][j] = c[i][j - 1];
					b[i][j] = "←";
				}
			}
		}
	}
}

ofstream out;
int length;
void PRINT_LCS(char*x, int i, int j)
{
	if (i == 0 || j == 0)
	{
		return;
	}
	if (b[i][j] == "↖")
	{
		PRINT_LCS(x, i - 1, j - 1);
		out << x[i]; length++;
	}
	else
	{
		if (b[i][j] == "↑")
		{
			PRINT_LCS(x, i - 1, j);
		}
		else
		{
			PRINT_LCS(x, i, j - 1);
		}
	}
}
void main()
{
	int temp;

	char x[MAX] = { '\0' };
	char y[MAX] = { '\0' };
	int length1[] = { 20,10,20,20,20,30,20,40,20,50,20,60,20,70 };
	int length2[] = { 15,25,30,25,45,25,60,25,75,25,90,25,105,25 };
	/*	生成随机字符串序列A,B
	ofstream strout("..\\input\\inputB.txt");
	srand((unsigned)time(NULL));
	for (int j = 0; j < 14; j++) {
		for (int i = 0; i < length[j]; i++) {
			temp = rand() % 26;
			strout << (char)('A' + temp);
		}
		strout << endl;
	}
	cout << "stringA ok" << endl;
	strout.close();
	*/
	LARGE_INTEGER li;
	long long f_time = 0;
	long long f_start, f_end;

	ofstream timeout;
	string filename1, filename2;
	filename1 = "..\\output\\ex"; //打开其它文件夹内的文件./为当前层，../为上层

	ifstream in("..\\input\\inputA.txt");
	filename2 = filename1 + "1\\time2.txt";
	timeout.open(filename2);

	string filename3;
	filename3 = filename1 + "1\\output2.txt";

	out.open(filename3);
/*	M = length1[0]; N = length1[0 + 1];
	for (int i = 1; i <= M; i++)  in >> x[i];
	for (int i = 1; i <= N; i++)  in >> y[i];
	length = 0;
	Lcs_Length(x, y);		 //先调用一次Lcs_Length（x,y)后可得到正常的序列1的第一个数据
	out.close();       
	out.open(filename3); */
	for (int j = 0; j < 14; j += 2) {

		M = length1[j]; N= length1[j + 1];
		for (int i = 1; i <= M; i++)  in >> x[i];
		for (int i = 1; i <= N; i++)  in >> y[i];
		length = 0;
		QueryPerformanceCounter(&li);		//计算时间
		f_start = li.QuadPart;
		Lcs_Length(x, y);
		QueryPerformanceCounter(&li);		//计算时间
		f_end = li.QuadPart;
		f_time = (f_end - f_start);
		timeout << "序列" << j / 2 + 1 << ":" << "time=" << f_time << endl;
		PRINT_LCS(x, M, N);
		out<<endl <<"LCS lenth="<< length << endl;
		/*	cout << "书中图15-8中的表格：" << endl;
			for (int i = 0; i <= N; i++)
			{
				for (int j = 0; j <= M; j++)
				{
					cout << b[i][j] << "\t";
				}
				cout << endl;
				for (int j = 0; j <= M; j++)
				{
					cout << c[i][j] << "\t";
				}
				cout << endl;
			}
			*/
	}
	out.close();
	in.close();
	timeout.close();
	in.open("..\\input\\inputB.txt");
	filename2 = filename1 + "2\\time2.txt";
	filename3 = filename1 + "2\\output2.txt";
	timeout.open(filename2);
	out.open(filename3);

	for (int j = 0; j < 14; j += 2) {
		M = length2[j]; N= length2[j + 1];
		for (int i = 1; i <= M; i++)  in >> x[i];
		for (int i = 1; i <= N; i++)  in >> y[i];
		length = 0;
		QueryPerformanceCounter(&li);		//计算时间
		f_start = li.QuadPart;
		Lcs_Length(x, y);
		QueryPerformanceCounter(&li);		//计算时间
		f_end = li.QuadPart;
		f_time = (f_end - f_start);
		timeout << "序列" << j / 2 + 1 << ":" << "time=" << f_time << endl;
		PRINT_LCS(x, M, N);
		out << endl << "LCS lenth=" << length << endl;
	}
	in.close();
	timeout.close();
	out.close();
}