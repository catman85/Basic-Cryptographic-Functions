#include <stdio.h>


int main(){
	int i;

	printf("Enter Message: \n");
	char msg[40];//maximum capacity
	scanf("%40s",msg);
	char key[sizeof(msg)];//maximum capacity
	char cipher[sizeof(msg)];


	printf("Enter Key: \n");
	scanf("%40s",key);


	//κάνουμε το msg κεφαλαία
	i=0;
	while(msg[i]!='\0'){
		if(msg[i]>=97 && msg[i]<=122){
				msg[i]-=32;
		}
		i++;
	}
	int msgsize=i;


	//κάνουμε το key κεφαλαία
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
			key[msgsize]='\0';//χαρακτήρας τερματισμού
		//
		//keysize=msgsize;
	}

	//Μετατροπή μυνήματος και κλειδιού σε αριθμούς
	int imsg[40],ikey[40];

	for(i=0;i<msgsize;i++){
		imsg[i]=msg[i]-65; //A=0 ASCII
	}
	for(i=0;i<keysize;i++){
		ikey[i]=key[i]-65; //Α=0 ASCII
	}



	//επανάληψη του key ώστε να ταιριάζειμε το msg
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

			//οι χαρακτήρες που μας
			//ενδιαφέρουν απο 65 μέχρι 90
			if(cipher[i]>90){
				cipher[i]=(cipher[i]%90)+65;
			}
	}

	//καθαρισμός του cipher
	for(i=0;i<sizeof(cipher);i++){
		if(cipher[i]<65 || cipher[i]>90){
			cipher[i]='\0';
		}
	}

	//καθαρισμός του κλειδιού
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
	printf("%s",cipher);

    getchar();
	return 0;


}
