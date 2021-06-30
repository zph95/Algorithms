# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# define MAX 100
void Addfloat(int *an1,int *an2,int maxlen){//求两个整数之和并将和放在数组an1中。数组长度最大为maxlen 
	int i,j;
	for(i=0;i<maxlen;i++){
		an1[i]+=an2[i];
		if(an1[i]>=10){
			an1[i+1]+=1;
			an1[i]=an1[i]-10;
		}
	}
}
int Maxlen1(char *str){          //整数部分的长度 
        int i;
		while(1){
 		
 		if(str[i]!='.') break;
 		i++;
 	}
 	return i;
}
int Maxlen2(char *str,int i){    //小数部分的长度 
	int j;
	for(j=i+1; ;j++){
		if(str[j]=='\0') break;
	}
	return j-i-1;	
}
 int main(){
 	char str1[MAX],str2[MAX];
 	char tmp1[MAX],tmp2[MAX],tmp3[MAX];
 	int an1[MAX],an2[MAX];
 	gets(str1);//printf("%s",str1);
 	gets(str2);
 	int i=0,j,max,max1;
 	int maxlen1,maxlen2;
 	int tme,tmf;
 	/*memset(tmp1,'\0',MAX);
    memset(tmp2,'\0',MAX);
    memset(tmp3,'\0',MAX);
    maxlen1=Maxlen1(str1);*/
    strncpy(tmp1,str1,maxlen1);//printf("%s",tmp1);
    
	maxlen2=Maxlen2(str1,maxlen1); 
	tme=Maxlen1(str2);//printf("%d",tme);
	strncpy(tmp2,str1+1+maxlen1,maxlen2);//printf("%s",tmp2);
    strncpy(tmp3,str2+1+tme,tmf);
    tmf=Maxlen2(str2,tme);
    tmf=Maxlen2(str2,tme);
    if(tmf>maxlen2){
 	max=tmf;
 }
 	else max=maxlen2;
 
    for(i=max-1;i>=0;i--){
 	tmp2[i]+=tmp3[i];
 	if(tmp2[i]>=10&&i>0){
 		tmp2[i-1]+1;
 		tmp2[i]--;
 		
	 }
 	
 }
 if(tmp2[0]>=10){
 	tmp1[0]++;
 }
	if(maxlen1<tme){
		max1=tme;
	}
		else max1=maxlen1;
	
	strncpy(tmp2,str2,tme);
	
	strrev(tmp1);//printf("%s",tmp1);
	strrev(tmp2);
	 for(i=0;i<max1;i++){
	 	tmp1[i]+=tmp2[i];
	 	if(tmp1[i]>=10){
	 		tmp1[i+1]++;//printf("%d\n",tmp1[i]);
	 		tmp1[i]--;
		 }
	 }
	 if(tmp1[max1]!='0') max1++;
	 //for(i=max-1;i>=0;i--){
	// printf("%d",tmp1[i]);
	// printf("."); 	
 
  for(i=max1-1;i>=0;i--){
  printf("%d",tmp1[i]);
	printf("."); 
	for(i=0;i<max;i++){
		printf("%d",tmp2[i]);
	}	
 
 }
 return 0;
}
 
