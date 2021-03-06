//
// Created by tag on 03/01/17.
//

#include "networktools.h"

/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>




void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int sockfd=-1, newsockfd=-1, portno;
socklen_t clilen;
char buffer[256];
struct sockaddr_in serv_addr, cli_addr;
int n;
int tour=0;



int init_connection( char *port)
{
    
     
     portno = atoi(port);
	
	 sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
         error("ERROR opening\n");
     int reuse=1;
     if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) < 0)
     	error("setsockopt(SO_REUSEADDR) failed");
     	
     bzero((char *) &serv_addr, sizeof(serv_addr));
     
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
	 if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              	error("ERROR on binding\n");
         
     return 0;
}
         
     
     
     
     
char* wait_connection(char *reponse, int longueur){
     tour++;
     //usleep(20000);
     	
     listen(sockfd,5);
     clilen = sizeof(cli_addr);
     newsockfd = accept(sockfd, 
             (struct sockaddr *) &cli_addr, 
             &clilen);
     if (newsockfd < 0){
         printf("ERROR on accept\n");
         return NULL;
     }
     	
     bzero(buffer,256);
     n = read(newsockfd,buffer,255);
     	
     //printf("Here is the message: %s\n",buffer);
     //sprintf(reponse, "I got your message %d",tour);
     n = write(newsockfd,reponse,longueur);
     
     close(newsockfd);
     
     return buffer;
}
     
void close_connection(){
	close(newsockfd);
    close(sockfd);     
}
