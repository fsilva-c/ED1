#include <stdio.h>
#include <stdlib.h>

typedef struct nodo{
	int info;
	struct nodo *next;
}Nodo;

void inserirLista(Nodo **listaTotal);
void removerLista(Nodo **listaTotal);
void destruirLista(Nodo **listaTotal);
void exibirLista(Nodo *listaTotal);
void menuLista();

int main(){
	
	Nodo *listaTotal = NULL;
	
	char opcaoDigitada;
	
	for(;;){
		
		system("cls");
		exibirLista(listaTotal);
		menuLista();
		printf("Informe uma opcao: ");
		scanf(" %c", &opcaoDigitada);
		
		if(opcaoDigitada == '1') inserirLista(&listaTotal);
		if(opcaoDigitada == '2') removerLista(&listaTotal);
		if(opcaoDigitada == '3') destruirLista(&listaTotal);
		if(opcaoDigitada == '4') exibirLista(listaTotal);
		if(opcaoDigitada == '5') break;
		
	}//FIM laço infinito
	
	system("pause");
	return 99999;
}//FIM main

void inserirLista(Nodo **listaTotal){
	
	Nodo *novo = (Nodo*)malloc(sizeof(Nodo));
	if(novo == NULL) exit(EXIT_FAILURE);
	
	printf("Informe um numero: ");
	scanf(" %d", &novo->info);
	
	if(*listaTotal == NULL){
		*listaTotal = novo;
		novo->next = NULL;		
	}else{
		
		Nodo *nodoAtual, *nodoPrev; nodoAtual = *listaTotal; nodoPrev = NULL;
		while((nodoAtual != NULL) && (nodoAtual->info < novo->info)){
			nodoPrev = nodoAtual;
			nodoAtual = nodoAtual->next;
		}
		
		if(nodoAtual == *listaTotal){
			novo->next = *listaTotal;
			*listaTotal = novo;
		}else if(nodoAtual == NULL){
			nodoPrev->next = novo;
			novo->next = NULL;
		}else{
			nodoPrev->next = novo;
			novo->next = nodoAtual;
		}
		
	}//FIM else se não houver elementos
	
}//FIM function

void removerLista(Nodo **listaTotal){
	
	if(*listaTotal == NULL){
		printf("Lista vaiza!\n");
		return;
	}
	
	int numInformado; 
	printf("Informe um elemento para remover: ");
	scanf(" %d", &numInformado);
	
	Nodo *nodoAtual, *nodoPrev, *elementoRemov;
	nodoAtual = *listaTotal; nodoPrev = elementoRemov = NULL;
	while((nodoAtual != NULL) && nodoAtual->info != numInformado){
		nodoPrev = nodoAtual;
		nodoAtual = nodoAtual->next;
	} 
	
	if(nodoAtual == *listaTotal){
		elementoRemov = nodoAtual;
		*listaTotal = (*listaTotal)->next;
		free(elementoRemov);
	}else if(nodoAtual == NULL){
		printf("Elemento nao existe na lista!\n");
		return;
	}else{
		elementoRemov = nodoPrev->next;
		nodoPrev->next = nodoAtual->next;
		free(elementoRemov);
	}
	
}//FIM function

void destruirLista(Nodo **listaTotal){
	
	if(*listaTotal == NULL){
		printf("Lista vazia!\n");
		return;
	}
	
	Nodo *iFree, *iBusca; iFree = NULL; iBusca = *listaTotal;
	while(iBusca != NULL){
		iFree = iBusca;
		iBusca = iBusca->next;
		free(iFree);
	}
	
	*listaTotal = NULL;
}//FIM function

void exibirLista(Nodo *listaTotal){
	
	if(listaTotal == NULL){
		printf("Lista vazia!\n");
		return;
	}
	
	for(Nodo *i = listaTotal; i != NULL; i = i->next) printf("[%d] ", i->info);
}//FIM function

void menuLista(){
	
	printf("\n========================================\n");	
	printf("1-> Inserir na lista\n");
	printf("2-> Remover da lista\n");
	printf("3-> Destruir a lista\n");
	printf("4-> Exibir a lista\n");
	printf("5-> Sair");
	printf("\n========================================\n");		
}//FIM function
