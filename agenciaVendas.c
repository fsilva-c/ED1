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
	char tipo;
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
void encadearClientes(listaPaises **listaTotal_Paises, listaClientes cliente, int codPais);
void gerar_ListaPaiseslista(listaPaises **listaTotal_Paises);
void listarPaises(listaPaises *listaTotal);
void listarEstrutura(listaPaises *listaTotal_Paises);
int buscaPais(Arvore *raiz);
int escolherDestino(int opInf);

void paisesVisitados(listaPaises *listaTotal_Paises);
void paisesNaoVisitados(listaPaises *listaTotal_Paises);
void clientesQueVisitaramUmPais(listaPaises *listaTotal_Paises, int codPais);
void paisesVisitadosPorPlano(listaPaises *listaTotal_Paises, int tipoPlano);
void paisesVisitadosPorDec_Ind(listaPaises *listaTotal_Paises, char tipoCliente);

void menuAgencia();
void menuRelatorios();


int main(){
	char opcao;
	int codPais;
	listaPaises *listaTotal_Paises = NULL;
	gerar_ListaPaiseslista(&listaTotal_Paises);
	
	menuAgencia();
	system("pause");
	menuRelatorios();
	
	Arvore *raizBase = NULL;
	raizBase = criar_Raizes(raizBase);
    //printEmOrdem(raizBase);
	
    listaClientes novoCliente;
    do{
    	system("cls");
    	printf("=================== BEM VINDO A AGENCIA DE VIAGENS ASSUNCAO TURISMO ===================\n\n");
    	//identificacao do cliente
    	fflush(stdin);
    	printf("Digite seu nome!\n-> ");
    	scanf("%[^\n]s", novoCliente.nome);
    	system("cls");
    	printf("Qual o plano da sua preferencia?\n(1)Padrao\t(2)Premium\n\nOpcao-> ");
    	scanf(" %d", &novoCliente.codPlano);
    	system("pause");
    	system("cls");
    	printf("================ Atualmente possuimos roteiros de viagens para os seguintes destinos ================\n\n");
    	listarPaises(listaTotal_Paises);
    	printf("\n\nJa possui um destino em mente?\n\n(s)Sim\t(n)Nao\nOpcao->");
    	scanf(" %c", &opcao);
    	if(opcao == 's'){
    		printf("\nDigite o codigo correspondente ao pais desejado!\n\n");
    		printf("Codigo do pais-> ");
    		scanf("%d", &codPais);
    		codPais = escolherDestino(codPais);
    		novoCliente.tipo = 'D';		//Cliente decidido
   		}
    	else{
    		printf("Iremos lhe ajudar!!!");
    		system("cls");
    		printf("===================== BEM VINDO A NOSSA ARVORE DE AUXILIO A DECISAO ====================");
    		codPais = buscaPais(raizBase);
    		novoCliente.tipo = 'I';		//Cliente indeciso
    	}
    	encadearClientes(&listaTotal_Paises, novoCliente, codPais);
		system("cls");
		system("pause");
		printf("Deseja cadastrar outro cliente?\n(s)Sim\t(n)Nao, sair do sistema\n\nOpcao->");
		scanf(" %c", &opcao);
		system("cls");
	}while(opcao != 'n');
	
	/*
	system("pause");
	listarEstrutura(listaTotal_Paises);
	printf("\n");
	
	system("pause");
	paisesVisitados(listaTotal_Paises);
	
	system("pause");
	paisesNaoVisitados(listaTotal_Paises);
	*/
	system("pause");
	printf("\n\n");
	int tipoPlano;
	printf("1-> Padrao\n2->Premium\n");
	printf("Informe o tipo de plano: ");
	scanf(" %d", &tipoPlano);
	paisesVisitadosPorPlano(listaTotal_Paises, tipoPlano);
	
	
	
	fflush(stdin);
	printf("\n\n");
	char tipoCliente;
	printf("D-> Decidido\nI->Indeciso\n");
	printf("Informe o tipo de plano: ");
	scanf(" %c", &tipoCliente);
	paisesVisitadosPorDec_Ind(listaTotal_Paises, tipoCliente);
	
	
	/* FUNCAO OK
	system("pause");
	int cdPais;
	listarPaises(listaTotal_Paises);
	printf("Informe um pais: ");
	scanf(" %d", &cdPais);
	cdPais = escolherDestino(cdPais);
	clientesQueVisitaramUmPais(listaTotal_Paises, cdPais);
	*/
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
}//FIM function

int buscaPais(Arvore *raiz){
	if(!raiz->casoSim){
		printf("O pais selecionado para voce eh: [%s]\n",raiz->info);
		system("pause");
		system("cls");
		return raiz->cod;
	}
	char opcao;	
	printf("%s\n", raiz->info);
	do{
		printf("\n(s)Sim;\t(n)Nao;\nInforme uma opcao: \n");
		scanf(" %c", &opcao);
		system("cls");
		if(opcao == 's')
			return buscaPais(raiz->casoSim);
		else if(opcao == 'n')
			return buscaPais(raiz->casoNao);
	}while(opcao != 'n' && opcao != 's');
}//FIM funcrion

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
	short somador = 1;
	for(listaPaises *nodoAux = listaTotal_Paises; nodoAux != NULL; nodoAux = nodoAux->next)
	printf("%d -- %s\n", somador++, nodoAux->nome);
}//FIM function

