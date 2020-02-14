#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
	int info;
	struct nodo *next, *prev;
}Nodo;

void inserirLista(Nodo **listaTotal);
void retirarLista(Nodo **listaTotal);
void exibirLista(Nodo *listaTotal);
void menuLista();

int main(){
	
	Nodo *listaTotal = NULL;
	
	char opcaoInformada;
	
	for(;;){
		system("cls");
		exibirLista(listaTotal);
		menuLista();
		printf("Informe uma opcao: ");
		scanf(" %c", &opcaoInformada);
		
		if(opcaoInformada == '1') inserirLista(&listaTotal);
		if(opcaoInformada == '2') retirarLista(&listaTotal);
		if(opcaoInformada == '3') exibirLista(listaTotal);
		if(opcaoInformada == '4') break;
		
		
	}//FIM laço infinito
	system("pause");
	return 99909;
}//FIM main

void inserirLista(Nodo **listaTotal){
	
	Nodo *novo = (Nodo*)malloc(sizeof(Nodo));
	if(novo == NULL) exit(EXIT_FAILURE);
	
	printf("Informe um valor: ");
	scanf(" %d", &novo->info);
	novo->next = NULL;
	novo->prev = NULL;
	
	if(*listaTotal == NULL){
		*listaTotal = novo;
	}else{
		
		Nodo *nodoAtual = *listaTotal;
		while((nodoAtual->next != NULL) && (nodoAtual->info < novo->info)) nodoAtual = nodoAtual->next;
					
		if((nodoAtual == *listaTotal) && (nodoAtual->info > novo->info)){
			novo->next = *listaTotal;
			nodoAtual->prev = novo;
			*listaTotal = novo;
			
		}else if((nodoAtual->next == NULL) && (nodoAtual->info < novo->info)){
			nodoAtual->next = novo;
			novo->prev = nodoAtual;
		}else{
			nodoAtual->prev->next = novo;
			novo->prev = nodoAtual->prev;
			novo->next = nodoAtual;
			nodoAtual->prev = novo;		
		}
	}//FIM else; se não houver elementos
}//FIM function

void retirarLista(Nodo **listaTotal){
	
	if(*listaTotal == NULL){
		printf("Lista vazia!\n");
		return;
	}
	
	int numInformado;
	printf("Informe um elemento para retirar: ");
	scanf(" %d", &numInformado);
	
	Nodo *aux = NULL;
	if((((*listaTotal)->next) == NULL) && ((*listaTotal)->prev == NULL) && (*listaTotal)->info == numInformado){
		aux = *listaTotal;
		free(aux);
		*listaTotal = NULL;
	}else{
	
		Nodo *nodoAtual, *nodoFree; nodoAtual = *listaTotal; nodoFree = NULL;
		while((nodoAtual->next != NULL) && (nodoAtual->info != numInformado)) nodoAtual = nodoAtual->next;
	
		if((nodoAtual == *listaTotal) && (nodoAtual->info == numInformado)){
			nodoFree = nodoAtual;
			nodoAtual = nodoAtual->next;
			nodoAtual->prev = NULL;
			*listaTotal = nodoAtual;
			free(nodoFree);
		}else if((nodoAtual->next == NULL) && (nodoAtual->info == numInformado)){
			Nodo *nodoAux = nodoAtual;
			nodoAux = nodoAux->prev;
			nodoFree = nodoAtual;
			nodoAux->next = NULL;
			free(nodoFree);
		}else if((nodoAtual->next && nodoAtual->prev) && (nodoAtual->info == numInformado)){
			nodoFree = nodoAtual;
			nodoAtual->prev->next = nodoAtual->next;
			nodoAtual->next->prev = nodoAtual->prev;
			free(nodoFree);
		}else{
			printf("Elemento nao encontrado!\n");
			return;
		}
	}
	system("pause");
}//FIM function

void exibirLista(Nodo *listaTotal){
	
	if(listaTotal == NULL){
		printf("Lista vazia!\n");
		return;
	}
	
	for(Nodo *i = listaTotal; i != NULL; i = i->next) printf("[%d] ", i->info);
}//FIM function

void menuLista(){
	
	printf("\n============================\n");
	printf("1-> Inserir\n");
	printf("2-> Remover\n");
	printf("3-> Listar\n");
	printf("4-> Sair\n");
	printf("\n============================\n");	
}
