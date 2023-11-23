#include <iostream>
#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<fstream>

using namespace std;

#define N 27	//���ݹ�ģ  9 27 81 234 729
#define LOGN 3	//�߹�ģ��log3 N  2 3  4 5   6
#define WHITE 0  
#define GRAY 1  
#define BLACK 2  

//�߽ṹ  
struct Edge
{
	int start; 
	int end;  
	Edge *next;//ͬһ����㿪ʼ����һ����  
	int type;//�ߵ�����  
	Edge(int s, int e) :start(s), end(e), next(NULL) {}
};
//����ṹ  
struct Vertex
{
	int id;
	Edge *head;//�Ըö���Ϊ������һ����  
	int color;
	Vertex *p;//ָ���������ĸ����  
	int d, f;//��һ�α����ֵ�ʱ��ͽ�������ʱ��  
	Vertex() :head(NULL), color(WHITE), p(NULL), d(0x7fffffff), id(0) {}
};
//ͼ�ṹ  
struct Graph
{
	Vertex V[N + 1];//N������ ��1��ʼ��N 
	Graph()
	{
		int i;
		for (i = 1; i <= N; i++)
			V[i].id = i;  //������
	}
};

int T = 0;
bool flag = 0;//flagΪ0��ʾ��һ�ε���DFS��Ϊ1��ʾ�ڶ��ε���DFS  
int Sort[N + 1] = { N };//�洢��u.f�Ӵ�С����ʱ�ĵ㣬�����˳�����DFS_Visit����  

						//����ߣ����ߵ�end��С��������  
void InsertEdge(Graph *G, int start, int end)
{
	Edge *E = new Edge(start, end);
	//�����ǰ��E->start������Ϊ�գ����E����Ϊhead  
	if (G->V[E->start].head == NULL)
		G->V[E->start].head = E;
	//����У����뵽�����У�����˳�����У����ڲ���  
	else
	{
		//����Ĳ���  
		Edge *e1 = G->V[E->start].head, *e2 = e1;
		while (e1 && e1->end < E->end)
		{
			e2 = e1;
			e1 = e1->next;
		}
		//�������ظ��ıߣ�ֱ�ӷ���  
		if (e1 && e1->end == E->end)
			return;
		//��һ���ߵ�end����E�ߵ�end�� ��ʱe1 == e2�����E��Ϊhead  
		if (e1 == e2)
		{
			E->next = e1;
			G->V[E->start].head = E;
		}
		//�ҵ�E����ȷλ��  
		else
		{
			e2->next = E;
			E->next = e1;
		}
	}
}
//ת�ã����¹���һ��ͼ  
Graph* Reverse(Graph *G)
{
	Graph *ret = new Graph;
	int i;
	//����ͼG�е�ÿһ���ߣ����յ�Ϊ��㣬�����Ϊ�յ㣬���뵽��ͼRET��     
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
//����ĳ���� 

ofstream dataout;
void DFS_Visit(Graph *G, Vertex *u)
{
	 
	if (flag)
		dataout << u->id << ' ';   //�ڵڶ���DFS����ʱ��� 
 
	u->color = GRAY;
	
	T++;
	
	u->d = T;	//��T����ֵ��¼Ϊ����ʱ��  
	//����u���ڵ�ÿ������v  
	Vertex *v;
	Edge *e = u->head;
	while (e)
	{
		v = &G->V[e->end];
		//�������Ϊ��ɫ  
		if (v->color == WHITE)
		{
			//�ݹ���ʶ���  
			v->p = u;
			DFS_Visit(G, v);
			//����  
			e->type = 1;
		}
		else if (v->color == GRAY)
		{
			//�����  
			e->type = 2;
		}
		else if (v->color == BLACK)
		{
			//�����  
			if (u->d < v->d)
				e->type = 3;
			//�����  
			else
				e->type = 4;
		}
		e = e->next;
	}
	
	u->color = BLACK;//��uΪ�������б߶���̽Ѱ����uΪ��ɫ  
	 
	T++;
	u->f = T;	//�������ʱ���¼��f[u]�� 

	if (flag == 0)
	{
		Sort[Sort[0]] = u->id;	//�ѽ������f�Ӵ�С��˳�򱣴���Sort������  
		Sort[0]--;
	}
}


//�����������  
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
	//���μ���V�еĶ��㣬���ְ�ɫ����ʱ������DFS_Visit���ʸö���  
	for (i = 1; i <= N; i++)
	{
		int j;
		//��һ����������˳�򰴵�1->2->3->.....->8��˳�����DFS_Visit����  
		if (flag == 0)
			j = i;
		//�ڶ�������f�Ӵ�С��˳�����˳���ڵ�һ��dfs�α�����Sort������  
		else
			j = Sort[i];
		//���ְ�ɫ����ʱ������DFS_Visit���ʸö���  
		if (G->V[j].color == WHITE)
		{
			if (flag)
				dataout << "ǿ��ͨ����Ϊ��( ";
			DFS_Visit(G, &G->V[j]);
			//flag == 1ʱ���ڶ��ε���DFS����ʱÿ�ε���DFS_Visit �ͻ����һ��ǿ��ͨ����
			if (flag)
				dataout <<")"<< endl;
		}
	}
}
void Strongly_Connected_Component(Graph *G)
{
	//��һ��DFS������ÿ�������f  
	DFS(G);
	//ת�ã�����GT     
	Graph *G2 = Reverse(G);
	//��һ�ε�DFS�͵ڶ��ε�DFS��ͬ����flag����  
	flag = 1;
	//�ڶ��ε�DFS������f�Ӵ�С��˳�����  
	DFS(G2);
}

string filename1, filename2, filename3;
int main()
{
	//����һ���յ�ͼ     
	Graph *G = new Graph;
	int edge[N*LOGN][2];//������	
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
	//����ǿ��ͨ������ʱ��

	ofstream timeout(filename2);
	dataout.open(filename3);
	QueryPerformanceCounter(&li);		//����ʱ��
		f_start = li.QuadPart;
		Strongly_Connected_Component(G);
		QueryPerformanceCounter(&li);		//����ʱ��
		f_end = li.QuadPart;
		f_time = (f_end - f_start);
		timeout <<  "time=" << f_time << endl;
		timeout.close();

	return 0;
}
