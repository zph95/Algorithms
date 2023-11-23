// #include <stdio.h>

// int main(int argc, char const *argv[]) {
//   printf("Hello World!\n");
// }

#include "pthread.h"
#include <stdio.h>

int N;
void *fib() {
  int i;
  int fib_a = 0;
  int fib_b = 1;
  int sum;
  printf("%d %d", fib_a, fib_b);
  for (i = 0; i < N - 2; i++) {
    sum = fib_a + fib_b;
    fib_a = fib_b;
    fib_b = sum;
    printf(" %d", sum);
  }
  pthread_exit(0);
}

int main(int argc, char const *argv[]) {
  printf("Hello World!\n");
  char *number;
  printf("please input the number N\n");
  scanf("%d", &N);
  pthread_t tid;
  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_create(&tid, &attr, fib, NULL);
  pthread_join(tid, NULL);
  printf("\nthe pthread finish");
}
