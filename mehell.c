#include <stdio.h>
#include <stdlib.h>

int b[]={1,2,4,9,20,38}; //(private key)
int B[6][3]; //its b but sorted like a
             //first column private key values, second column order, third column knapsack (0 or 1)
int a[6][2];//={3,5,1,9,0,60};//(public key)
			//a[i][0] value of public key | a[i][1] index before sorting
int m=105; //bigger than the sum
int w=31; //gcd(w,m)=1
int p[]={0,0,1,1,0,0, 1,1,0,1,0,0, 1,1,1,0,1,0}; //18 values
int C[3];	//SIZEOF(p)/SIZEOF(a) 3
int P[3];//SIZEOF(c) 3

#define SIZEOF(X) (sizeof(X)/sizeof((X)[0]))

void printPlainText(){
printf("Our Plain text is: \n");
int i;
for(i=0;i<SIZEOF(p);i++){
    printf("%d",p[i]);
}
puts("\n");
}

void printPrivateKey(){
printf("Our Private Key is: \n");
int i;
for(i=0;i<SIZEOF(b);i++){
    printf("%d ",b[i]);
}
puts("\n");
}
//finds multiplication inverse w under modulo m
//output 61
int mulInverse(int w, int m){
    w = w%m;
    int x;
    for (x=1; x<m; x++){
       if ((w*x) % m == 1){
          printf("\n\nMul. Inverse of (%d mod %d) is %d\n\n",w,m,x);
          return x;
       }
    }
}
//prints out B array (Private Key, order , plaintext)
void printB(){
     printf("Pr.Key  | order | Plain\n");
     printf("------------------------\n");
     int i;
     for(i=0;i<SIZEOF(B);i++){
        printf("%d \t| %d \t| %d\n",B[i][0],B[i][1],B[i][2]);
     }
     puts("");

}
//sorts A array (public key)
void bubbleSortA(){
   int temp,temp2;
   int i,j;

   int MAX=SIZEOF(a);
   for(i = 0; i < MAX-1; i++) {
      for(j = 0; j < MAX-1-i; j++) {
         if(a[j][0] > a[j+1][0]) {
            temp = a[j][0];
            temp2= a[j][1];

            a[j][0] = a[j+1][0];
            a[j][1] = a[j+1][1];

            a[j+1][0] = temp;
            a[j+1][1] = temp2;
         }
      }
   }
}
//sorts B array (private Key)
void bubbleSortB() {// B is 1 2 4 9 20 38
   int temp,temp2,temp3;
   int i,j;

   int MAX=SIZEOF(B);
   for(i = 0; i < MAX-1; i++) {
      for(j = 0; j < MAX-1-i; j++) {
         if(B[j][0] > B[j+1][0]) {
            temp = B[j][0];
            temp3= B[j][2];

            B[j][0] = B[j+1][0];
            B[j][2] = B[j+1][2];

            B[j+1][0] = temp;
            B[j+1][2] = temp3;
         }
      }
   }
}
//calculates Public key using our private key , w and m
void calcPublic(){
	int Size=SIZEOF(b);
	int i;
	printf("...Calculating Public Key...\n");
	for(i=0;i<Size;i++){
		a[i][0]=(b[i]*w)%m;
        printf("%d =(%d * %d)mod% d\n",a[i][0],b[i],w,m);
		a[i][1]=i;
	}
	puts("\n");

	bubbleSortA();
}
void printPublicKey(){
printf("Our Public Key is: \n");
int i;
for(i=0;i<SIZEOF(a);i++){
    printf("%d ",a[i][0]);
}
puts("\n");
}
//input p , a[][]
//we encrypt using our public key a[][]
//the output is C[]
void encrypt(){
	//i runs p (plain text)
	//j runs a (public key)
	//k runs c (cipher text)
	printf("...Encrypting...\n");
	int i,j,k,sum;
	for(i=0,j=0,k=0,sum=0;i<SIZEOF(p)+1;i++,j++){
		if(i%(SIZEOF(a))==0 && i!=0){ //break the plain text in 3 parts of length 6
			j=0;
			printf("= %d\n",sum);
			C[k]=sum;
			sum=0;
			k++;
		}
		sum+=((int)a[j][0])*((int)p[i]);

		if(i<(SIZEOF(p)-1)){
		printf("(%d * %d) + \n",a[j][0],p[i]);
        }
	}
	puts("\n");
}
//input C[]
//output P[] goes to knapsack
void decrypt(){
  int I=mulInverse(w,m); //61
  int Size=SIZEOF(C); // 3
  printf("...Decrypting...\n");
  int i;
  for(i=0;i<Size;i++){
	  P[i]=(C[i]*I)%m;
	  printf("%d = (%d * %d)mod%d\n",P[i],C[i],I,m);
  }
  puts("\n");
}
//creates our (our public key)
//output B[][0] is 4 38 1 2 9 20
void createB(){
	int j,i;
	for(i=0;i<SIZEOF(b);i++){
        //B[][0] private  key value
        //a[][1] public key index
        //b[] private key value
		B[i][0]=b[a[i][1]];

		//B[][1]private key index
		//a[][1]public key index
		//0 initial knapsack value
		B[i][1]=a[i][1];

		//B[][2]private key knapsack
		//initializing
        B[i][2]=0;
	}
}
//orders B from B[i][1]
void recoverState(){

    int knap[SIZEOF(B)];
    int j,i;
    for(i=0;i<SIZEOF(b);i++){
        knap[i]=B[i][2];
    }
	for(i=0;i<SIZEOF(b);i++){
        //B[][0] private  key value
        //B[][1] index
        //B[][2] knapsack switch
        //b[] private key value
        B[i][0]=b[B[i][1]];
        B[i][2]=knap[B[i][1]];
	}
}
//Knapsack(P[i])
void Knapsack(int S){
    // S must be bigger than the max value of b but not bigger than 2*Max
	//b private key
	//a public key
    //the B array is our private key sorted like a
	createB();
    bubbleSortB();

	printf("Knapsack(%d)\n",S);


	//we print out our private key
	int i;
	for(i=SIZEOF(B)-1;i>=0;i--){
         if(i>0){
            printf("%d , ",B[i][0]);
         }else if(i==0){
            printf("%d \n",B[i][0]);
         }
	}
	//knapsack algorithm
	for(i=SIZEOF(B)-1;i>=0;i--){
		if(S>=B[i][0]){
          printf("%d-%d=%d       \t%d\n",S,B[i][0],S-B[i][0],B[i][0]);
          S=S-B[i][0];
          B[i][2]=1;
		}
	}
	puts("");
    recoverState();
	printB();

}



int main(){

printPlainText();
printPrivateKey();

calcPublic();
printPublicKey();

encrypt();
decrypt();

int i;
for(i=0;i<SIZEOF(P);i++){
Knapsack(P[i]);
}
getchar();
return 0;
}
