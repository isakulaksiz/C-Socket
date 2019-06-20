#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include <unistd.h>

#define uzunluk 100
int main(){
	int soket,yeni_soket,c_uzunlugu,n,sayac=1;
	struct sockaddr_in serverAdress;
	struct sockaddr_in clientAdress;
	char mesaj[uzunluk];

	soket=socket(AF_INET,SOCK_STREAM,0);
	
	serverAdress.sin_family=AF_INET;
	serverAdress.sin_port=htons(9999);
	serverAdress.sin_addr.s_addr=INADDR_ANY;

	if(bind(soket,(struct sockaddr *)&serverAdress,sizeof(serverAdress))<0){
		printf("Not Created Socket !!!!n");
		exit(1);
	}
	else
		printf("Created Socket.\n");

	listen(soket,10);
	printf("Listening...\n");

	while (1){
		c_uzunlugu=sizeof(clientAdress);
		yeni_soket=accept(soket,(struct sockaddr *)&clientAdress,&c_uzunlugu);

		if(yeni_soket>0){
				printf("%d.Created Connection.\n",sayac);
				sayac++; }	
				 
		else
				printf("Not Created Connection!!!!\n");

		if(!fork()){
			while(1){
				recv(yeni_soket,mesaj,uzunluk,0);	
				n=strlen(mesaj)+1;
				printf("\n the text from client: %s",mesaj);
				printf("write text to client : %s",mesaj);
				send(yeni_soket,mesaj,n,0);
				}	
			exit(1);
			}
		else{
		close(yeni_soket);
		}
	}
	return 0;}

