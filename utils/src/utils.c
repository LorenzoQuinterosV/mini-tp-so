#include "utils.h"

t_log* iniciar_logger(char* nombrelog, char* nombre) {
    return log_create(archivo, nombre, true, LOG_LEVEL_INFO);
}

int IniciarServidor(int puerto, t_log* logger){

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
    int fd_servidor=socket(serverinfo->ai_family,
                           serverinfo->ai_socktype,
                           serverinfo->ai_protocol);

    //Permito que un socket se pueda conectar al mismo puerto
    setsockopt (fd_servidor, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));
    //Le asigno un puerto al socket
    if (err = bind(fd_servidor, serverinfo->ai_addr, serverinfo->ai_addrlen) ==-1){
        log_trace(logger, "fallo el bind");
        freeaddrinfo(server_info);
        return -1;
    }
    if (err= listen (fd_servidor, SOMAXCONN) == -1){
        log_trace(logger, "fallo el listen");
        freeaddrinfo(server_info);
        return -1;
    }


    freeaddrinfo(server_info);
    log_trace(logger, "Listo para la escucha del cliente");
    return fd_servidor;
}

int EsperarConexion(int fd_servidor, t_log *logger){
   int fd_cliente;
    fd_cliente = accept(fd_servidor, NULL, NULL);
    if(fd_cliente==-1){
        log_trace(logger, "error al aceptar la conexion");
        return -1;
    }
    log_trace(logger, "La conexion sucedio con exito");
    return fd_cliente;
}

int CrearConexion(chr *ip, int puerto, t_log *logger){

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
    int fd_cliente =socket(serverinfo->ai_family,
                           serverinfo->ai_socktype,
                           serverinfo->ai_protocol);

    if(connect(fd_cliente, serverinfo->ai_addr, serverinfo->ai_addrlen)==-1){
        log_trace(logger, "La conexion fallo...");
        freeaddrinfo(serverinfo);
        close(fd_cliente);
        return -1;
    }

    freeaddrinfo(serverinfo);
    return fd_cliente;
}




void saludar(char* quien) {
    printf("Hola desde %s!!\n", quien);
}