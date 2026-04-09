#include "kernel.h"

char* fd_servidor;
char* puerto_escucha;
t_config* config;
char* fd_cpu;
t_log* logger;
t_log_level log_level;

int main(int argc, char* argv[]) {
    
    saludar("kernel");
    ObtenerConfig();
    fd_servidor = IniciarServidor(puerto_escucha);
    fd_cpu = EsperarConexion(fd_servidor);
    logger = log_create("kernel.log", "KERNEL", true, log_level);
    log_info(logger, "se conecto la cpu");

    return 0;
}

void ObtenerConfig(){
    config = config_create("kernel.config");
    puerto_escucha = config_get_string_value(config, "PUERTO_ESCUCHA");
    log_level = log_level_from_string (config_get_string_value(config, "LOG_LEVEL"));
}