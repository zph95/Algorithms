#include <memory.h>
#include <string.h> 
#include <stdio.h> 
#include <stdbool.h>
#include<math.h>
# define MAX 20
int wallori[MAX][MAX];
int wall[MAX][MAX];
char wallorigin[MAX][MAX];
int  wallpaint[MAX][MAX];
int min;
void paintstatus(int j,int n,int *paint){
	int i;
	for(i=0;i<n;i++)
		paint[i]=(j>>i)&1;
}
void Applypaint( int *wallq, int *wallnext, int *paint,int n){
	for ( int i = 0; i < n; i++ ) {
		if( paint[i] ) {
			if ( i > 0 ) wallq[i-1] = 1 - wallq[i-1]; 
			wallq[i] = 1-wallq[i]; 
			if ( i < n-1) wallq[i+1] = 1 - wallq[i+1]; 
			wallnext[i] = 1 - wallnext[i];
		}
	}
}
void OutputResult(int wallpaint[][20],int n){
	int i,j,sum=0;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			sum=sum+wallpaint[i][j];
	if(sum<min) min=sum;
	
}  
int  main(){
	int i,j,k,n,m;
	char s;
		scanf("%d",&n);
		for(i=0;i<n;i++)
			{	
				scanf("%s",wallorigin[i]);

			}
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
				if(wallorigin[i][j]=='y') wallori[i][j]=1;
				else wallori[i][j]=0;
		m=pow(2,n);
		min=n*n+1;
		for(j=0;j<m;j++){
			memcpy(wall,wallori,sizeof(wall));
			paintstatus(j,n,wallpaint[0]);
			for( k = 0; k < n; k++ ) { 	
				Applypaint( wall[k],wall[k+1], wallpaint[k],n); 
					for(int p=0;p<n;p++){
					if(wall[k][p]==1) wallpaint[k+1][p]=0;
					else wallpaint[k+1][p]=1; 
				}	
			}
			bool bOk=true;
			for (  k = 0; k < n; k ++ ) { 
			if ( wall[n-1][k] ==0) { bOk = false; break;}
			}
			if ( bOk )  { OutputResult(wallpaint,n);}
		}
		if(min==n*n+1) printf("inf\n");
		else printf("%d\n",min); 
	return 0;
}
