#include <stdio.h>

#define N 100

int main(){
    int a[N+2][N+2];
    int n, i, j, area=0, border=0;
    scanf("%d", &n);

    for (i=1; i<=n; i++) {
        for (j=1; j<=n; j++) {
        scanf("%d", &a[i][j]);
        }
    }

    for (i=0; i<=n+1; i++) {
         a[i][0] = 51; 
         a[i][n+1] = 51; 
   }
   for (j=0; j<=n+1; j++) {
   a[0][j] = 51; 
   a[n+1][j] = 51; 
   }

   for (i=1; i<=n; i++) {
       for (j=1; j<=n; j++) {
       if (a[i][j] <= 50) {
       area += 1; 
       if (a[i-1][j]>50 ||
       a[i+1][j]>50 ||
       a[i][j-1]>50 ||
       a[i][j+1]>50 ) {border += 1; }
       }
       }
   }

   printf("%d %d\n", area, border);
   return (0);
}
