#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//a estrutura de clientes ira apontar para a estrutura paises
//lista deve ser criada previamente, em tempo de compilação 

/*
pergunta1 60
pergunta2 50
pergunta3 70
pergunta4 40
pergunta5 56
pergunta6 66
pergunta7 80
pergunta8 30
pergunta9 46
pergunta10 54
pergunta11 58
pergunta12 64
pergunta13 68
pergunta14 76
pergunta15 90
paisA 29
paisB 33
paisC 45
paisD 49
paisE 53
paisF 55
paisG 57
paisH 59
paisI 63
paisJ 65
paisK 67
paisL 69
paisM 75
paisN 79
paisO 89
paisP 101
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

typedef struct arvoreDecisao{
	char info[100];
	int cod;
	struct arvoreDecisao *casoSim;
	struct arvoreDecisao *casoNao;
}Arvore;

Arvore *criar_Raizes(Arvore *raiz);
Arvore *gerar_Arvore(Arvore *raiz, char infoRaiz[], int codArvore);
void printEmOrdem(Arvore *raiz);

listaPaises *criarElemento(char nomePais[50], int codPais);
void encadear_listaPaises(listaPaises **listaTotal_Paises, listaPaises *elementoPaises);
void gerar_ListaPaiseslista(listaPaises **listaTotal_Paises);
void listarPaises(listaPaises *listaTotal);

int main(){
	listaPaises *listaTotal_Paises = NULL;
	
	gerar_ListaPaiseslista(&listaTotal_Paises);
	listarPaises(listaTotal_Paises);
	
	Arvore *raizBase = NULL;
	raizBase = criar_Raizes(raizBase);
   	printEmOrdem(raizBase);
	system("pause");
	return 0;
	
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
	
	char nomePais[50] = {'\0'};
	unsigned short codPais;
	while(fscanf(ptrArquivo, "%d %[^\n]s", &codPais, nomePais) != EOF){
		if(codPais % 2){
			listaPaises *elemento = criarElemento(nomePais, codPais);
			encadear_listaPaises(listaTotal_Paises, elemento);
		}
	}
	fclose(ptrArquivo);
}//FIM function

Arvore *criar_Raizes(Arvore *raiz){
     char infoRaiz[99] = {'\0'};
     int codArvore;

     FILE *ptrArquivo = fopen("perguntas_Paises.txt", "r");
     if(ptrArquivo == NULL)
        exit(EXIT_FAILURE);

     while(fscanf(ptrArquivo, "%d %[^\n]s", &codArvore, infoRaiz) != EOF)
          raiz = gerar_Arvore(raiz, infoRaiz, codArvore);

     fclose(ptrArquivo);
     return (raiz);
     }

Arvore *gerar_Arvore(Arvore *raiz, char infoRaiz[], int codArvore){
    if(!raiz){
        raiz = (Arvore*)malloc(sizeof(Arvore));
        raiz->casoSim = NULL;
        raiz->casoNao = NULL;
        raiz->cod = codArvore;
        strcpy(raiz->info,infoRaiz);
    }
    else{
        if(raiz->cod < codArvore)
            raiz->casoSim = gerar_Arvore(raiz->casoSim, infoRaiz, codArvore);
        else
            raiz->casoNao = gerar_Arvore(raiz->casoNao, infoRaiz, codArvore);
    }
    return (raiz);
}

void printEmOrdem(Arvore *raiz){
    //Percorre a arvore atÃ© o ultimo no a esquerda, depois printa esse no e percorre todos os seus nos a direta,
    //repetindo esse movimento para os nos a esquerda, anteriores
    if(!raiz)
        return;
    printEmOrdem(raiz->casoNao);
    printf("[%s]\t[%d]\n", raiz->info, raiz->cod);
    printEmOrdem(raiz->casoSim);
}

void listarPaises(listaPaises *listaTotal_Paises){
	for(listaPaises *nodoAux = listaTotal_Paises; nodoAux != NULL; nodoAux = nodoAux->next)
	printf("%d -- %s\n", nodoAux->cod, nodoAux->nome);
}//FIM function
