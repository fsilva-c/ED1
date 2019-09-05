#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//a estrutura de clientes ira apontar para a estrutura paises
//lista deve ser criada previamente, em tempo de compilação 

/*
60 pergunta1 60
50 pergunta2 50
70 Testanto a pergunta com espacos entre as palavras
40 pergunta4 40
56 pergunta5 56
66 pergunta6 66
80 pergunta7 80
30 pergunta8 30
46 pergunta9 46
54 pergunta10 54
58 pergunta11 58
64 pergunta12 64
68 pergunta13 68
76 pergunta14 76
90 Voce gosta de flores?
29 paisA
33 paisB
45 paisC
49 paisD
53 paisE
55 paisF
47 paisG
59 paisH
63 paisI
65 paisJ
67 paisK
69 paisL
75 paisM
79 paisN
89 paisO
101 paisP
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
