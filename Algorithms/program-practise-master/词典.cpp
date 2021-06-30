# include<stdio.h>
# include<stdlib.h>
# include<string.h>
struct dictionary{
	char english[11],foreign[11];
}dic[100010],s;

int compare(const void *p1,const void *p2){
	return strcmp((*(dictionary *)p1).foreign,(*(dictionary *)p2).foreign);
}

int main(){
	int n=0;
	char temp[30];
	dictionary * p;
	while(1){
		gets(temp);
		if(temp[0]=='\0')  break;
		sscanf(temp,"%s%s",dic[n].english,dic[n].foreign);
		n++;
	}
	qsort(dic,n,sizeof(dic[0]),compare);
	while(scanf("%s", temp)!= EOF)
   {
        sscanf(temp,"%s",s.foreign);
		p=(dictionary*)bsearch(&s,dic,n,sizeof(dictionary),compare);
		if(p!=NULL)  printf("%s\n",p->english);
		else  printf("eh\n");	
	}
	return 0;
}
