#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINEA 100

void mostrar_mensaje(const char *mensaje,enum tipo_accion accion,void *aux)
{
	printf("🤍%s🤍\n",mensaje);
}
void imprimir_terreno(sala_t *sala)
{
	printf("\n");
	printf("✨ʙɪᴇɴᴠᴇɴɪᴅᴏꜱ ᴀ ʟᴀ ꜱᴀʟᴀ ᴅᴇ ᴇꜱᴄᴀᴘᴇ ᴘᴏᴋᴇᴍᴏɴ✨\n");
	printf("🐣ᴘᴇᴅɪ ᴀʏᴜᴅᴀ ᴘᴀʀᴀ ᴠᴇʀ ʟᴏꜱ ᴄᴏᴍᴀɴᴅᴏꜱ Qᴜᴇ ᴘᴏᴅᴇꜱ ʜᴀᴄᴇʀ:🐣\n");
	int cantidad_conocidos = 0;
	char **nombres_conocidos = sala_obtener_nombre_objetos_conocidos(sala, &cantidad_conocidos);
	printf("🌷🌷🌷𝐎𝐛𝐣𝐞𝐭𝐨𝐬 𝐂𝐨𝐧𝐨𝐜𝐢𝐝𝐨𝐬🌷🌷🌷:\n");
	for(int i= 0 ; i<cantidad_conocidos ; i++){
		printf("%s---",nombres_conocidos[i]);
	}
	printf("\n");
	printf("🌷🌷🌷🌷🌷🌷🌷🌷🌷🌷🌷🌷🌷🌷🌷🌷🌷🌷🌷🌷🌷🌷🌷🌷\n");
	printf("\n");
	printf("\n");
	printf("🐇🐇🐇𝐎𝐛𝐣𝐞𝐭𝐨𝐬 𝐏𝐨𝐬𝐞𝐢𝐝𝐨𝐬🐇🐇🐇:\n" );
	int cantidad_poseidos = 0;
	char **nombres_poseidos = sala_obtener_nombre_objetos_poseidos(sala, &cantidad_poseidos);
	if(cantidad_poseidos == 0){
		printf("🤍Aun no posees nada QWQ🤍\n");
	}else{
		for(int i= 0 ; i<cantidad_poseidos ; i++)
			printf("%s---",nombres_poseidos[i]);
	}
	printf("\n");
	printf("🐇🐇🐇🐇🐇🐇🐇🐇🐇🐇🐇🐇🐇🐇🐇🐇🐇🐇🐇🐇🐇🐇🐇🐇\n" );
	printf("\n");
	printf("\n");
	
	free(nombres_conocidos);
	free(nombres_poseidos);

}
void realizar_jugada(sala_t *sala , bool *escape_exitoso)
{
	char comando[MAX_LINEA];
	char *verbo;
	char *objeto1;
	char *objeto2;
	printf("🌈Escribi en el siguiente formato para poder interactuar en la sala :3 :\n");
    printf("🌈<verbo>  <objeto>     <objeto_parametro> \n");
    printf("🌈Por ejemplo: \n");
    printf("🌈romper   puerta  hacha \n");
    printf("🌈O tambien, si no necesitas objeto parametro directamento no escribis nada en <objeto_parametro>: \n");
	printf("🌈quemar   habitacion  \n");
    printf("🌈tambien podes pedir ayuda para ver que mas interacciones hay ;D suertee: \n");
    fgets(comando , 150 , stdin);
	int contador_espacio = 0;
	for(int i = 0 ; i<strlen(comando) ; i++){
		if(comando[i] == ' '){
			contador_espacio++;
		}
	}
	if(contador_espacio == 0){
		if(strcmp(comando,"ayuda\n")==0 ){
			printf("\n");
			printf("\n");
			printf("\n");
			printf("\n");

			printf("🏁𝐚𝐠𝐚𝐫𝐫𝐚𝐫<𝐨𝐛𝐣𝐞𝐭𝐨>--------𝑰𝒏𝒕𝒆𝒏𝒕𝒂 𝒂𝒈𝒂𝒓𝒓𝒂𝒓 𝒖𝒏 𝒐𝒃𝒋𝒆𝒕𝒐\n");
			printf("🏁𝐝𝐞𝐬𝐜𝐫𝐢𝐛𝐢𝐫<𝐨𝐛𝐣𝐞𝐭𝐨>------𝑪𝒐𝒎𝒐 𝒅𝒊𝒄𝒆, 𝒅𝒆𝒔𝒄𝒓𝒊𝒃𝒐 𝒖𝒏 𝒐𝒃𝒋𝒆𝒕𝒐,𝒅𝒂𝒂𝒉\n");
			printf("🏁𝐬𝐚𝐥𝐢𝐫------------------𝑵𝒐 𝒒𝒖𝒆𝒓𝒆𝒔 𝒋𝒖𝒈𝒂𝒓 𝒎𝒂𝒔 𝒚 𝒔𝒂𝒍𝒊𝒔 𝒅𝒆𝒍 𝒋𝒖𝒆𝒈𝒐 :c\n");
			printf("\n");
		}
		else if( strcmp(comando,"salir\n")==0 ){
			(*escape_exitoso) = true;
		}else{
			printf("🤍QWQ no se que quieres decir🤍\n");
			printf("\n");
			printf("\n");
		}
	}else if(contador_espacio == 1){
		verbo = strtok(comando , " ");
		objeto1 = strtok(NULL , "\n");
		if(strcmp(verbo,"describir")==0){
			char *descripcion_objeto = sala_describir_objeto(sala, objeto1);
			if(descripcion_objeto){
				printf("🤍%s🤍\n",descripcion_objeto);
				printf("\n");
				printf("\n");
			}else{
				printf("🤍De que estas diciendo? OWO no lo conozco eee🤍\n");
				printf("\n");
				printf("\n");
			}
		}else if(strcmp(verbo,"agarrar")==0){
			if(sala_agarrar_objeto(sala, objeto1)){
				printf("🤍Nuevo item adquirido:%s! >W<🤍\n", objeto1);
				printf("\n");
				printf("\n");
			}else{
				printf("🤍oops, no se como agarrar esto QWQ🤍\n");
				printf("\n");
				printf("\n");
			}
		}else if(sala_es_interaccion_valida(sala, verbo, objeto1,"")){
			sala_ejecutar_interaccion(sala, verbo,objeto1, "",mostrar_mensaje,NULL);
			printf("\n");
			printf("\n");
		}else{
			printf("🤍QWQ no se que quieres decir🤍\n");
			printf("\n");
			printf("\n");
		}
	}else if(contador_espacio == 2){
		verbo = strtok(comando , " ");
		objeto1 = strtok(NULL , " ");
		objeto2 = strtok(NULL , "\n");
		if(sala_es_interaccion_valida(sala, verbo, objeto1,objeto2)){
			sala_ejecutar_interaccion(sala, verbo,objeto1, objeto2,mostrar_mensaje,NULL);
			printf("\n");
			printf("\n");
		}else{
			printf("🤍QWQ no se que quieres decir🤍\n");
			printf("\n");
			printf("\n");
		}
	}
	imprimir_terreno(sala);
}

int main(int argc, char *argv[])
{
	//Los archivos deben venir como parámetros del main
	
	sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);

	if (!sala) {
		printf("Error al crear la sala de escape\n");
		return -1;
	}
	
	bool escape_exitoso = false;

	imprimir_terreno(sala);
	
	while(!sala_escape_exitoso(sala) && !escape_exitoso){
		realizar_jugada(sala , &escape_exitoso);
	}
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	if(sala_escape_exitoso(sala)){
		printf("💛💛💛GANASTE!Yuupi! ^W^ are u genius??💛💛💛 \n");

	}else{
		printf("😔😔😔Oh no,,, te fuiste?? lemme give u a hug❤️‍🩹❤️‍🩹❤️‍🩹 \n");
	}
	printf("\n");
	printf("\n");
	sala_destruir(sala);

	return 0;
}
