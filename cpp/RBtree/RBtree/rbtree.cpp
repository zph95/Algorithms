#include<iostream>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<fstream>
#include<string>
#include<windows.h> //ʹ��windowϵͳ�ļ�ʱapi
#define N 80//���ݹ�ģ
#define MAX 150
#define BLACK 1  
#define RED 0
#define Nil -1  
#define LEN sizeof(struct Tree) 
using namespace std;

struct Tree{
	int key;
	int color;
	int size;
	struct  Tree *parent;
	struct  Tree *left;
	struct  Tree *right;
};
struct Tree*ROOT[4];
struct Tree*root;
struct Tree*nil = NULL;

ofstream dataout;

void LEFT_ROTATE( struct Tree*x);
void RIGHT_ROTATE(struct Tree*x);

struct Tree *os_select(struct Tree *T, int num)
{
	int r = T->left->size + 1;
	if (r == num)
	{
		return T;
	}
	else if (r>num)
	{
		return os_select(T->left, num);
	}
	else
	{
		return os_select(T->right, num - r);
	}
}
void SizeAdjust(struct Tree*T) //�ݹ����sizeֵ
{
	if (T != nil)
	{
		SizeAdjust(T->left);
		SizeAdjust(T->right);
		T->size = T->left->size + T->right->size + 1;
	}
}

