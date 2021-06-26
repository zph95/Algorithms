#include<iostream>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<fstream>
#include<windows.h> //使用window系统的计时api
#define N 27//数据规模3^……
#define MAX 65535
using namespace std;

void sort1(int b[]);
void sort2(int b[]);
void sort3(int b[]);
void sort4(int b[]);
void sort5(int b[]);

int main() {
	
	long  i, j;
	int temp;
	int *a, *b;
	a = new int[N];
	b = new int[N];
	/*构造随机序列
		srand((unsigned)time(NULL));
		ofstream out("input_numble.txt");
		for (i = 0; i < N; i++) {
			temp = rand()%MAX+1;
			a[i] = temp;
			out << a[i] <<endl;
			}
		*/
	ifstream in;
	in.open("input_numble.txt");
	for (i = 0; i < N; i++) {
		in>>a[i];
	}
	in.close();
	//冒泡排序，快速排序，归并排序， 基数排序，计数排序
	LARGE_INTEGER li;
	long long f_time;
	ofstream timeout("time.txt");
	//for (i = 1; i <= 5; i++) {
		i = 3;
		for (j = 0; j < N; j++) b[j] = a[j];
		switch (i) {
		case 1: {
			QueryPerformanceCounter(&li);		//计算算法效率时间
			long long f_start = li.QuadPart;
			sort1(b);
			QueryPerformanceCounter(&li);
			long long f_end = li.QuadPart;
			f_time = (f_end - f_start);
			timeout << "冒泡排序 time=" << f_time << endl;
			ofstream out("冒泡排序result.txt");
			for (j = 0; j < N; j++) out << b[j] << endl;
			out.close(); 
			break; 
		}
		case 2: {	
			QueryPerformanceCounter(&li);		//计算算法效率时间
			long long f_start = li.QuadPart;
			sort2(b);
			QueryPerformanceCounter(&li);
			long long f_end = li.QuadPart;
			f_time = (f_end - f_start);
			timeout << "快速排序 time=" << f_time << endl;
			ofstream out("快速排序result.txt");
			for (j = 0; j < N; j++) out << b[j] << endl;
			out.close();
			break;
		}
		case 3: {	
			QueryPerformanceCounter(&li);		//计算算法效率时间
			long long f_start = li.QuadPart;
			sort3(b);
			QueryPerformanceCounter(&li);
			long long f_end = li.QuadPart;
			f_time = (f_end - f_start);
			timeout << "归并排序 time=" << f_time << endl;
			ofstream out("归并排序result.txt");
			for (j = 0; j < N; j++) out << b[j] << endl;
			out.close(); 
			break; 
		}
		case 4: {	QueryPerformanceCounter(&li);		//计算算法效率时间
			long long f_start = li.QuadPart;
			sort4(b);
			QueryPerformanceCounter(&li);
			long long f_end = li.QuadPart;
			f_time = (f_end - f_start);
			timeout << "计数排序 time=" << f_time << endl;
			ofstream out("计数排序result.txt");
			for (j = 0; j < N; j++) out << b[j] << endl;
			out.close();
			break;
		}
		case 5: {	QueryPerformanceCounter(&li);		//计算算法效率时间
			long long f_start = li.QuadPart;
			sort5(b);
			QueryPerformanceCounter(&li);
			long long f_end = li.QuadPart;
			f_time = (f_end - f_start);
			timeout << "基数排序 time=" << f_time << endl;
			ofstream out("基数排序result.txt");
			for (j = 0; j < N; j++) out << b[j] << endl;
			out.close();
			break;
		}
		default: break;
		}
		
	//}
	timeout.close();
	return 0;
}

void sort1(int b[]) {		//冒泡排序
	long i, j;
	int temp;
	for (i = 1; i < N; i++) {
		for (j = 0; j < N-i; j++) {
			if (b[j] > b[j + 1]) { temp = b[j]; b[j] = b[j + 1]; b[j + 1] = temp; }
		}
	}
}

long partition(int b[], long p, long r) {
	int x = b[r];
	int temp;
	long i = p - 1;
	for (long j = p; j < r; j++) {
		if (b[j] <= x) {
			i = i + 1;
			temp = b[i];
			b[i] = b[j];
			b[j] = temp;
		}
	}
	temp = b[i+1];
	b[i+1] = b[r];
	b[r] = temp;
	return i + 1;
}

