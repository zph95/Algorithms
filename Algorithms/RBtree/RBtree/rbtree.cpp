#include<iostream>
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<fstream>
#include<string>
#include<windows.h> //使用window系统的计时api
#define N 80//数据规模
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
void SizeAdjust(struct Tree*T) //递归调整size值
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
			struct Tree*y = z->parent->parent->right;//叔结点  
			if (y->color == RED) 
			{//解决了z的父结点和z都是红色结点问题  
				z->parent->color = BLACK;		//case 1:叔结点为红色
				y->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;//把z的祖父结点当成新结点z进入下一次循环  
			}
			else
			{
				if (z == z->parent->right)//case2：z是一个右孩子且叔结点为黑色 
				{//使用一个左旋让情况2转变为情况3  
					z = z->parent; //case2
					LEFT_ROTATE( z); 
				}
				z->parent->color = BLACK;//case3：是z是一个左孩子且叔结点为黑色，改变z的父和祖父结点颜色并做一次右旋，以保持性质5  
				z->parent->parent->color = RED;
				RIGHT_ROTATE( z->parent->parent); 
			}
		}
		else//下面else分支类似于上面
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
	root->color = BLACK;//最后给根结点着为黑色。  
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
	z->left = nil;//给插入结点左右孩子结点置空。  
	z->right = nil;
	z->color = RED;//给插入结点着为红色。  
	RB_INSERT_INSERT_FIXUP(z);  //调整结点
	SizeAdjust(root);//重新计算size值
}

void RIGHT_ROTATE( struct Tree*x)
{//右旋转  
	struct Tree*y = x->left;//设置y结点。  
	x->left = y->right;//本行以及if结构表示“y的右孩子成为x的左孩子”
	if (y !=nil &&y->right != nil)
	{
		y->right->parent = x;
	}
	y->parent = x->parent;//本行以及if-else结构表示“y成为该子树新的根”
	if (x->parent == nil)
	{
		root = y;
	}
	else if (x == x->parent->right)//该if结构表示“y成为x父亲的孩子”
	{
		x->parent->right = y;
	}
	else x->parent->left = y;
	y->right = x;//x成为y的右孩子
	x->parent = y;
}

void LEFT_ROTATE( struct Tree*x)
{ //左旋转
	struct Tree*y = x->right;//设置y结点。  
	x->right = y->left;//本行以及if结构表示“y的左孩子成为x的右孩子”。
	if (y != nil&&y->left != nil)
	{
		y->left->parent = x;
	}
	y->parent = x->parent;//本行以及if-else结构表示“y成为该子树新的根”。 
	if (x->parent == nil)
	{
		root = y;
	}
	else if (x == x->parent->left)//该if结构表示“y成为x父亲的孩子”
	{
		x->parent->left = y;
	}
	else x->parent->right = y;
	y->left = x;//x成为y的左孩子
	x->parent = y;
}

void RB_TRANSPLANT(struct Tree*u, struct Tree*v) //用v子树替换u子树
{
	if (u->parent == nil)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else u->parent->right = v;
	v->parent = u->parent;
}
  
struct Tree*TREE_MINIMUM(struct Tree*x)
{//非递归版本的查找二叉查找树的最小值
	while (x->left != nil)
	{
		x = x->left;
	}
	return x;
}

