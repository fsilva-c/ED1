#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
	int info;
	struct nodo *next;
}Nodo;

void inserirFila(Nodo **inicioFila, Nodo **fimFila);
void retirarFila(Nodo **inicioFila, Nodo **fimFila);
void listarFila(Nodo *inicioFila);
void menuFila();

int main(){
	
	Nodo *inicioFila = NULL; 
	Nodo *fimFila = NULL;
	
	char opcaoDigitada;
	
	for(;;){
		
		menuFila();
		printf("\nInforme uma opcao: ");
		scanf(" %c", &opcaoDigitada);
		system("cls");
	
			if(opcaoDigitada == '1') inserirFila(&inicioFila, &fimFila);
			if(opcaoDigitada == '2') retirarFila(&inicioFila, &fimFila);
			if(opcaoDigitada == '3') listarFila(inicioFila);
			if(opcaoDigitada == '4') break;
	
	}
	
	system("pause");
	
} // FIM main

void inserirFila(Nodo **inicioFila, Nodo **fimFila){
	
	Nodo *novo = (Nodo*)malloc(sizeof(Nodo));
	if(novo == NULL) exit(EXIT_FAILURE);
	
	printf("Informe um numero para enfileirar: ");
	scanf(" %d", &novo->info);
	
	novo->next = NULL;
	
	if(*inicioFila == NULL){
		*inicioFila = novo;
		*fimFila = novo;
	}else{
		(*fimFila)->next = novo;
	}
	
	*fimFila = novo;
	
}

void retirarFila(Nodo **inicioFila, Nodo **fimFila){
	
		if(*inicioFila == NULL){
		printf("Fila vazia!\n");
		return;	
	}
	
	Nodo *elementoAux = *inicioFila;
	*inicioFila = elementoAux->next;
	printf("Elemento removido: [%d]\n", elementoAux->info);
	free(elementoAux);
}
void listarFila(Nodo *inicioFila){
	
	if(inicioFila == NULL){
		printf("Fila vazia!\n");
		return;
	}
	
	for(Nodo *i = inicioFila; i != NULL; i = i->next) printf("[%d]\n", i->info);
	
}

void menuFila(){
	
	printf("=================================\n");
	
	printf("1-> Inserir na fila\n");
	printf("2-> Remover da fila\n");
	printf("3-> Listar a fila\n");
	printf("4-> Sair\n");
	
	printf("=================================");
	
}
