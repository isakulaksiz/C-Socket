#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include <arpa/inet.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>

#define ip "127.0.0.1"
#define mesaj_max 200

int main(){
	printf("\n If you want to turn off the client write "!" ");
	int soket,uzunluk;
	soket=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in serverAdress;
	char mesaj1[mesaj_max];
	char mesaj2[mesaj_max];

	serverAdress.sin_family=AF_INET;
	serverAdress.sin_port=htons(9999);
	serverAdress.sin_addr.s_addr=inet_addr(ip);
	
	if(connect(soket,(struct sockaddr *)&serverAdress,sizeof(serverAdress))<0){
		printf("\n connection not created !!!");
		exit(1); }
	else
		printf("\n Connection created.\n");

	while(1){
		
		printf("\n Write the text to sent : "); 
		fgets(mesaj1,mesaj_max,stdin);

		if(mesaj1[0]=='!') break;

		uzunluk=strlen(mesaj1)+1;
		send(soket,mesaj1,uzunluk,0);
		recv(soket,mesaj2,mesaj_max,0);

		printf("The text from Server : %s",mesaj2);

	}
	return 0;
}

