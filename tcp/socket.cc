#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h> 
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

#include "tcp/socket.h"
#include "exceptions/socket_exception.h"


Socket::Socket(int domain, int protocol, int port)
    : _domain{domain}, _protocol{protocol}, _port{port}
{
    _socketfd = socket(_domain, SOCK_STREAM, _protocol);
    if (_socketfd < 0)
        throw SocketInitException();

    memset(&_serv_addr, 0, sizeof(_serv_addr));
    _serv_addr.sin_family = _domain;
    _serv_addr.sin_addr.s_addr = INADDR_ANY;
    _serv_addr.sin_port = htons(_port);

    int bind_status = bind(_socketfd, (struct sockaddr *)&_serv_addr, sizeof(_serv_addr));
    if (bind_status < 0)
        throw SocketBindException();

    listen(_socketfd, _listen_backlog_queue);
    std::cout << "waiting for a client to connect........" << std::endl;
}

void Socket::handleMsg()
{
    struct sockaddr_in cli_addr;
    socklen_t cli_addr_size = sizeof(cli_addr);
    char indata[1024] = {0}, outdata[1024] = {0};
    while (1)
    {
        int newsockfd = accept(_socketfd, (struct sockaddr *)&cli_addr, &cli_addr_size);
        if (newsockfd < 0)
            throw SocketAcceptException();
        
        std::cout << "Connect with client from: " << inet_ntoa(cli_addr.sin_addr) << 
            " port: " << ntohs(cli_addr.sin_port) << std::endl;
        
        while (1)
        {
            int nbytes = recv(newsockfd, indata, sizeof(indata), 0);
            if (nbytes <= 0) {
                close(newsockfd);
                printf("client closed connection.\n");
                break;
            }
            printf("recv: %s\n", indata);

            sprintf(outdata, "echo %s", indata);
            send(newsockfd, outdata, strlen(outdata), 0);
        }
    }

}

Socket::~Socket()
{
    close(_socketfd);
}