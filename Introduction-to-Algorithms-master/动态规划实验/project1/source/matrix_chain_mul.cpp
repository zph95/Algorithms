#include <iostream>  
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<fstream>
#include<string>
#include<windows.h> //使用window系统的计时api
using namespace std;

//#define MAX 50

struct Matrix_CHAIN//矩阵链  
{
	int n = 30;
	int **m;//运算次数  
	int **s;//划分方式   
	Matrix_CHAIN()
	{  
		
		m = new int *[n+1];
		for (int k = 0; k<=n ; k++)
		{
			m[k] = new int[n+1 ];
		}
		s = new int *[n];
		for (int t = 0; t<=n-1 ; t++)
		{
			s[t] = new int[n +1];
		}
	}
};


struct Matrix_CHAIN MATRIX_CHAIN_ORDER(int p[],int n)
{

	Matrix_CHAIN T;
	for (int i = 1; i<=n; i++)
	{
		T.m[i][i] = 0;
	}
	for (int l = 1; l <= n-1; l++)
	{
		for (int i = 1; i <= n - l ; i++)
		{
			int j = i + l ;
			T.m[i ][j ] = 0x7fffffff;
			for (int k = i; k <= j - 1; k++)
			{
				int q = T.m[i ][k ] + T.m[k+1][j ] + p[i - 1] * p[k] * p[j];
				if (q<T.m[i ][j ])
				{
					T.m[i ][j ] = q;
					T.s[i ][j ] = k ;
				}
			}
		}
	}
	return T;
}

ofstream out;

void PRINT_OPTIMAL_PARENS(Matrix_CHAIN T, int i, int j)
{   

	if (i == j)
	{
		out << "A" << i;
	}
	else
	{
		out << "(";
		PRINT_OPTIMAL_PARENS(T, i, T.s[i][j]);
		PRINT_OPTIMAL_PARENS(T, T.s[i][j] + 1, j);
		out << ")";
	}
}

int main()
{
	int n;  //数据规模
	int p[30];
	int temp;
	
	/*生成n个随机数
	srand((unsigned)time(NULL));
	ofstream out("..\\input\\input_numble.txt");
	for (int i = 0; i <n; i++) {
	temp= rand() % 50 +1;				
	p[i] = temp;
	}
	for (int i = 0; i < n; i++) {
	out << p[i] << endl;
	}
	out.close();*/
	
	
	string filename1, filename2;
	filename1 = "..\\input\\input1.txt"; //打开其它文件夹内的文件./为当前层，../为上层
	LARGE_INTEGER li;
	long long f_time = 0;
	ifstream in;
	ofstream timeout;
	filename2 = "..\\output\\time.txt";
	timeout.open(filename2);

	string filename3;
	filename3 = "..\\output\\output.txt";

	out.open(filename3);
	
	struct Matrix_CHAIN T;
	for (n = 4; n <=28; n = n + 4) {

		in.open(filename1);
		if (!in)//检查文件是否打开
		{
			cerr << "error: unable to open input file:" << filename1 << endl;
			system("pause");
			return -1;
		}
		for (int i = 0; i < n + 1; i++) {
			in >> p[i];
		}
		in.close();
		long long f_start, f_end;
		QueryPerformanceCounter(&li);		//计算时间
		f_start = li.QuadPart;
		T = MATRIX_CHAIN_ORDER(p, n);
		QueryPerformanceCounter(&li);
		f_end = li.QuadPart;
		f_time = (f_end - f_start);
		timeout << "数据规模" << n << ":" << "time=" << f_time << endl;
		/*
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (T.m[i][j] < 0)
				{
					cout << " " << "\t";
				}
				else cout << T.m[i][j] << "\t";
			}
			cout << endl;
		}  //显示m矩阵
		for (int i = 1; i <= n - 1; i++)
		{
			for (int j = 2; j <= n; j++)
			{
				if (T.s[i][j] < 0)
				{
					cout << " " << "\t";
				}
				else cout << T.s[i][j] << "\t";
			}
			cout << endl;
		}//显示s矩阵
		*/
		for (int i = 0; i < n + 1; i++) {
			out<< p[i]<<" ";
		}
		out << endl;
		PRINT_OPTIMAL_PARENS(T, 1, n);
		out << endl;
	}
	timeout.close();
	out.close();
	//cin >> temp;
	return 0;
}