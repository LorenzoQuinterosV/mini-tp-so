#include "cpu.h"

t_config* config;
t_log* logger;
char* ip;
char* puerto;
t_log_level log_level;
char* fd_kernel;


int main(int argc, char* argv[]) {
    saludar("cpu");
    ObtenerConfig();
    logger = log_create("cpu.log", "CPU", true, log_level);
    fd_kernel = CrearConexion(ip, puerto, logger);

    return 0;
}

void ObtenerConfig(){
    config = config_create("cpu.config");
    ip = config_get_string_value(config, "IP_KERNEL");
    puerto = config_get_string_value(config, "PUERTO_KERNEL");
    log_level = log_level_from_string (config_get_string_value(config, "LOG_LEVEL");
}