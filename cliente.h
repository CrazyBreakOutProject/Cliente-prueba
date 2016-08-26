/* 
 * File:   cliente.h
 * Author: ellioth
 *
 * Created on March 22, 2016, 1:51 PM
 */

#ifndef CLIENTE_H
#define	CLIENTE_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pthread.h>
#include <iostream>
#include <fstream>
#include "Constantes.h"

using namespace std;
class cliente : public Constantes{
public:
    cliente(int port, const char* ip);
    virtual ~cliente();
    void* writeOnServer();
    void* readOnServer();
private:
    int _sockfd,_n;
    struct sockaddr_in _serv_addr;
    struct hostent * _server;
    void * connectToServer(int port, const char* ip);
    void error(const char* msg);
    
};

#endif	/* CLIENTE_H */

