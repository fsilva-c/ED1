#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
	int info;
	struct nodo *next;
}Nodo;

void inserirPilha(Nodo **topoPilha);
void retirarPilha(Nodo **topoPilha);
void listarPilha(Nodo *topoPilha);
void menuPilha();

int main(){
	
	Nodo *topoPilha = NULL;
	
	char opcaoDigitada;
	
	for(;;){
		
		menuPilha();
		printf("\nInforme uma opcao: ");
		scanf(" %c", &opcaoDigitada);
		system("cls");
	
			if(opcaoDigitada == '1') inserirPilha(&topoPilha);
			if(opcaoDigitada == '2') retirarPilha(&topoPilha);
			if(opcaoDigitada == '3') listarPilha(topoPilha);
			if(opcaoDigitada == '4') break;
	
	}
	
	system("pause");
	
} // FIM main

void inserirPilha(Nodo **topoPilha){
	
	Nodo *novo = (Nodo*)malloc(sizeof(Nodo));
	if(novo == NULL) exit(EXIT_FAILURE);
	
	printf("Informe um numero para empilhar: ");
	scanf(" %d", &novo->info);
	
	if(*topoPilha == NULL) novo->next = NULL;
	else novo->next = *topoPilha;
	
	*topoPilha = novo;
	
}

void retirarPilha(Nodo **topoPilha){
	
	if(*topoPilha == NULL){
		printf("Pilha vazia!\n");
		return;	
	}
	
	Nodo *elementoAux = *topoPilha;
	*topoPilha = elementoAux->next;
	printf("Elemento removido: [%d]\n", elementoAux->info);
	free(elementoAux);
	
}

void listarPilha(Nodo *topoPilha){
	
	if(topoPilha == NULL){
		printf("Pilha vazia!\n");
		return;
	}
	
	for(Nodo *i = topoPilha; i != NULL; i = i->next) printf("[%d]\n", i->info);
	
}

void menuPilha(){
	
	printf("=================================\n");
	
	printf("1-> Inserir na pilha\n");
	printf("2-> Remover da pilha\n");
	printf("3-> Listar a pilha\n");
	printf("4-> Sair\n");
	
	printf("=================================");
	
}
