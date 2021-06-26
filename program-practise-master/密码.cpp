#include<stdio.h>
#include<string.h>
#define MAX 256
int n,i,map[MAX],tmp,num,k,time[MAX];
char str[MAX],str2[MAX];
int main(){
	while(scanf("%d",&n)!=EOF&&n){
		for(i=0;i<n;i++){
			scanf("%d",&map[i]);
			map[i]--;
		}
		for(i=0;i<n;i++){
			tmp=i;
			num=0;
			do{
			tmp=map[tmp];
			num++;
			}while(tmp!=i);
			time[i]=num;
		}
		while(scanf("%d",&k)!=EOF&&k){
			getchar();
			gets(str);
			for(i=0;i<n;i++)
			str2[i]=' ';
			for(i=0;str[i]!=0;i++){
				num=k%time[i];
				tmp=i;
				while(num--) tmp=map[tmp];
				str2[tmp]=str[i];
			}
			str2[n]=0;
			puts(str2);
		}
		putchar('\n');
	}
	return 0;
}
