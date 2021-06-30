#include <stdio.h>
int main()
{
    unsigned short a,b;
    unsigned short aa;
    int n;
    scanf("%d",&n);
    int i;
    for(i = 0;i < n;i++)
    {
        scanf("%hu%hu",&a,&b);
        int N;
        bool A = false;
        for(N = 0;N < 16;N++)
        {
            aa=( a >> (16-N) ) | (a << N);      //Ñ­»·ÒÆÎ»
            if( aa == b)
            {
                printf("YES\n");
                A = true;
                break;
            }
        }
        if( !A )
            printf("NO\n");
    }
    return 0;
}
