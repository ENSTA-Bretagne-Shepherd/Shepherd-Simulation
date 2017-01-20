#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


/*
Compilation sans librairie
lancer d'abord le serveur puis le client dans 
deux terminals différents avec les commandes:
./server 51717
./client localhost 51717

(si les executables s'appellent client et server
*/

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    int tour=0;	
    char buffer[256];
    
    while(1){
	// initialisation
    	if (argc < 3) {
       		fprintf(stderr,"usage %s hostname port\n", argv[0]);
       		exit(0);
    		}
    	portno = atoi(argv[2]);
    	sockfd = socket(AF_INET, SOCK_STREAM, 0);
    	if (sockfd < 0) 
        	error("ERROR opening socket");
    	server = gethostbyname(argv[1]);
    	if (server == NULL) {
        	fprintf(stderr,"ERROR, no such host\n");
        	exit(0);
    	}
    	bzero((char *) &serv_addr, sizeof(serv_addr));
    	serv_addr.sin_family = AF_INET;
    	bcopy((char *)server->h_addr, 
         	(char *)&serv_addr.sin_addr.s_addr,
         	server->h_length);
    	serv_addr.sin_port = htons(portno);
    	if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        	error("ERROR connecting");
   
    	tour++;
    	
    	
    	//printf("Please enter the message: ");
    	//usleep(20000);// cadencé à 50Hz
    	bzero(buffer,256);
    	sprintf(buffer,"demande des coordonnées %d",tour);
    	//fgets(buffer,255,stdin);
    	n = write(sockfd,buffer,strlen(buffer));
    	if (n < 0) 
         	error("ERROR writing to socket");
    	bzero(buffer,256);
    	n = read(sockfd,buffer,255);
    	if (n < 0) 
         	error("ERROR reading from socket");
        int i;
        for(i=0; i<n; i++){
        	if(i%32 == 0)printf("\n");        	
    		if(i%4 == 0)printf(" ");
    		printf("%02x",(unsigned char)buffer[i]);
    		
    	}    	
    	printf("  fin message");
    	close(sockfd);
    }
    
    
    return 0;
}
