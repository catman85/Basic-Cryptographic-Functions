#include <stdio.h>

int mulInverse(int w, int m);
int gcd(int a, int b);
void cleanup(char *input);

int main(){

	printf("Enter Message: \n");
	char msg[40];//maximum capacity
	scanf("%40s",msg);

	printf("Enter Keys (two numbers): \n");
	int a,b;
	scanf("%d",&a);
	scanf("%d",&b);

	if(gcd(a,26)!=1 || a==0){
		puts("Error: gcd(firstNumber,26)!=1 OR firstNumber==0 \n");
		return 0;
	}
	//Capitalizing Input
	int i=0;
	while(msg[i]!='\0'){
		if(msg[i]>=97 && msg[i]<=122){
				msg[i]-=32;
		}
		i++;
	}
	int msgsize=i;

    cleanup(msg);
	//converting msg to an integer array
	int imsg[40];
	for(i=0;i<msgsize;i++){
		imsg[i]=msg[i]-64; //A==1 B==2
	}




    //----------------
	//encrypt
	//english alphabet 26 letters
	printf("\nEncrypting...\n");
	int icipher[msgsize];
	for(i=0;i<msgsize;i++){
			icipher[i]=(a*imsg[i]+b)%26;
	}
	for(i=0;i<msgsize;i++){
			printf("%c",icipher[i]+64);
	}
	puts("\n");

    //---------------
	//decrypt
	printf("Decrypting...\n");
	int plain[msgsize];
	int mul=mulInverse(a,26);
	for(i=0;i<msgsize;i++){
            int reg=(icipher[i]-b);
            if(reg<0){
               reg=26+reg;
            }

			plain[i]=(reg*mul)%26;
	}
	for(i=0;i<msgsize;i++){
			printf("%c",plain[i]+64);
	}
	puts("\n");
	getchar();
	return 0;
}

//finds multiplication inverse w under modulo m
int mulInverse(int w, int m)
{
    w = w%m;
    int x;
    for (x=1; x<m; x++){
       if ((w*x) % m == 1){
          return x;
       }
    }
}

int gcd(int a, int b)
{
    int r;
    /* Check For Proper Input */
    if(b == 0)
        return a;
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

void cleanup(char *input){
    int i;
	for(i=0;i<sizeof(input);i++){
		if(input[i]<65 || input[i]>90){
			input[i]='\0';
		}
	}
}

