#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int efkl2(int a, int b, int *x, int *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1; 
    int gcd = efkl2(b%a, a, &x1, &y1);

    // Update x and y using results of recursive
    *x = y1 - (b/a) * x1;
    *y = x1;

    return gcd;
}


void usage(void){
        printf("Type 2 integers with a space between them and hit Enter\n");
}

int main(int argc, char *argv[])
{
    int x, y, a, b;
     if(argc!=3){
		do{
			usage();

		}while(scanf("%d%d",&a, &b)!=2);

     }else{
                a=atoi(argv[1]);
                b=atoi(argv[2]);
     }
    int g = efkl2(a, b, &x, &y);
    printf("gcd(%d, %d) = %d = %d*%d + %d*%d\n",
           a, b, g, x, a, y, b);
    return 0;
}
