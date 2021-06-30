#include <iostream> 
#include<time.h>
#include<stdio.h>
#include<windows.h>
#include<fstream>
#define N 729
using namespace std;

const int INFINIT = 655350;

struct Graph
{
	int ** Matrix;
	int vertexNum;
	int edgeNum;
};
int ** d = new int *[N];
int ** path = new int *[N];
ofstream dataout;
int length = 0;
string filename1, filename2, filename3;
void CreateGraph(Graph & g)
{
	g.Matrix = NULL;
	int i, j, edgeStart, edgeEnd, weight;
	g.vertexNum = N;
	g.edgeNum=N*log(N)/log(3);
	cout << g.edgeNum<<endl;

	int n = g.vertexNum;

	g.Matrix = new int *[n];
	for (i = 0; i < n; ++i)
	{
		g.Matrix[i] = new int[n];
	}

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (j == i)
				g.Matrix[i][j] = 0;
			else
				g.Matrix[i][j] = INFINIT;
		}
	}
	srand((unsigned)time(NULL));

	filename1 = "..\\input\\size5\\input.txt";
	filename2 = "..\\output\\size5\\time2.txt";
	filename3 = "..\\output\\size5\\output2.txt";
	//system("md ..\\input\\size5"); //创建文件夹
	//system("md ..\\output\\size5");

	ofstream edgeout(filename1);

	for (int j = 0; j < g.edgeNum; j++) {
		edgeStart = rand() % N;
		edgeEnd  = rand() % N;
		if (edgeEnd == edgeStart) { j--; continue; }
		weight = rand() % 90-5;
		edgeout << edgeStart << " " << edgeEnd << " "<<weight<<endl;
		g.Matrix[edgeStart][edgeEnd] = weight;
	}
	//cout << "edge ok" << endl;
	edgeout.close();
}

void PrintAdjMatrix(const Graph & g)
{
	int i, j, n, weight;
	n = g.vertexNum;
	cout << "Adjacent matrix for this graph is: "<<endl;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			weight = g.Matrix[i][j];
			if (weight == INFINIT)
				cout << "INF"<<" \t ";
			else
			{
				cout << weight << " \t ";
			}
		}
		cout << endl;
	}
	
}
void DeleteGraph(Graph & g)
{
	if (g.Matrix != NULL)
		delete[] g.Matrix;
	g.Matrix = NULL;
}

void CheckShortestMatrix(int n)
{
	int i, j, k;
	
	for (k = 0; k < n; k++)
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{	
				if (d[i][k] == INFINIT || d[k][j] == INFINIT) {
					//若d[i][k]或d[k][j]等于无穷，则不能用d[i][k] + d[k][j] 做比较运算 ，否则可能会出现 负数+inf<inf， inf设定的是一个很大的数
				}
				else   if (d[i][k] + d[k][j] < d[i][j])
				{
					cout << "error:graph中存在负环路" << endl;
					exit(1);
				}
			}
		}
	}
	/*
	cout << "The shortest path matrix is: \n ";
	
	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			if (d[i][j] == INFINIT)
				cout << "INF \t ";
			else {
				cout << d[i][j] << " \t ";
			}

		}
		cout << " \n ";
	}
	*/
}

void PrintShortestPath(Graph & g,int ** path, int i, int j)
{
	
	if (i == j)
	{
		dataout << i << " ";
	}
	else if (path[i][j] == INFINIT) { 
						dataout << "INF";
								return;}
	else { 
	int k = path[i][j];
	length+=g.Matrix[k][j];
	PrintShortestPath(g,path, i,k );
	dataout << j<<" ";
	}
	
}
void FloydWarshall(Graph & g)
{
	int i, j, k, n;
	n = g.vertexNum;

	for (i = 0; i < n; ++i)
	{
		d[i] = new int[n];
		path[i] = new int[n];
	}
	for (i = 0; i < n; ++i)
	{
		for (j = 0; j < n; ++j)
		{
			d[i][j] = g.Matrix[i][j];
			if (i != j&&d[i][j] < INFINIT) path[i][j] = i;
			else  path[i][j] = INFINIT;
		}
	}

	for (k = 0; k < n; k++)
	{
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < n; j++)
			{   
				if (d[i][k] == INFINIT || d[k][j] == INFINIT) {
					//若d[i][k]或d[k][j]等于无穷，则不能用d[i][k] + d[k][j] 做比较运算 ，否则可能会出现 负数+inf<inf， inf设定的是一个很大的数
				}
				else if (d[i][k] + d[k][j] < d[i][j])
				{
					d[i][j] = d[i][k] + d[k][j];
					path[i][j] = path[k][j];
				}
			}
		}
	}
	
}

int main( )
{
	Graph g;
	CreateGraph(g);
	//PrintAdjMatrix(g);

	LARGE_INTEGER li;
	long long f_time = 0;
	long long f_start, f_end;
	//计算时间
	ofstream timeout(filename2);
	dataout.open(filename3);
	QueryPerformanceCounter(&li);		//计算时间
	f_start = li.QuadPart;
	FloydWarshall(g);
	QueryPerformanceCounter(&li);		//计算时间
	f_end = li.QuadPart;
	f_time = (f_end - f_start);
	timeout << "time=" << f_time << endl;
	timeout.close();
	CheckShortestMatrix(N);
	delete[] d;
	for (int i = 0; i <N; i++) {
		for (int j = 0; j < N; j++) {
			if (i != j)
			{
				dataout << " v" << i << " to v" << j << " is:  ";
				PrintShortestPath(g,path, i, j);
				dataout << "  length=" << length<<endl;
				length = 0;
			}
		}
	}
	delete[] path;
	DeleteGraph(g);
	return 0;
}