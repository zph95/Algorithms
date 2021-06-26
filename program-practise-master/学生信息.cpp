# include<stdio.h>
# include<string.h>
# include<ctype.h>
# include<stdlib.h>

struct student{
	char name[20];
	int number;
	char sex;
	int age;
}stu[100];

int Compare( const void * name1, const void * name2 )
{
student * p1;
student * p2;

p1 = ( student * ) name1;
p2 = ( student * ) name2;

return _stricmp( (*(student *)name1).name , (*(student *)name2).name );
}

int main(){
	struct student temp;
	int n=0,i,j,k;char s[20];
	gets(stu[n].name);
	do{
		scanf("%d,%c %d",&stu[n].number,&stu[n].sex,&stu[n].age);
		n++;
		gets(s);
		gets(stu[n].name);
	}while(isalpha(stu[n].name[0]));
	
	qsort(stu, n, sizeof( stu[0] ), Compare );

/*	for(i=0;i<n-1;i++){
	   k=i;
	   for(j=i+1;j<n;j++)
	   if(strcasecmp(stu[k].name,stu[j].name)>0) k=j;
	   if(k!=i){
	   	temp=stu[k];stu[k]=stu[i];stu[i]=temp;
	   }
	   
}*/
	n=0;
	do{
		puts(stu[n].name);
	    printf("%08d,%c %d\n",stu[n].number,stu[n].sex,stu[n].age);
	    n++;
	}while(isalpha(stu[n].name[0]));
	return 0;
}
