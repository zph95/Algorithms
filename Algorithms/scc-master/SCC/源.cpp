#include <iostream>
#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<fstream>

using namespace std;

#define N 27	//数据规模  9 27 81 234 729
#define LOGN 3	//边规模，log3 N  2 3  4 5   6
#define WHITE 0  
#define GRAY 1  
#define BLACK 2  

//边结构  
struct Edge
{
	int start; 
	int end;  
	Edge *next;//同一个起点开始的下一条边  
	int type;//边的类型  
	Edge(int s, int e) :start(s), end(e), next(NULL) {}
};
//顶点结构  
struct Vertex
{
	int id;
	Edge *head;//以该顶点为起点的下一条边  
	int color;
	Vertex *p;//指向遍历结果的父结点  
	int d, f;//第一次被发现的时间和结束检查的时间  
	Vertex() :head(NULL), color(WHITE), p(NULL), d(0x7fffffff), id(0) {}
};
//图结构  
struct Graph
{
	Vertex V[N + 1];//N个顶点 从1开始到N 
	Graph()
	{
		int i;
		for (i = 1; i <= N; i++)
			V[i].id = i;  //顶点标号
	}
};

int T = 0;
bool flag = 0;//flag为0表示第一次调用DFS，为1表示第二次调用DFS  
int Sort[N + 1] = { N };//存储按u.f从大到小排序时的点，按点的顺序调用DFS_Visit函数  

						//插入边，按边的end由小到大排列  
void InsertEdge(Graph *G, int start, int end)
{
	Edge *E = new Edge(start, end);
	//如果当前点E->start的链表为空，则把E边作为head  
	if (G->V[E->start].head == NULL)
		G->V[E->start].head = E;
	//如果有，加入到链表中，递增顺序排列，便于查重  
	else
	{
		//链表的插入  
		Edge *e1 = G->V[E->start].head, *e2 = e1;
		while (e1 && e1->end < E->end)
		{
			e2 = e1;
			e1 = e1->next;
		}
		//插入了重复的边，直接返回  
		if (e1 && e1->end == E->end)
			return;
		//第一条边的end都比E边的end大， 此时e1 == e2，则把E作为head  
		if (e1 == e2)
		{
			E->next = e1;
			G->V[E->start].head = E;
		}
		//找到E的正确位置  
		else
		{
			e2->next = E;
			E->next = e1;
		}
	}
}
//转置，重新构造一个图  
Graph* Reverse(Graph *G)
{
	Graph *ret = new Graph;
	int i;
	//遍历图G中的每一条边，以终点为起点，以起点为终点，加入到新图RET中     
	for (i = 1; i <= N; i++)
	{
		Edge *E = G->V[i].head;
		while (E)
		{
			InsertEdge(ret, E->end, E->start);
			E = E->next;
		}
	}
	return ret;
}
//访问某顶点 

ofstream dataout;
void DFS_Visit(Graph *G, Vertex *u)
{
	 
	if (flag)
		dataout << u->id << ' ';   //在第二次DFS调用时输出 
 
	u->color = GRAY;
	
	T++;
	
	u->d = T;	//将T的新值记录为发现时间  
	//检查和u相邻的每个顶点v  
	Vertex *v;
	Edge *e = u->head;
	while (e)
	{
		v = &G->V[e->end];
		//如果顶点为白色  
		if (v->color == WHITE)
		{
			//递归访问顶点  
			v->p = u;
			DFS_Visit(G, v);
			//树边  
			e->type = 1;
		}
		else if (v->color == GRAY)
		{
			//反向边  
			e->type = 2;
		}
		else if (v->color == BLACK)
		{
			//正向边  
			if (u->d < v->d)
				e->type = 3;
			//交叉边  
			else
				e->type = 4;
		}
		e = e->next;
	}
	
	u->color = BLACK;//以u为起点的所有边都被探寻后，置u为黑色  
	 
	T++;
	u->f = T;	//并将完成时间记录在f[u]中 

	if (flag == 0)
	{
		Sort[Sort[0]] = u->id;	//把结果按照f从大到小的顺序保存于Sort数组中  
		Sort[0]--;
	}
}


//深度优先搜索  
void DFS(Graph *G)
{
	int i;
	
	for (i = 1; i <= N; i++)
	{
		G->V[i].id = i;
		G->V[i].color = WHITE;
		G->V[i].p = NULL;
	}
 
	T = 0;
	//依次检索V中的顶点，发现白色顶点时，调用DFS_Visit访问该顶点  
	for (i = 1; i <= N; i++)
	{
		int j;
		//第一次是以正常顺序按点1->2->3->.....->8的顺序调用DFS_Visit函数  
		if (flag == 0)
			j = i;
		//第二次是以f从大到小的顺序，这个顺序在第一次dfs次保存于Sort数组中  
		else
			j = Sort[i];
		//发现白色顶点时，调用DFS_Visit访问该顶点  
		if (G->V[j].color == WHITE)
		{
			if (flag)
				dataout << "强连通分量为：( ";
			DFS_Visit(G, &G->V[j]);
			//flag == 1时，第二次调用DFS，此时每次调用DFS_Visit 就会输出一个强连通分量
			if (flag)
				dataout <<")"<< endl;
		}
	}
}
void Strongly_Connected_Component(Graph *G)
{
	//第一次DFS，计算每个顶点的f  
	DFS(G);
	//转置，计算GT     
	Graph *G2 = Reverse(G);
	//第一次的DFS和第二次的DFS不同，用flag区分  
	flag = 1;
	//第二次的DFS，按照f从大到小的顺序调用  
	DFS(G2);
}

string filename1, filename2, filename3;
int main()
{
	//构造一个空的图     
	Graph *G = new Graph;
	int edge[N*LOGN][2];//边数组	
	srand((unsigned)time(NULL));
	
	filename1 = "..\\input\\size2\\input.txt";
	filename2 = "..\\output\\size2\\time1.txt";
	filename3="..\\output\\size2\\output1.txt";
	//system("md ..\\input\\size1");
	//system("md ..\\output\\size1");

		ofstream edgeout(filename1);

		for (int j = 0; j < N*LOGN; j++) {
			edge[j][0] = rand() % N;
			edge[j][1] = rand() % N;
			edgeout << edge[j][0] << "," << edge[j][1] << endl;
		}
		//cout << "edge ok" << endl;
		edgeout.close();
	
	for (int i = 1; i < N*LOGN; i++)
	{
		int start = edge[i][0];
		int end = edge[i][1];
		InsertEdge(G, start, end);
	}
	LARGE_INTEGER li;
	long long f_time = 0;
	long long f_start, f_end;
	//计算强联通分量和时间

	ofstream timeout(filename2);
	dataout.open(filename3);
	QueryPerformanceCounter(&li);		//计算时间
		f_start = li.QuadPart;
		Strongly_Connected_Component(G);
		QueryPerformanceCounter(&li);		//计算时间
		f_end = li.QuadPart;
		f_time = (f_end - f_start);
		timeout <<  "time=" << f_time << endl;
		timeout.close();

	return 0;
}