void RB_INSERT_INSERT_FIXUP( struct Tree*z)
{
	while (z->parent->color == RED)
	{
		if (z->parent == z->parent->parent->left)
		{
			struct Tree*y = z->parent->parent->right;//����  
			if (y->color == RED) 
			{//�����z�ĸ�����z���Ǻ�ɫ�������  
				z->parent->color = BLACK;		//case 1:����Ϊ��ɫ
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;//��z���游��㵱���½��z������һ��ѭ��  
			}
			else
			{
				if (z == z->parent->right)//case2��z��һ���Һ���������Ϊ��ɫ 
				{//ʹ��һ�����������2ת��Ϊ���3  
					z = z->parent; //case2
					LEFT_ROTATE( z); 
				}
				z->parent->color = BLACK;//case3����z��һ������������Ϊ��ɫ���ı�z�ĸ����游�����ɫ����һ���������Ա�������5  
				z->parent->parent->color = RED;
				RIGHT_ROTATE( z->parent->parent); 
			}
		}
		else//����else��֧����������
		{
			struct Tree*y = z->parent->parent->left;
			if (y->color == RED)
			{
				z->parent->color = BLACK;
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}
			else
			{
				if (z == z->parent->left)
				{
					z = z->parent;
					RIGHT_ROTATE( z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				LEFT_ROTATE( z->parent->parent);
			}
		}
	}
	root->color = BLACK;//�����������Ϊ��ɫ��  
}

void RB_INSERT( struct Tree*z)
{
	struct Tree*y = nil;
	struct Tree*x = root;
	while (x != nil)
	{
		y = x;
		if (z->key<x->key)
		{
			x = x->left;
		}
		else x = x->right;
	}
	z->parent = y;
	if (y == nil)
	{
		root = z;
	}
	else if (z->key<y->key)
	{
		y->left = z;
	}
	else y->right = z;
	z->left = nil;//�����������Һ��ӽ���ÿա�  
	z->right = nil;
	z->color = RED;//����������Ϊ��ɫ��  
	RB_INSERT_INSERT_FIXUP(z);  //�������
	SizeAdjust(root);//���¼���sizeֵ
}

void RIGHT_ROTATE( struct Tree*x)
{//����ת  
	struct Tree*y = x->left;//����y��㡣  
	x->left = y->right;//�����Լ�if�ṹ��ʾ��y���Һ��ӳ�Ϊx�����ӡ�
	if (y !=nil &&y->right != nil)
	{
		y->right->parent = x;
	}
	y->parent = x->parent;//�����Լ�if-else�ṹ��ʾ��y��Ϊ�������µĸ���
	if (x->parent == nil)
	{
		root = y;
	}
	else if (x == x->parent->right)//��if�ṹ��ʾ��y��Ϊx���׵ĺ��ӡ�
	{
		x->parent->right = y;
	}
	else x->parent->left = y;
	y->right = x;//x��Ϊy���Һ���
	x->parent = y;
}

void LEFT_ROTATE( struct Tree*x)
{ //����ת
	struct Tree*y = x->right;//����y��㡣  
	x->right = y->left;//�����Լ�if�ṹ��ʾ��y�����ӳ�Ϊx���Һ��ӡ���
	if (y != nil&&y->left != nil)
	{
		y->left->parent = x;
	}
	y->parent = x->parent;//�����Լ�if-else�ṹ��ʾ��y��Ϊ�������µĸ����� 
	if (x->parent == nil)
	{
		root = y;
	}
	else if (x == x->parent->left)//��if�ṹ��ʾ��y��Ϊx���׵ĺ��ӡ�
	{
		x->parent->left = y;
	}
	else x->parent->right = y;
	y->left = x;//x��Ϊy������
	x->parent = y;
}

void RB_TRANSPLANT(struct Tree*u, struct Tree*v) //��v�����滻u����
{
	if (u->parent == nil)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else u->parent->right = v;
	v->parent = u->parent;
}
  
struct Tree*TREE_MINIMUM(struct Tree*x)
{//�ǵݹ�汾�Ĳ��Ҷ������������Сֵ
	while (x->left != nil)
	{
		x = x->left;
	}
	return x;
}

void RB_DELETE_FIXUP(struct Tree*x)
{
	struct Tree*w = nil;//w��x���ֵܽ��  
	while (x != root&&x->color == BLACK)//���x�Ǻ�ɫ���Ҳ��Ǹ���㣬�Ž���ѭ����  
	{//x��һ������˫����ɫ�Ľ�㣬������Ŀ���ǰ�x�ĺ�ɫ���������ƶ���  
		if (x == x->parent->left)
		{
			w = x->parent->right;
			if (w->color == RED)//���һ��x���ֵܽ��w�Ǻ�ɫ�ġ�  
			{//�ı�w��x.p����ɫ+һ����תʹ���Ϊ������������ġ�  
				w->color = BLACK;
				x->parent->color = RED;
				LEFT_ROTATE(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK&&w->right->color == BLACK)//�������x���ֵܽ��w�Ǻ�ɫ�ģ�����w�������ӽڵ㶼�Ǻ�ɫ��  
			{
				w->color = RED;//��x��w��ȥ��һ�غ�ɫ��x���Ǻ�ɫ����w��Ϊ��ɫ��  
				x = x->parent;//x��������ƶ���Ϊ�µĴ�������㡣  
			}
			else
			{
				if (w->right->color == BLACK)//�������x���ֵܽ��w�Ǻ�ɫ�ģ�w�������Ǻ�ɫ�ģ�w���Һ����Ǻ�ɫ�ġ�  
				{//����w��w.left����ɫ+��תʹ��ת��Ϊ����ġ�  
					w->left->color = BLACK;
					w->color = RED;
					RIGHT_ROTATE(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;//����������ģ�x���ֵܽ��w�Ǻ�ɫ�ģ���w���Һ����Ǻ�ɫ�ġ�  
				x->parent->color = BLACK;//��x.p��w.rightΪ��ɫ+��תʹ��ȥ��x�Ķ����ɫ��  
				w->right->color = BLACK;
				LEFT_ROTATE(x->parent);
				x = root;//x��Ϊ����㣬����ѭ����  
			}
		}
		else//���º������if��֧����  
		{
			w = x->parent->left;
			if (w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				RIGHT_ROTATE(x->parent);
				w = x->parent->left;
			}
			if (w->left->color == BLACK&&w->right->color == BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				if (w->left->color == BLACK)
				{
					w->right->color = BLACK;
					w->color = RED;
					LEFT_ROTATE(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				RIGHT_ROTATE(x->parent);
				x = root;
			}
		}
	}x->color = BLACK;
}
void RB_DELETE(struct Tree*z)
{
	struct Tree*y = z, *x;//yΪ��ɾ������ƶ����  
	int y_original_color = y->color;//����z��ԭʼ��ɫ  
	if (z->left == nil)
	{
		x = z->right;//xָ��y��Ψһ�ӽ�������Ҷ�ӽ��  
		RB_TRANSPLANT(z, z->right);//����z.rightΪ���������滻��zΪ����������  
	}
	else if (z->right == nil)
	{
		x = z->left;//xָ��y��Ψһ�ӽ�������Ҷ�ӽ�� 
		RB_TRANSPLANT(z, z->left);//����z.leftΪ���������滻��zΪ����������  
	}
	else
	{
		y = TREE_MINIMUM(z->right);//�ҵ�z.right�ĺ�̡�  
		y_original_color = y->color;
		x = y->right;//xָ��y��Ψһ�ӽ�������Ҷ�ӽ��
		if (y->parent == z)
		{
			x->parent = y; 
		}
		else
		{
			RB_TRANSPLANT(y, y->right);//����y.rightΪ���������滻��yΪ����������  
			y->right = z->right;
			y->right->parent = y;
		}
		RB_TRANSPLANT(z, y);//����yΪ���������滻��zΪ����������  
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;//���Ѿ�ɾ���Ľ����ɫ��ֵ��y����֤��y���ϵ����ṹ������ʲ��䡣  
	}
	if (y_original_color == BLACK) //y��ԭʼ��ɫΪ��ɫ��˵����Ҫ���������ɫ��  
		RB_DELETE_FIXUP(x);
	SizeAdjust(root);   //���¼���sizeֵ
}

//�������������key,color,size
//�������  
void postorderTraverse(struct Tree *p)
{	

	if (p != nil)
	{
		postorderTraverse(p->left);
		postorderTraverse(p->right);
		dataout << p->key;
		if (p->color == 1) dataout << 'B';
		else dataout << 'R';
		dataout << p->size << ' ';
	}
}

//�������  
void preorderTraverse(struct Tree *p)
{
	if (p != nil)
	{	
		dataout << p->key;
		if (p->color == 1) dataout << 'B';
		else dataout << 'R';
		dataout << p->size << ' ';
		preorderTraverse(p->left);
		preorderTraverse(p->right);
	}
}

//�������  
void InorderTraverse(struct Tree *p)
{	
	
	if (p != nil)
	{
		InorderTraverse(p->left);
		dataout << p->key ;
		if (p->color == 1) dataout << 'B';
		else dataout << 'R';
		dataout <<p->size<< ' ';
		InorderTraverse(p->right);
	}
}

int main() {
	int  i,j,k,num;
	int  *b;
	int *a;
	a = new int[MAX];
	b = new int[N];
	//����n������������,�������������
	/*srand((unsigned)time(NULL));
	ofstream out("..\\input\\input_numble.txt");
	for (i = 0; i < MAX; i++) a[i] = i+1;//������a��������1~36
	for (i = 0; i < MAX; i++) {			
		j= rand() % MAX ;				//��a[i]��a[j]������a[j]Ϊ����һ����
		num = a[j];
		a[j] = a[i];
		a[i] = num;
	}
		for (i = 0; i < N; i++) {
				out << a[i] << endl;
			}	
	out.close(); */
	string filename;
	string filename1, filename2;
	filename = "..\\input\\input_numble.txt"; //�������ļ����ڵ��ļ�./Ϊ��ǰ�㣬../Ϊ�ϲ�
	LARGE_INTEGER li;
	long long f_time=0;
	ifstream in;
	int n;
	k = 0;
	for (n = 20; n <= N;n+=20){
		
		in.open(filename);
		if (!in)//����ļ��Ƿ��
		{
			cerr << "error: unable to open input file:" << filename << endl;
			system("pause");
			return -1;
		}
		for (i = 0; i < n; i++) {
			in >> b[i];
		}
			in.close();
	nil = new struct Tree[LEN];
	nil->key = Nil; nil->color = BLACK;  //����nil���
	nil->size = 0;

	ofstream timeout;
	filename1 = "..\\output\\size";
	filename1+=to_string(n);
	filename2 =filename1+ "\\time1.txt";
	timeout.open(filename2);
	long long f_start,f_end;
	QueryPerformanceCounter(&li);		//����ʱ��
	f_start = li.QuadPart;
		i = 0;
		root = nil;
		struct Tree*temp = new struct Tree[LEN];
		temp->key = b[i++];
		RB_INSERT(temp);	//������
		root = temp;
		while (i != n)
		{
			struct Tree*z = new struct Tree[LEN];
			z->key = b[i];
			RB_INSERT(z);
			i++;	
				if (i % 10 == 0) {  //ÿ����10��������һ��ʱ��
					QueryPerformanceCounter(&li);
					 f_end = li.QuadPart;
					f_time += (f_end - f_start);
					timeout <<"����"<<i-10<<"~"<< i << "��� time:" << f_end - f_start << endl;
					f_start = li.QuadPart;
				}
		}
		
		timeout << "������� time=" << f_time << endl;
		timeout.close();

		ROOT[k] = root;  //������õĺ��������㱣����ROOT[]������

		filename2 = filename1 + "\\preorder.txt";  //���������
		dataout.open(filename2);
		preorderTraverse(ROOT[k]);
		dataout.close();
		filename2 = filename1 + "\\inorder.txt";
		dataout.open(filename2);
		InorderTraverse(ROOT[k]);
		dataout.close();
		filename2 = filename1 + "\\posteorder.txt";
		dataout.open(filename2);
		postorderTraverse(ROOT[k]);
		dataout.close();

		struct Tree *result1,*result2;  //�ҵ�n/4,n/2���
		result1=os_select(ROOT[k], n / 4);
		result2 = os_select(ROOT[k], n / 2);
		filename2 = filename1 + "\\delete_data.txt";
		dataout.open(filename2);
		dataout << n << "/4��㣺" << result1->key;
		if (result1->color == 1) dataout << 'B';
		else dataout << 'R';

		dataout<< result1 ->size << endl;
			dataout << n << "/2��㣺" << result2->key;
			if (result2->color == 1) dataout << 'B';
			else dataout << 'R';
			dataout<< result2->size << endl;
		dataout.close();

		QueryPerformanceCounter(&li);		//����ɾ��ʱ��
		f_start = li.QuadPart;
		RB_DELETE(result1);
		QueryPerformanceCounter(&li);
		f_end = li.QuadPart;
		f_time = (f_end - f_start);

		filename2 = filename1 + "\\time2.txt";
		timeout.open(filename2);
		timeout << "delete n/4 time=" << f_time<<endl;

		QueryPerformanceCounter(&li);		//����ɾ��ʱ��
		f_start = li.QuadPart;
		RB_DELETE(result2);
		QueryPerformanceCounter(&li);
		f_end = li.QuadPart;
		f_time = (f_end - f_start);
		timeout << "delete n/2 time=" << f_time<<endl;
		
		timeout.close();
		filename2 = filename1 + "\\delete_inorder.txt";  //����ɾ���������
		dataout.open(filename2);
		InorderTraverse(ROOT[k]);
		dataout.close();
		k++;
	}
	return 0;
}