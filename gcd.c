#include <stdio.h>


int greatestCommonDivisor(int a, int b)
{
    int r;

    // Check For Proper Input. Fix Input.
    if(b == 0)
        return a; //gcd(a,0)=a
    if(a < 0) a=-a;
    if(b < 0) b=-b;

	//gcd(a,b)=gcd(b,amodb);
    do
    {
        r = a % b;
        if(r == 0)
            break;
        a = b;//new a
        b = r;//new b
    }
    while(1);

    return b;
}


void usage(void){
	printf("Type 2 integers with a space between them and hit Enter\n");
}

int main(int argc, char *argv[])
{
	int num1,num2;

	if(argc!=3){ 							  
		while(scanf("%d%d",&num1,&num2)!=2){ 
			usage();				       
			while(getchar()!='\n');       
		}
	}else{
		num1=atoi(argv[1]);
		num2=atoi(argv[2]);
	}
    int gcd = greatestCommonDivisor(num1, num2);
    printf("The GCD of %d and %d is %d\n", num1, num2, gcd);
    getchar();
    return 0;
}
