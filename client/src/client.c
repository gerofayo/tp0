#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* clave;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	ip 		= config_get_string_value(config,"IP");
	puerto 	= config_get_string_value(config,"PUERTO");
	clave	= config_get_string_value(config,"CLAVE");

	log_info(logger, ip);
	log_info(logger, puerto);
	log_info(logger, clave);

	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);
	
	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(clave, conexion);
	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;

	nuevo_logger = log_create("tpo.log", "logger", true, LOG_LEVEL_INFO);

	if(!nuevo_logger)
	{
		perror("No se pudo crear el logger.\n");
		abort();
	}

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;

	nuevo_config = config_create("cliente.config");

	if(!nuevo_config)
	{
		perror("No se pudo crear el config.\n");
		abort();
	}

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	//char* leido;

	//leido = readline("> ");

}

void paquete(int conexion)
{
	char* leido;
	t_paquete* paquete;
	bool stringIsNotEmpty;

	paquete = crear_paquete();

	printf("Agergar al paquete: \n");
	do{
		leido = readline("#");
		stringIsNotEmpty = strcmp(leido,"") != 0;
		
		if(stringIsNotEmpty)
		{
			agregar_a_paquete(paquete, leido, strlen(leido)+1);
		}

		free(leido);
	}while(stringIsNotEmpty);

	enviar_paquete(paquete, conexion);

	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}
