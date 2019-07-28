#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
	int info;
	struct nodo *next, *prev;
}Nodo;

void inserirLista(Nodo **listaTotal);
void exibirLista(Nodo *listaTotal);
void menuLista();


int main(){
	
	Nodo *listaTotal = NULL;
	
	char opcaoDigitada;
	
	for(;;){
		
		system("cls");
		exibirLista(listaTotal);
		menuLista();
		printf("\nInforme uma opcao: ");
		scanf(" %c", &opcaoDigitada);
		
		if(opcaoDigitada == '1') inserirLista(&listaTotal);
		if(opcaoDigitada == '2') exibirLista(listaTotal);
		if(opcaoDigitada == '3') break;
		
	}
	
	system("pause");
	
}// FIM main

void inserirLista(Nodo **listaTotal){
	
	Nodo *novo = (Nodo*)malloc(sizeof(Nodo));
	if(novo == NULL) exit(EXIT_FAILURE);
		
	printf("Informe um valor: ");
	scanf(" %d", &novo->info);
	
	if(*listaTotal == NULL){
		novo->next = NULL;
		novo->prev = NULL;
		*listaTotal = novo;
	}else{
		
		Nodo *nodoAtual = *listaTotal;
		//INSERIR NA PRIMEIRA POSIÇÃO
		if((novo->info)<= (nodoAtual->info)){
			nodoAtual->prev = novo;
			novo->next = nodoAtual;
			novo->prev = NULL;
			*listaTotal = novo;
		} else{
			
		while ((nodoAtual->next != NULL) && novo->info > nodoAtual->info) nodoAtual = nodoAtual->next;
		
		//for(Nodo *i = *listaTotal; i != NULL;) if(novo->info > nodoAtual->info) i = i->next;

		
		if((nodoAtual->next == NULL) && (novo->info >= nodoAtual->info)){
			nodoAtual->next = novo;
			novo->prev = nodoAtual;
			novo->next = NULL;
		} else{
			nodoAtual->prev->next = novo;
			novo->next = nodoAtual;
			nodoAtual->prev = novo;
			novo->prev = nodoAtual->prev->next;
		} // FIM else; insercao entre nós;			
			
		}// FIM else; insercao no meio da lista
				
	}// FIM else; lista não esta vazia
	
}

void exibirLista(Nodo *listaTotal){
	
	if(listaTotal == NULL){
		printf("Lista vazia!\n");
	}
	
	for(Nodo *i = listaTotal; i != NULL; i = i->next) printf("[%d] ", i->info);
	
}

void menuLista(){
	
	printf("\n=================================\n");
	
	printf("1-> Inserir na lista\n");
	printf("2-> Exibir a lista\n");
	printf("3-> Sair\n");
	
	printf("=================================");
	
}
