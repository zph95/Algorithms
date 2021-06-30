# include<stdio.h>
# include<string.h>
# include<ctype.h>
# define MAX_LEN 101
int an1[MAX_LEN+10],an2[MAX_LEN+10];
char szLine1[MAX_LEN+10], szLine2[MAX_LEN+10]; 

int Add(int nMaxLen, int *an1, int *an2,int *nh,int *nl) {
	int i,j=0;
	*nh=0;*nl=0;
	for(i=0;i<nMaxLen;i++){
		an1[i]+=an2[i];
		if(an1[i]>=10){
			an1[i]-=10;
			an1[i+1]++;
		}
		if(an1[i])    *nh=i;
	}
	while(an1[j]==0){
		j++;
		*nl=j;
	}
	return 0;
} 

	
int main(){
	char s[10];
	int n,m;
	int nhighest,nlowest; //分别记录最高位，最低位
	int *nh=&nhighest,*nl=&nlowest;
	scanf("%d",&n);
	while(n>0){
		n--;
		scanf("%s",szLine1); scanf("%s",szLine2);
		memset(an1, 0, sizeof(an1));       memset(an2, 0, sizeof(an2)); 
		int i, j; 
		int npoint1=0,npoint2=0; 
		int nLen1 = strlen(szLine1);
		for(i=nLen1-1;i>=0;i--)
			if(isalnum(szLine1[i]))  npoint1++;
			else break;
	
		for (j = 0, i = nLen1 - 1; i >= nLen1-npoint1; i--) 
			an1[j++] = szLine1[i] - '0';
		i--;
		for( ;i>=0;i--)
			an1[j++] = szLine1[i] - '0';
		
		int nLen2 = strlen(szLine2); 
		for(i=nLen2-1;i>=0;i--)
			if(isalnum(szLine2[i]))  npoint2++;
			else break;
		for (j = 0, i = nLen2 - 1; i >= nLen2-npoint2; i--) 
			an2[j++] = szLine2[i] - '0';
		i--;
		for( ;i>=0;i--)
			an2[j++] = szLine2[i] - '0';
			
	    if(npoint1<npoint2){						//压位补0 
			m=npoint2-npoint1;
			for(i=nLen1-2;i>=0;i--)
				if(i>m) {
				an1[m+i]=an1[i];
				}
				else {an1[m+i]=an1[i];
				an1[i]=0;}
			nLen1+=m;
			npoint1=npoint2;
	     }   
		
		else  if(npoint1>npoint2){
			    m=npoint1-npoint2;
			    for(i=nLen2-2;i>=0;i--)
				if(i>m) an2[m+i]=an2[i];
				else {
				an2[m+i]=an2[i];
			    an2[i]=0;
			}
			    nLen2+=m;		
			}
	
			
		Add(MAX_LEN,an1,an2,nh,nl);	

	
		for(i=nhighest;i>=npoint1;i--)
			printf("%d",an1[i]);
		if(nhighest<npoint1) printf("0");
		printf(".");
		for(i=npoint1-1;i>=nlowest;i--)
			printf("%d",an1[i]);
		if(n>0) printf("\n");	
		gets(s);		
	}
	return 0;
} 