void quicksort(int b[],long p, long r) {
	if (p < r) {
		long q = partition(b, p, r);
		quicksort(b, p, q - 1);
		quicksort(b, q + 1, r);
	}
}

void sort2(int b[]) { //快速排序
	quicksort(b, 0, N-1);
}

void merge(int b[], long p, long q, long r) {
	int *temp;
	temp = new int[N];
	long i = p, j = q + 1;
	long m= q, n= r;
	long k=0;
	while (i <= m&&j <= n) {
		if (b[i] <= b[j])  temp[k++] = b[i++]; 
		else temp[k++] = b[j++];
	}
	while (i <= m)
		temp[k++] = b[i++];

	while (j <= n)
		temp[k++] = b[j++];

	for (i = 0; i < k; i++)
		b[p + i] = temp[i];
	free(temp);
}

void mergesort(int b[], long p, long r) {
	if (p < r) {
		long q = (p + r) / 2;
		mergesort(b, p, q);
		mergesort(b, q + 1, r);
		merge(b, p, q, r);
		//cout << q << endl;
	}
}

void sort3(int b[]) {  //归并排序
	mergesort(b, 0, N - 1);
}

void sort4(int b[]) {  //计数排序
	int *out,*temp;
	out= new int[N+1];
	temp = new int[MAX+1];
	long i, j;
	for (i = 0; i < MAX+1; i++) {
		temp[i] = 0;
	}
	for (j = 0; j < N; j++) {
		temp[b[j]] = temp[b[j]] + 1;
	}
	for (i = 1; i < MAX+1; i++) {
		temp[i] = temp[i] + temp[i - 1];
	}
	for (j = N - 1; j >= 0; j--) {
		out[temp[b[j]]] = b[j];
		temp[b[j]] = temp[b[j]] - 1;
	}
	for (i = 0; i < N; i++) {
		b[i] = out[i+1];
	}
}

void COUNTING_SORT(int B[ ][5], int C[ ], int k, int h)  
{//基数排序调用的计数排序  
	int  i;
	long j;
	int *D = new int[k + 1];
	for ( i = 0; i <= k; i++)//O(k)  
	{
		D[i] = 0;
	}
	for ( j = 0; j<N; j++)//O(n)  
	{
		D[B[j][h]] = D[B[j][h]] + 1;
	}
	for (i = 0; i <= k; i++)//O(k)  
	{
		D[i + 1] = D[i + 1] + D[i];
	}
	for (j = N- 1; j >= 0; j--)//O(n)  
	{
		C[D[B[j][h]] - 1] = j;//把排好序的下标存放到数组C中以便按顺序把它存储到辅助数组E中。  
		D[B[j][h]] = D[B[j][h]] - 1;
	}
}
void Converted_to_Decimal(int A[], int B[][5], long i)//O(d)+O(d)=O(d)  
{//此函数是将十进制数以2维数组B的形式存放。  
	int x = A[i];
	int j;
	for (j = 0; x>0; j++)//O(d)循环了j<d次  
	{
		B[i][j] = x % 10;
		x = x / 10;
	}
	if (j<5)
	{
		for (int k = j; k<5; k++)//O(d) 循环了d-j次  
		{
			B[i][k] = 0;
		}
	}
}
void radix_sort(int b[],int B[][5],int C[],int E[],int d) {
	int j;
	long i;
	for ( i = 0; i < N; i++) {
		Converted_to_Decimal(b, B, i);
	}
	for (j = 0; j < 5; j++) {
		COUNTING_SORT(B, C, 9, j);
		for ( i = 0; i<N; i++)//O(n)  
		{
			E[i] = b[C[i]];//每位上排好序后，将其复制到辅助数组E上。  
		}
		for (i = 0; i<N; i++)//O(n)  
		{
			Converted_to_Decimal(E, B, i);//把辅助数组E上的数转换成二维数组存放到二维数组B中。  
	
		}
		for (i = 0; i<N; i++)//O(n)  
		{
			b[i] = E[i];//每次将按位排好序的数存放到数组A中以便在下一次循环中对下一位进行排序。  
		}
	}

}

void sort5(int b[]) {//基数排序
	int  (*B)[5]=new int[N][5];
	int *C, *E;
	C = new int[N];
	E = new int[N];
	//int  B[N][5] = { 0 }, C[N] = { 0 }, E[N] = { 0 };
	radix_sort(b, B, C, E, 5);
}