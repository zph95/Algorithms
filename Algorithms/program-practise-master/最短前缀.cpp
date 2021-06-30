# include<stdio.h>
# include<string.h>
int main(){
	char str[1001][21],c;
	int mark[1001]={0};
	int n=0,i,j,k;
	while(gets(str[n])!=NULL&&str[n][0])     //ÅĞ¶Ï½áÊøÊäÈë 
	     n++;
	for ( i = 0; i < n-1;i++ )
 		for ( j = i+1; j < n; j++ ){
			for ( k = 0; str[i][k]!='\0' &&str[j][k]!='\0'; k++ )
			{
 			if ( str[i][k] != str[j][k] ) break;
			if ( k >=mark[i] ) mark[i]++;
			if ( k >=mark[j] ) mark[j]++;
			}
		}
	for(i=0;i<n;i++){
		printf("%s ",str[i]);
		for(k=0;k<=mark[i];k++){
			c=str[i][k];
			if(c!='\0') putchar(c);
		}
		putchar('\n');
	}
	return 0; 
}
