#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

void cleanup(char *str);
void count(); 
void paths(); 
int iseven(int d);
int autoc(int d);

void convert(); // {0,1} -> {-1,1}
float polwsh();// χ^2= (ν1-ν0)^2/ν
float m(int d);


int n0=0,n1=0;
char *input; 
int conv[]={}; // {-1,1}

#define SIZEOF(X) (sizeof(X)/sizeof((X)[0])) 

int main(int argc, char *argv[]) {

	
    if (argc < 1)
        return 0;

    int i;
    int strsize = 0;
    for (i=1; i<argc; i++) {
        strsize += strlen(argv[i]);
        if (argc > i+1)
            strsize++;
    }

    input = malloc(strsize);
    input[0] = '\0';

    for (i=1; i<argc; i++) {
        strcat(input, argv[i]);
        if (argc > i+1)
            strcat(input, " ");
    }
    //--------


  
    cleanup(input);
    printf("Input: %s\n", input);

   
	count();
	printf("Frequency difference: %d Polwsh (closer to 0 is better): %lf\n",abs(n0-n1),polwsh());


    
    paths();

	
	convert();
	puts("");


    printf("Autocorrelation A(0)=%d m=%f \n",autoc(0),m(0));
    printf("Autocorrelation A(1)=%d m=%f \n",autoc(1),m(1));
    printf("Autocorrelation A(2)=%d m=%f \n",autoc(2),m(2));

	free(input);
    return 0;
}

void cleanup(char *str) {
	//ASCII 0=48 1=49
    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst == '0' | *dst == '1' ) dst++;
    }
    *dst = '\0';
}

void count(){
	char *test;
	for(test=input;*test!='\0';test++){
		if(*test=='0') n0++;
		if(*test=='1') n1++;
	}
}

void paths(){
	char *test;
	int paths[strlen(input)];
	int strsize=strlen(input);
	int i=0;
	int counter=0;
	for(test=input;*test!='\0';test++){
		while(*test==*(test+1)){
			test++;
			counter++;
		}
		paths[i]=counter;
		counter=0;
		i++;
	}
	int numpaths=i;
	int longestpath=0;
	printf("Paths: ");
	for(i=0;i<numpaths;i++){
		paths[i]++;//they were initialized with zero
		//finding the max of paths[] (longestpath)
		if(paths[i]>longestpath){
			longestpath=paths[i];
		}
		printf("%d ",paths[i]);
	}
	puts("");

	//printing input size
	if(!iseven(strsize)){
		strsize--;
	}
	printf("Input Size: %d (even)\n ",strsize);
	puts("");

	//--------------
	//initializing pathsoflength array
	int pathsoflength[longestpath+1];
	for(i=1;i<longestpath+1;i++){
		pathsoflength[i]=0;
	}
	//building pathsoflength array
	for(i=0;i<numpaths;i++){
		pathsoflength[paths[i]]++;
	}

	//printing stats
	for(i=1;i<longestpath+1;i++){
		if(pathsoflength[i]!=0){
			printf("\t\t%d path(s)\thave length: %d \n",pathsoflength[i],i);
		}
	}
	puts("");
	int j;
	for(i=2,j=1;i<numpaths && j<SIZEOF(pathsoflength);i=2*i,j++){
		printf("(1/%d of %d) \t%d paths, should have length: %d. (Stats: %d difference)\n",i,strsize,strsize/i,j,abs(pathsoflength[j]-(strsize/i)));
	}

}

int iseven(int d){
	if(d%2==0)
		return 1;
	else
		return 0;

}


int autoc(int d){
    //https://en.wikipedia.org/wiki/Autocorrelation
	int buffer=0;
	int n=n0+n1;
	
	int j;
	for(j=0;j<n-d;j++){
		buffer+=(conv[j])*(conv[j+d]);
	}
	return buffer;
}

float m(int d){
	int n=n0+n1;
	float m;
	m=(pow(n1,2)*(n-d))/pow(n,2);
	return m;
}


void convert(){//works
	char *test;
	int i=0;
	for(test=input;*test!='\0';test++,i++){
		if(*test=='1'){
			conv[i]=1;
        }
		else{
			conv[i]=-1;
		}
	}
}

float polwsh(){
	int n=n0+n1;
	return pow(n0-n1,2)/n;// ^ == bit XOR
}




