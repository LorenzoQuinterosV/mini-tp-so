
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <commons/log.h>
#include <netdb.h>
#include <unistd.h>
#include <commons/config.h>

void saludar(char *quien);
char* IniciarServidor(char *puerto);
char* EsperarConexion(char *socket);
char* CrearConexion(char *ip, char *puerto);

