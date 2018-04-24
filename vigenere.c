#include <stdio.h>


int main(){
	int i;
	printf("Use only Characters... \n");
	printf("Enter Message: \n");
	char msg[40];//maximum capacity
	scanf("%40s",msg);
	char key[sizeof(msg)];//maximum capacity
	char cipher[sizeof(msg)];


	printf("Enter Key: \n");
	scanf("%40s",key);


	//capitalizing
	i=0;
	while(msg[i]!='\0'){
		if(msg[i]>=97 && msg[i]<=122){
				msg[i]-=32;
		}
		i++;
	}
	int msgsize=i;


	//capitalizing key
	i=0;
	while(key[i]!='\0'){
		if(key[i]>=97 && key[i]<=122){
				key[i]-=32;
		}
		i++;
	}
	int keysize=i;

	//making sure that keysize<=msgsize
	if(keysize>msgsize){
		//for(i=msgsize;i<40;i++)s
			key[msgsize]='\0';
		
		//keysize=msgsize;
	}

	//converting msg and key to integers
	int imsg[40],ikey[40];

	for(i=0;i<msgsize;i++){
		imsg[i]=msg[i]-65; //A=0 ASCII
	}
	for(i=0;i<keysize;i++){
		ikey[i]=key[i]-65; //Α=0 ASCII
	}



	//repeating the key so it fits the msg
	if(keysize<msgsize){
		for(i=0;i<msgsize-keysize;i++){
			ikey[keysize+i]=ikey[i];
			key[keysize+i]=ikey[i]+65;
		}
		//keysize=msgsize;
	}

	//Encryption
	for(i=0;i<msgsize;i++){
			cipher[i]=ikey[i]+imsg[i]+65;
			if(cipher[i]>90){
				cipher[i]=(cipher[i]%90)+65;
			}
	}

	//cleanup cipher
	for(i=0;i<sizeof(cipher);i++){
		if(cipher[i]<65 || cipher[i]>90){
			cipher[i]='\0';
		}
	}

	//key cleanup
	for(i=0;i<sizeof(key);i++){
		if(key[i]<65 || key[i]>90){
			key[i]='\0';
		}
	}

	puts("\nInitial Message: ");
	printf("%s\n\n",msg);

	puts("Key: ");
	printf("%s\n\n",key);

	puts("Encrypted Message:");
	printf("%s\n\n",cipher);

    getchar();
	return 0;


}
