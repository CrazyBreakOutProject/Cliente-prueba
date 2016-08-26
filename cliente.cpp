/* 
 * File:   cliente.cpp
 * Author: ellioth
 * 
 * Created on March 22, 2016, 1:51 PM
 */


#include "cliente.h"

cliente::cliente(int port , const char* ip) {
    connectToServer(port,ip);
}

cliente::~cliente() {
    
}

/**
 * metodo que lo usan los hilos para crear la conexion entre los servidores
 * que estan conectados.
 * @param pNumbThread recibe un dato tipo int, que es el numero del hilo 
 * que estamos usando.
 * @return no retorna nada, solo se usa para la instancia del thread.
 */
void* cliente::connectToServer(int port, const char* ip) {
    _sockfd= socket(AF_INET, SOCK_STREAM, CERO);
    if (_sockfd < CERO) 
        error(ERROR1);
    _server = gethostbyname(ip);
    if (_server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(CERO);
    }
    bzero((char *) &_serv_addr, sizeof(_serv_addr));
    _serv_addr.sin_family = AF_INET;
    bcopy((char *)_server->h_addr, 
        (char *)&_serv_addr.sin_addr.s_addr,
        _server->h_length);
    _serv_addr.sin_port = htons(port);
    if (connect(_sockfd,(struct sockaddr *) &_serv_addr,sizeof(_serv_addr))<
            CERO) 
        error(ERROR4);
    //writeOnServer(0);
}

void* cliente::writeOnServer() {
    cout<<"ingrese su mensaje \n";
    string data;
    cin>>data;
    char datoToServer[data.length()+UNO];
    strcpy(datoToServer,data.c_str());
    datoToServer[data.length()]='\0';
    _n=send(_sockfd,datoToServer,data.length(),0);
    if(_n<CERO)
        error(ERROR4);
    while(true){
        cout<<"ingrese su mensaje \n";
        string data;
        cin>>data;
        char moviment[data.length()+UNO];
        strcpy(moviment,data.c_str());
        moviment[data.length()]='\0';
        _n=send(_sockfd, moviment, data.length(), 0);
        if(_n<CERO)
            error(ERROR4);
    }
}

void* cliente::readOnServer() {
    void * dato= malloc(90);
    cout<<"ingrese su mensaje \n";
    string dataFromConsole;
    cin>>dataFromConsole;
    char datoToServer[dataFromConsole.length()+UNO];
    strcpy(datoToServer,dataFromConsole.c_str());
    datoToServer[dataFromConsole.length()]='\0';
    _n=send(_sockfd,datoToServer,dataFromConsole.length(),0);
    if(_n<CERO)
        error(ERROR4);
    while(true){
        bzero(dato,89);
        _n=recv(_sockfd,dato,89,0);
        if(_n<CERO)
            error(ERROR6);
        cout<<(char*)dato<<endl;
        
    }
}

/**
 * metodo para botar todo el programa si existe algun fallo y 
 * evitar errores futuros.
 * @param msg dato char* que es el mensaje que corresponde a error 
 * probocado.
 */
void cliente::error(const char* msg) {
    perror(msg);
    exit(UNO);
}