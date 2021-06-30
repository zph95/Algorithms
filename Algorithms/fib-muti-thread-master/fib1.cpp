#include<stdio.h>
#include<windows.h> 
int N;
DWORD WINAPI fib(LPVOID param){
	int i;
	int fib_a=0;
    int fib_b=1;
	int sum;
	printf("%d %d",fib_a,fib_b);
	for (int i=0;i<N-2;i++){
		sum=fib_a+fib_b;
		fib_a=fib_b;
		fib_b=sum;
		printf(" %d",sum);
	}	
	return DWORD();
}

int main(){
	printf("please input the number N\n");
	scanf("%d",&N);
	HANDLE ThreadHandle;
	ThreadHandle=CreateThread(NULL,0,fib,NULL,0,NULL);
	if(ThreadHandle!=NULL){
		WaitForSingleObject(ThreadHandle,INFINITE);
		CloseHandle(ThreadHandle);
		printf("\nthe windows thread finished");
	}
	return 0;
} 


