# include <stdio.h>
# include <stdlib.h>
# include <string.h>
int Maxlen1(char *str){
	int i;
	while(1){
		if(str[i]=='.') break;
		i++;
	}
	return i;
}
int Maxlen2(char *str,int n){
	int i;
	int a;
    for(i=n+1; ;i++){
    	if(str[i]=='\0') break;
		i++; 
	} 
	a=i-n-1;
	return a;
}
void Addint(int *an1,int *an2,int max){
	int i;
	for(i=0;i<max;i++){
		an1[i]+=an2[i];
		if(an1[i]>=10){
			an1[i]-=10;
			an1[i+1]++;
		}
	}
}

int main(){
	int i;
	int count=0;
	char str1[100],str2[100];
	char temp1[100],temp2[100];
	int an1[100],an2[100];
	char teip1[100],teip2[100];
	int ani1[100],ani2[100];
	memset(an1,0,100);
		memset(temp1,'\0',100);
		memset(temp2,'\0',100);
		memset(teip1,'\0',100);
		memset(teip1,'\0',100);
	memset(an2,0,100);
    memset(ani2,0,100);
    memset(ani1,0,100);
    int max1,max2,max;
	int maxx1,maxx2,maxx;
	gets(str1);
	gets(str2);
	max1=Maxlen1(str1);//??¨ºy2?¡¤?3¡è?¨¨ 
	//printf("%d\n",max1);
	max2=Maxlen1(str2);
	maxx1=Maxlen2(str1,max1);//D?¨ºy2?¡¤?3¡è?¨¨ 
	//printf("%d\n",maxx1);
	//????D?¨ºy2?¡¤? 
	maxx2=Maxlen2(str2,max2);
	//printf("%d",maxx2);
	strncpy(temp1,str1+max1+1,maxx1); //puts(temp1);
	strncpy(temp2,str2+max2+1,maxx2);
	
	maxx=maxx1;
	if(maxx<maxx2) {
	maxx=maxx2;
	for(i=maxx1-1;i<maxx2-1;i++){
		temp1[i]='0';
	}
	temp1[maxx2-1]='\0'; 
}
printf("%d\n",maxx1);
    if(maxx>maxx2){
    	for(i=maxx2-1;i<maxx1-1;i++){
    		temp2[i]='0';
		}
		temp2[maxx1-1]='\0'; 
	}
	//puts(temp2);
	strrev(temp1);puts(temp1);
	strrev(temp2);
	
	for(i=0;i<maxx;i++){
		an1[i]=temp1[i]-'0';
		an2[i]=temp2[i]-'0';
	}
	for(i=0;i<maxx;i++){
		printf("%d",an1[i]);
	}
	printf("\n");
	Addint(an1,an2,maxx);
	for(i=0;i<maxx;i++){
		printf("%d",an1[i]);
	}
		printf("\n");
	if(an1[maxx-1]>10){
		an1[maxx-1]-=10;
		count=count+1;
	}
	//puts(temp1);
    strncpy(teip1,str1,max1); //puts(teip1);
	strncpy(teip2,str2,max2);//puts(teip2);
	strrev(teip1);
	strrev(teip2);//puts(teip2);
	
	
	max=max1;
	if(max<max2) max=max2;
	for(i=0;i<max;i++){
		ani1[i]=teip1[i]-'0';
		ani2[i]=teip2[i]-'0';
	}
	Addint(ani1,ani2,max);
	if(ani1[max-1]>10){
		ani1[max-1]-=10;
		ani1[max]++;
		max=max+1;
	}
	if(count==0)  ;
	else if(count==1)  {
		ani1[0]+=count;
		for(i=0;i<max;i++)
		{
			if(ani1[i]>=10){
			ani1[i]-=10;
			ani1[i+1]++;
		}
		}
	}
	
	for(i=max-1;i>=0;i--){
		printf("%d",ani1[i]);
		
	}
	printf("%c",'.');
	//puts(teip1);
//	printf("\n");
	for(i=maxx-1;i>=0;i--){
		printf("%d",an1[i]);
			}
	return 0;

}