void RB_DELETE_FIXUP(struct Tree*x)
{
	struct Tree*w = nil;//w是x的兄弟结点  
	while (x != root&&x->color == BLACK)//如果x是黑色并且不是根结点，才进行循环。  
	{//x是一个具有双重颜色的结点，调整的目的是把x的黑色属性向上移动。  
		if (x == x->parent->left)
		{
			w = x->parent->right;
			if (w->color == RED)//情况一：x的兄弟结点w是红色的。  
			{//改变w和x.p的颜色+一次旋转使其变为情况二，三，四。  
				w->color = BLACK;
				x->parent->color = RED;
				LEFT_ROTATE(x->parent);
				w = x->parent->right;
			}
			if (w->left->color == BLACK&&w->right->color == BLACK)//情况二：x的兄弟结点w是黑色的，而且w的两个子节点都是黑色。  
			{
				w->color = RED;//从x和w上去掉一重黑色。x还是黑色，而w变为红色。  
				x = x->parent;//x结点向上移动成为新的待调整结点。  
			}
			else
			{
				if (w->right->color == BLACK)//情况三：x的兄弟结点w是黑色的，w的左孩子是红色的，w的右孩子是黑色的。  
				{//交换w和w.left的颜色+旋转使其转变为情况四。  
					w->left->color = BLACK;
					w->color = RED;
					RIGHT_ROTATE(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;//以下是情况四：x的兄弟结点w是黑色的，且w的右孩子是红色的。  
				x->parent->color = BLACK;//置x.p和w.right为黑色+旋转使其去掉x的额外黑色。  
				w->right->color = BLACK;
				LEFT_ROTATE(x->parent);
				x = root;//x成为根结点，结束循环。  
			}
		}
		else//以下和上面的if分支类似  
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
	struct Tree*y = z, *x;//y为待删除或待移动结点  
	int y_original_color = y->color;//保存z的原始颜色  
	if (z->left == nil)
	{
		x = z->right;//x指向y的唯一子结点或者是叶子结点  
		RB_TRANSPLANT(z, z->right);//把以z.right为根的子树替换以z为根的子树。  
	}
	else if (z->right == nil)
	{
		x = z->left;//x指向y的唯一子结点或者是叶子结点 
		RB_TRANSPLANT(z, z->left);//把以z.left为根的子树替换以z为根的子树。  
	}
	else
	{
		y = TREE_MINIMUM(z->right);//找到z.right的后继。  
		y_original_color = y->color;
		x = y->right;//x指向y的唯一子结点或者是叶子结点
		if (y->parent == z)
		{
			x->parent = y; 
		}
		else
		{
			RB_TRANSPLANT(y, y->right);//把以y.right为根的子树替换以y为根的子树。  
			y->right = z->right;
			y->right->parent = y;
		}
		RB_TRANSPLANT(z, y);//把以y为根的子树替换以z为根的子树。  
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;//把已经删除的结点颜色赋值给y，保证了y以上的树结构红黑性质不变。  
	}
	if (y_original_color == BLACK) //y的原始颜色为黑色，说明需要调整红黑颜色。  
		RB_DELETE_FIXUP(x);
	SizeAdjust(root);   //重新计算size值
}

//遍历操作，输出key,color,size
//后序遍历  
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

//先序遍历  
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

//中序遍历  
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
	//生成n个互异的随机数,采用随机交换法
	/*srand((unsigned)time(NULL));
	ofstream out("..\\input\\input_numble.txt");
	for (i = 0; i < MAX; i++) a[i] = i+1;//将数组a中数字置1~36
	for (i = 0; i < MAX; i++) {			
		j= rand() % MAX ;				//将a[i]与a[j]交换，a[j]为任意一个数
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
	filename = "..\\input\\input_numble.txt"; //打开其它文件夹内的文件./为当前层，../为上层
	LARGE_INTEGER li;
	long long f_time=0;
	ifstream in;
	int n;
	k = 0;
	for (n = 20; n <= N;n+=20){
		
		in.open(filename);
		if (!in)//检查文件是否打开
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
	nil->key = Nil; nil->color = BLACK;  //设置nil结点
	nil->size = 0;

	ofstream timeout;
	filename1 = "..\\output\\size";
	filename1+=to_string(n);
	filename2 =filename1+ "\\time1.txt";
	timeout.open(filename2);
	long long f_start,f_end;
	QueryPerformanceCounter(&li);		//计算时间
	f_start = li.QuadPart;
		i = 0;
		root = nil;
		struct Tree*temp = new struct Tree[LEN];
		temp->key = b[i++];
		RB_INSERT(temp);	//插入结点
		root = temp;
		while (i != n)
		{
			struct Tree*z = new struct Tree[LEN];
			z->key = b[i];
			RB_INSERT(z);
			i++;	
				if (i % 10 == 0) {  //每插入10个结点测试一下时间
					QueryPerformanceCounter(&li);
					 f_end = li.QuadPart;
					f_time += (f_end - f_start);
					timeout <<"插入"<<i-10<<"~"<< i << "结点 time:" << f_end - f_start << endl;
					f_start = li.QuadPart;
				}
		}
		
		timeout << "构造完成 time=" << f_time << endl;
		timeout.close();

		ROOT[k] = root;  //将构造好的红黑树根结点保存在ROOT[]数组中

		filename2 = filename1 + "\\preorder.txt";  //遍历红黑树
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

		struct Tree *result1,*result2;  //找到n/4,n/2结点
		result1=os_select(ROOT[k], n / 4);
		result2 = os_select(ROOT[k], n / 2);
		filename2 = filename1 + "\\delete_data.txt";
		dataout.open(filename2);
		dataout << n << "/4结点：" << result1->key;
		if (result1->color == 1) dataout << 'B';
		else dataout << 'R';

		dataout<< result1 ->size << endl;
			dataout << n << "/2结点：" << result2->key;
			if (result2->color == 1) dataout << 'B';
			else dataout << 'R';
			dataout<< result2->size << endl;
		dataout.close();

		QueryPerformanceCounter(&li);		//计算删除时间
		f_start = li.QuadPart;
		RB_DELETE(result1);
		QueryPerformanceCounter(&li);
		f_end = li.QuadPart;
		f_time = (f_end - f_start);

		filename2 = filename1 + "\\time2.txt";
		timeout.open(filename2);
		timeout << "delete n/4 time=" << f_time<<endl;

		QueryPerformanceCounter(&li);		//计算删除时间
		f_start = li.QuadPart;
		RB_DELETE(result2);
		QueryPerformanceCounter(&li);
		f_end = li.QuadPart;
		f_time = (f_end - f_start);
		timeout << "delete n/2 time=" << f_time<<endl;
		
		timeout.close();
		filename2 = filename1 + "\\delete_inorder.txt";  //遍历删除后的序列
		dataout.open(filename2);
		InorderTraverse(ROOT[k]);
		dataout.close();
		k++;
	}
	return 0;
}