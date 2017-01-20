/*
** server.c -- a stream socket server demo
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <iostream>
#include "serverToBuoys.h"
#include "config.h"


//

void *task1(void *);

static int connFd;

int main(int argc, char* argv[])
{
    int pId, portNo, listenFd;
    socklen_t len; //store size of the address
    bool loop = false;
    struct sockaddr_in svrAdd, clntAdd;

    pthread_t threadA[3];

    if (argc < 2)
    {
        std::cerr << "Syntam : ./server <port>" << std::endl;
        return 0;
    }

    portNo = atoi(argv[1]);

    if((portNo > 65535) || (portNo < 2000))
    {
        std::cerr << "Please enter a port number between 2000 - 65535" << std::endl;
        return 0;
    }

    //create socket
    listenFd = socket(AF_INET, SOCK_STREAM, 0);

    if(listenFd < 0)
    {
        std::cerr << "Cannot open socket" << std::endl;
        return 0;
    }

    bzero((char*) &svrAdd, sizeof(svrAdd));

    svrAdd.sin_family = AF_INET;
    svrAdd.sin_addr.s_addr = INADDR_ANY;
    svrAdd.sin_port = htons(portNo);

    //bind socket
    if(bind(listenFd, (struct sockaddr *)&svrAdd, sizeof(svrAdd)) < 0)
    {
        std::cerr << "Cannot bind" << std::endl;
        return 0;
    }

    listen(listenFd, 5);

    len = sizeof(clntAdd);

    int noThread = 0;

    while (noThread < 3)
    {
        std::cout << "Listening" << std::endl;

        //this is where client connects. svr will hang in this mode until client conn
        connFd = accept(listenFd, (struct sockaddr *)&clntAdd, &len);

        if (connFd < 0)
        {
            std::cerr << "Cannot accept connection" << std::endl;
            return 0;
        }
        else
        {
            std::cout << "Connection successful" << std::endl;
        }

        pthread_create(&threadA[noThread], NULL, task1, NULL);

        noThread++;
    }

    for(int i = 0; i < 3; i++)
    {
        pthread_join(threadA[i], NULL);
    }


}

void *task1 (void *dummyPt)
{
    std::cout << "Thread No: " << pthread_self() << std::endl;
    char test[300];
    bzero(test, 301);
    bool loop = false;
    while(!loop)
    {
        bzero(test, 301);


        read(connFd, test, 300);

        std::string tester (test);
        std::cout << tester << std::endl;


        if(tester == "exit")
            break;
    }
    std::cout << "\nClosing thread and conn" << std::endl;
    close(connFd);
}

