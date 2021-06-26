#include<stdio.h>
#include<string.h>
char name[32],gb,xb,maxname[32];
int qm,py,lw,n;

int main()
{
	scanf("%d",&n);
	getchar();
	int sum=0,max=0;
	while(n--)
{
	int money=0;
	scanf("%s %d %d %c %c %d",name,&qm,&py,&gb,&xb,&lw);
	getchar();
	if(qm>80&&lw)
	money+=8000;
	if(qm>85&&py>80)
	money+=4000;
	if(qm>90)
	money+=2000;
	if(qm>85&&xb=='Y')
	money+=1000;
	if(py>80&&gb=='Y')
	money+=850;
	sum+=money;
	if(money>max)
	{
	max=money;
	strcpy(maxname,name);
	}
}
	printf("%s\n%d\n%d",maxname,max,sum);
}