void encadearClientes(listaPaises **listaTotal_Paises, listaClientes cliente, int codPais){
	listaPaises *paisAtual = *listaTotal_Paises;
	while(paisAtual->cod != codPais)
		paisAtual = paisAtual->next;
	
	listaClientes *novoCliente = (listaClientes*)malloc(sizeof(listaClientes));
			strcpy(novoCliente->nome,cliente.nome);
			novoCliente->tipo = cliente.tipo;
			novoCliente->codPlano = cliente.codPlano;
			novoCliente->next = NULL;
			
	//PrimeiroCliente
	if(!(paisAtual->cliente))
		paisAtual->cliente = novoCliente;
	
	else{
		listaClientes *clienteAtual = paisAtual->cliente;
		while(clienteAtual->next)
			clienteAtual = clienteAtual->next;
		clienteAtual->next = novoCliente;
	}
}

int escolherDestino(int opInf){
    int codPais[16] = {91, 89, 77, 75, 69, 67, 65, 63, 59, 57, 55, 53, 47, 45, 31, 29};
    
    return codPais[opInf - 1];
}//FIM function

void listarEstrutura(listaPaises *listaTotal_Paises){
    listaClientes *listaTotal_Clientes;
    if(!listaTotal_Paises)
        printf("0xE004 - Nao ha nenhum pais cadastrado");
    while(listaTotal_Paises){
    		printf("\n");
            printf("[%s]",listaTotal_Paises->nome);
        if(listaTotal_Paises->cliente){
                listaTotal_Clientes = listaTotal_Paises->cliente;
        while(listaTotal_Clientes){
            printf("  [%s]",listaTotal_Clientes->nome);
          listaTotal_Clientes = listaTotal_Clientes->next;}
       }
        listaTotal_Paises = listaTotal_Paises->next;
    }
    return;
}

void paisesVisitados(listaPaises *listaTotal_Paises){
	system("cls");
	printf("======== LISTA DE PAISES VISITADOS =========\n\n");
	while(listaTotal_Paises != NULL){
		if(listaTotal_Paises->cliente != NULL)
			printf("[%s] ", listaTotal_Paises->nome);
		listaTotal_Paises = listaTotal_Paises->next;	
	}
}//FIM function

void paisesNaoVisitados(listaPaises *listaTotal_Paises){
	system("cls");
	printf("======== LISTA DE PAISES NAO VISITADOS =========\n\n");
	while(listaTotal_Paises != NULL){
		if(listaTotal_Paises->cliente == NULL)
			printf("[%s] ", listaTotal_Paises->nome);
		listaTotal_Paises = listaTotal_Paises->next;	
	}
}//FIM function

void clientesQueVisitaramUmPais(listaPaises *listaTotal_Paises, int cdPais){
	listaClientes *listaTotal_Clientes;
	while(listaTotal_Paises->cod != cdPais)
		listaTotal_Paises = listaTotal_Paises->next;
	
	if(listaTotal_Paises->cliente != NULL){
		listaTotal_Clientes = listaTotal_Paises->cliente;
		while(listaTotal_Clientes){
			printf("[%s]\n", listaTotal_Clientes->nome);	
			listaTotal_Clientes = listaTotal_Clientes->next;
		}
	}else return;
		
}//



//FUNCAO COM PROBLEMAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
void paisesVisitadosPorPlano(listaPaises *listaTotal_Paises, int tipoPlano){
	
	short checkPais;
	printf("======== LISTA DE PAISES VISITADOS POR PLANO =========\n\n");
	while(listaTotal_Paises != NULL){
		checkPais = 0;
		if(listaTotal_Paises->cliente != NULL){
			listaClientes *listaTotal_Clientes = listaTotal_Paises->cliente;
				while(listaTotal_Clientes->next != NULL && checkPais == 0){
					if(listaTotal_Clientes->codPlano == tipoPlano) 
						checkPais = 1;
				listaTotal_Clientes = listaTotal_Clientes->next;
			}
		}
		if(checkPais == 1) printf("[%s] ", listaTotal_Paises->nome);	
		listaTotal_Paises = listaTotal_Paises->next;	
 }
	return;
}//

void paisesVisitadosPorDec_Ind(listaPaises *listaTotal_Paises, char tipoCliente){
	listaClientes *listaTotal_Clientes;
	short check = 0;
	system("cls");
	printf("======== LISTA DE PAISES VISITADOS POR CLIENTE =========\n\n");
	while(listaTotal_Paises != NULL){
		check = 0;
		if(listaTotal_Paises->cliente != NULL){
			listaTotal_Clientes = listaTotal_Paises->cliente;
				while(listaTotal_Clientes->next != NULL && check == 0){
					if(listaTotal_Clientes->tipo == tipoCliente)
					check = 1;	
				listaTotal_Clientes = listaTotal_Clientes->next;
			}
		}
			if(check == 1) printf("[%s] ", listaTotal_Paises->nome);
		listaTotal_Paises = listaTotal_Paises->next;	
	}
	return;
}//


void menuAgencia(){
	system("cls");
	printf("=================== ASSUNSSAO TURISMOS ==================\n\n");
	printf("1-> CADASTRAR NOVO CLIENTE\n");
	printf("2-> PAIS MAIS VISITADO\n");
	printf("3-> PAIS VISITADO POR PLANO CONTRATUAL\n");
	printf("\n========================================================\n\n");
}//END function

void menuRelatorios(){
	system("cls");
	printf("======================= RELATORIOS ======================\n\n");
	printf("1-> PAISES DISPONIVEIS\n");
	printf("2-> PAISES VISITADOS POR CLIENTES DECIDIDOS\n");
	printf("3-> PAISES VISITADOS POR CLIENTES INDECISOS\n");
	printf("4-> PAISES VISITADOS\n");
	printf("5-> PAISES QUE AINDA NAO FORAM VISITADOS\n");
	printf("6-> Listagem DE CLIENTES DADO UM DETERMINADO PAIS\n");
	printf("\n========================================================\n\n");
}//END function


