#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

char input[200][20]; //输入保存
char str[20]; //每项的输入
char files[200][20]; //保存要输出的文件（只保存最近目录下的，用来排序用）
int blank;//空格的次数
int dirs[200]; //用来表示嵌套的第几次文件，每项纪录的是当前目录在input中的排序
int dnum; //当前在哪个目录下，和dirs搭配使用
/*输出空格*/
void printBlank(){ 
	for(int i=0;i<blank;i++){
	printf("| ");
	}
}
/**排序的函数，搭配qsort*/

int compare(const void *elem1,const void *elem2)
{
	return (strcmp((char*)elem1,(char*)elem2));
}

//对输入的项进行处理
void process(int pos){
	switch(input[pos][0]){
	case '*':{ //遇到结尾的处理，从当前位置向上数到头，遇到file就保存，准备输出
			int i=pos;
			int j=0;
			while(i>=0){
			if(input[i][0]=='f'){
			strcpy(files[j++],input[i]);
			}	
			i--;
			}	
			qsort(files,j,20,compare);
			for(i=0;i<j;i++){
				printBlank();
				puts(files[i]);
				}
			break;
		}	
	case 'd':{ //遇到目录就输出
			blank++;
			printBlank();
			printf("%s\n",input[pos]);
			dirs[dnum++]=pos;
			process(pos+1);
			break;
		}
	case 'f':{ //遇到文件就跳过
		process(pos+1);
		break;
	}
	case ']':{ //遇到]准备打印当前目录下的文件
		int i=pos;
		int j=0;
		while(i>dirs[dnum-1]){
			if(input[i][0]=='f'){
			strcpy(files[j++],input[i]);
			input[i][0]='s';
			}
		i--;
		}
		qsort(files,j,20,compare);
		for(i=0;i<j;i++){
		printBlank();
		puts(files[i]);
	}
	if(dnum>1) dnum--;
	blank--;
	process(pos+1);
	break;
	}
	}
}

int main(){
	int i=0;
	int flag=0;
	int n=1;
	while(scanf("%s",str)!=EOF){ //读入字符串
		if(str[0]=='#') break; //结束
		if(str[0]!='*'){ //一直输入
		strcpy(input[i++],str);
		}else{
		strcpy(input[i],"*"); //遇到一组结束，准备处理
		printf("DATA SET %d:\n",n++);
		printf("ROOT\n");
		blank=0;
		process(0);
		i=0;	
		puts("");	
	}
	}
	system("pause");
	return 0;
}
