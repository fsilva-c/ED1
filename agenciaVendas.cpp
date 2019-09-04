#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//a estrutura de clientes ira apontar para a estrutura paises
//lista deve ser criada previamente, em tempo de compilação 

/*
Russia 3
Espanha 5
Italia 7
Grecia 9
Alemanha 11
*/

typedef struct listaPaises{
	char nome[30];
	int cod;
	struct listaPaises *next;
	struct listaClientes *cliente;
}listaPaises;

typedef struct listaClientes{
	char nome[50];
	int codPlano;
	struct listaClientes *next;
}listaClientes;

listaPaises *criarElemento(char nomePais[50], int codPais);
void encadear_listaPaises(listaPaises **listaTotal_Paises, listaPaises *elementoPaises);
void gerar_ListaPaiseslista(listaPaises **listaTotal_Paises);
void listarPaises(listaPaises *listaTotal);

int main(){
	listaPaises *listaTotal_Paises = NULL;
	
	gerar_ListaPaiseslista(&listaTotal_Paises);
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

void gerar_ListaPaiseslista(listaPaises **listaTotal_Paises){
	FILE *ptrArquivo = fopen("perguntas_Paises.txt", "r");
	if(ptrArquivo == NULL) exit(EXIT_FAILURE);
	
	unsigned short codPais;
	char nomePais[50] = {'\0'};
	while(fscanf(ptrArquivo, "%s %d", nomePais, &codPais) != EOF){
		listaPaises *elemento = criarElemento(nomePais, codPais);
		encadear_listaPaises(listaTotal_Paises, elemento);
	}
	fsclose(ptrArquivo);
}//FIM function

void listarPaises(listaPaises *listaTotal_Paises){
	for(listaPaises *nodoAux = listaTotal_Paises; nodoAux != NULL; nodoAux = nodoAux->next)
	printf("%s ", nodoAux->nome);
}//FIM function
