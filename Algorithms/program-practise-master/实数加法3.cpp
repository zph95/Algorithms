# include <stdio.h>
# include <string.h>
# include <stdlib.h>
int main(){
	int answer;
	int i=0;
	int j=0;
	int tmp;
	int flag=0;//记录两数组大小 
	int count;
	char str1[100],str2[100];
	int an[100],bn[100],temp[100],result[100];
	int len1,len2,len3;

	memset(an,0,sizeof(an));
	memset(bn,0,sizeof(bn));
	memset(temp,0,sizeof(temp));
	memset(result,0,sizeof(result));
	gets(str1);
	gets(str2);
    len1=sizeof(str1);
    len2=sizeof(str2);
    for(i=len1-1,j=0;i>=0;i--){
    	an[j++]=str1[i]-'0';
	}
	for(i=len2-1,j=0;i>=0;i--){
		bn[j++]=str2[i]-'0';
	}
	if(len1>len2) flag=1;
	else for(i=len2-1;i>=0;i--){
		if(an[i]>bn[i]) {
			flag=1;break;
		}
	}
	if(flag){
		for(i=0;i<len1;i++){
			temp[i]=an[i];
			an[i]=bn[i];
			bn[i]=temp[i];
		}
		tmp=len1;
		len1=len2;
		len2=tmp;
	}
	for(i=0;i<len1;i++) result[i]=an[i];
	for(answer=1; ;answer++) {
		for(i=0;i<len3;i++){//len3>len1
		for(j=0;j<len1;j++){
			result[i+j]+=an[j]*result[i]; 
		}	
		}
		for(i=0;i<len1+len3;i++){
			if(result[i]>=10){
				result[i+1]+=result[i]/10;
				result[i]=result[i]%10;
			}	
		}
		if(result[len1+len3]>0) len3=len1+len1;
		if(len2<len3) break;
	    if(len2=len3){	
	    for(i=len2-1;i>=0;i--){
		if(result[i]>bn[i]) break;
		if(result[i]==bn[i]&&(i==len2-1)) answer++;break;
			
    }
	}
	
	}
	if(flag) answer=-answer;
	printf("%d",answer);
	return 0;	
		
	
    
} 
