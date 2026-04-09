#include "utils.h"



char* IniciarServidor(char *puerto){

    int err;
    //creo las estructuras para los parametrizar los sockets
    struct addrinfo hints, *serverinfo;

    //seteo la memoria en 0
    memset(&hints, 0, sizeof(hints));

    //le doy los parametros que quiero
    hints.ai_family=AF_INET;
    hints.ai_socktype=SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

    //Busco la info para el socket
    getaddrinfo(NULL, puerto, &hints, &serverinfo);

    //Creo el socket
    char* fd_servidor=socket(serverinfo->ai_family,
                           serverinfo->ai_socktype,
                           serverinfo->ai_protocol);

    //Permito que un socket se pueda conectar al mismo puerto
    setsockopt (fd_servidor, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    //Le asigno un puerto al socket
    if ((err = bind(fd_servidor, serverinfo->ai_addr, serverinfo->ai_addrlen)) ==-1){

        freeaddrinfo(serverinfo);
        return -1;
    }
    if ((err= listen (fd_servidor, SOMAXCONN)) == -1){

        freeaddrinfo(serverinfo);
        return -1;
    }


    freeaddrinfo(serverinfo);
    return fd_servidor;
}

char* EsperarConexion(char *fd_servidor){
   char *fd_cliente;
    fd_cliente = accept(fd_servidor, NULL, NULL);
    if(fd_cliente==-1){
        return -1;
    }
    return fd_cliente;
}

char* CrearConexion(char *ip, char *puerto){

    //creo las estructuras para los parametrizar los sockets
    struct addrinfo hints, *serverinfo;

    //seteo la memoria en 0
    memset(&hints, 0, sizeof(hints));

    //le doy los parametros que quiero
    hints.ai_family=AF_INET;
    hints.ai_socktype=SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

    //Busco la info para el socket, distinto que el server
    getaddrinfo(ip, puerto, &hints, &serverinfo);

    //Creo el socket
    char* fd_cliente =socket(serverinfo->ai_family,
                           serverinfo->ai_socktype,
                           serverinfo->ai_protocol);

    if(connect(fd_cliente, serverinfo->ai_addr, serverinfo->ai_addrlen)==-1){
        freeaddrinfo(serverinfo);
        close(fd_cliente);
        return -1;
    }

    freeaddrinfo(serverinfo);
    return fd_cliente;
}




void saludar(char *quien) {
    printf("Hola desde %s!!\n", quien);
}