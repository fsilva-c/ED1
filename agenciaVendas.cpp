#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//a estrutura de clientes ira apontar para a estrutura paises
//lista deve ser criada previamente, em tempo de compilação 

typedef struct listaPaises{
	char nome[30];
	int cod;
	struct listaPaises *next;
	struct listaClientes *cliente;
}listaPaises;

typedef struct listaClientes{
	char nome[50];
	int codPlano;
//add tipo cliente(decidido ou indeciso)
	struct listaClientes *next;
}listaClientes;

listaPaises *criarElemento(char nomePais[50], int codPais);
void encadear_listaPaises(listaPaises **listaTotal_Paises, listaPaises *elementoPaises);
void listarPaises(listaPaises *listaTotal);

int main(){
	listaPaises *listaTotal_Paises = NULL;
	
	listaPaises *paisRussia = criarElemento("Russia", 1);
	encadear_listaPaises(&listaTotal_Paises, paisRussia);
	
	listaPaises *paisEspanha = criarElemento("Espanha", 2);
	encadear_listaPaises(&listaTotal_Paises, paisEspanha);
	
	listaPaises *paisItalia = criarElemento("Italia", 3);
	encadear_listaPaises(&listaTotal_Paises, paisItalia);
	
	listaPaises *paisGrecia = criarElemento("Grecia", 4);
	encadear_listaPaises(&listaTotal_Paises, paisGrecia);
	listarPaises(listaTotal_Paises);
	
}//FIM main

listaPaises *criarElemento(char nomePais[50], int codPais){
	listaPaises *novo = (listaPaises*)malloc(sizeof(listaPaises));
	if(novo == NULL) exit(EXIT_FAILURE);
	
	novo->cod = codPais;
	strcpy(novo->nome, nomePais);
	novo->next = NULL;
	novo->cliente = NULL;
}//FIM function

void encadear_listaPaises(listaPaises **listaTotal_Paises, listaPaises *elementoPaises){
	if(*listaTotal_Paises == NULL){
		*listaTotal_Paises = elementoPaises;
	}else{
		elementoPaises->next = *listaTotal_Paises;
		*listaTotal_Paises = elementoPaises;	
	}
}//FIM function

void listarPaises(listaPaises *listaTotal_Paises){
	for(listaPaises *nodoAux = listaTotal_Paises; nodoAux != NULL; nodoAux = nodoAux->next)
	printf("%s ", nodoAux->nome);
}//FIM function







