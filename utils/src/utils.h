#ifndef utils.h
#define utils.h


#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <commons/log.h>
#include <netdb.h>
#include <unistd.h>

void saludar(char* quien);
t_log* iniciar_logger(char* nombrelog, char* nombre);
int IniciarServidor(int puerto);
int EsperarConexion(int socket);
int CrearConexion(chr *ip, int puerto, t_log *logger);

#endif