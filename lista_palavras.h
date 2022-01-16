/****************************
Lista circular duplamente encadeada com sentinela - a melhor de todas!!!
****************************/

#include "lista_ocorrencias.h"

typedef struct palavra{
    char letras[50];
    int qtdOcorrencias;
    Ocorrencia *ocorrencias;
    struct palavra *prox;//,*ant;
}Palavra;

///cria uma lista de palavras apenas com o sentinela (ele não terá ocorrências)
Palavra *CriarListaPalavras(){
    Palavra *sentinela = (Palavra*)malloc(sizeof(Palavra));
    sentinela->prox = NULL;//sentinela;
    //sentinela->ant = sentinela;
    sentinela->ocorrencias = NULL;
    return sentinela;
}

///destroi a lista de palavras
Palavra *DestruirListaPalavras(Palavra *lista){
    Palavra *aux = lista;

    //lista->ant->prox = NULL;
    while (aux!=NULL){
        lista = lista->prox;
        if (aux->ocorrencias) //sentinela não tem ocorrências
            aux->ocorrencias = DestruirListaOcorrencias(aux->ocorrencias);
        free(aux);
        aux = lista;
    }

    return NULL;
}

///insere uma palavra no fim da lista (para quando ler do arquivo binário)
void InserirPalavraFim(Palavra *lista, char *letras, int qtdOcorrencias){
    Palavra *novo = (Palavra*)malloc(sizeof(Palavra));

    strcpy(novo->letras,letras);
    novo->qtdOcorrencias = qtdOcorrencias;
    novo->ocorrencias = CriarListaOcorrencias();
    novo->prox=NULL;
    
    Palavra *aux=lista;
    while(lista!=NULL)
        aux=aux->prox;
    aux=novo;
    //novo->prox = inicio;
    //novo->ant = inicio->ant;

    //inicio->ant->prox = novo;
    //inicio->ant = novo;
}

///insere uma palavra em ordem alfabética na lista (para quando ler do arquivo texto)
void InserirPalavraOrdem(Palavra **lista, char *letras){
    //Palavra *novo = (Palavra*)malloc(sizeof(Palavra));
    char inicial=letras[0];
    if(inicial>=97 && inicial<=122){
        inicial-=32;
    }
    int idc=inicial-65;
    
    InserirPalavraFim(lista[idc],letras,1);
    // strcpy(novo->letras,letras);
    // novo->qtdOcorrencias = 0;
    // novo->ocorrencias = CriarListaOcorrencias();

    //Palavra *aux = lista->prox;

    // while (aux!=lista && strcmp(aux->letras,letras)<0)
    //     aux = aux->prox;

    // novo->prox = aux;
    // novo->ant = aux->ant;

    // aux->ant->prox = novo;
    // aux->ant = novo;

    //return novo;
}

///acrescenta uma nova ocorrência para a palavra
void AcrescentaNovaOcorrencia(Palavra *palAtual, int numLinha, int arquivo){
    Ocorrencia *oc = palAtual->ocorrencias->ant; //verificar qual foi a última ocorrência da palavra
    if (oc->arquivo==arquivo){//outra ocorrência no mesmo arquivo
        oc->qtdOcorrencias++;
        oc->linhas = (int*) realloc(oc->linhas,sizeof(int)*oc->qtdOcorrencias);
        oc->linhas[oc->qtdOcorrencias-1] = numLinha;
    }else{//ocorrência num arquivo novo
        int *linhas = (int*)malloc(sizeof(int));
        linhas[0] = numLinha;
        InserirOcorrenciaFim(palAtual->ocorrencias,arquivo,1,linhas);//insere uma nova ocorrência no final da lista
        palAtual->qtdOcorrencias++; //aumenta o número de ocorrência da palavra
    }
}

///lê as palavras de um arquivo binário
void LerPalavras(Palavra *lista, int qtd, FILE *arq){
    int qtdLetras;
    int qtdOcorencias;
    char letras[50];

    for (int i=0;i<qtd;i++){
        fread(&qtdLetras,sizeof(int),1,arq);
        fread(letras,sizeof(char),qtdLetras,arq);
        fread(&qtdOcorencias,sizeof(int),1,arq);

        InserirPalavraFim(lista,letras,qtdOcorencias);

        //LerOcorrencias(lista->ant->ocorrencias,qtdOcorencias,arq);-> rever
    }
}

///salva as palavras num arquivo binário
void SalvarPalavras(Palavra *inicio, FILE *arq){
    Palavra *pal = inicio->prox;

    while (pal!=inicio){
        int qtdLetras = strlen(pal->letras)+1;
        fwrite(&qtdLetras,sizeof(int),1,arq);
        fwrite(pal->letras,sizeof(char),qtdLetras,arq);
        fwrite(&(pal->qtdOcorrencias),sizeof(int),1,arq);
        SalvarOcorrencias(pal->ocorrencias,arq);

        pal = pal->prox;
    }
}

///mostra as palavras na tela
void MostrarPalavras(Palavra *lista){
    Palavra *aux = lista->prox;
    while (aux!=lista){
        printf("<%s> em %d arquivos\n",aux->letras,aux->qtdOcorrencias);
        MostrarOcorrencia(aux->ocorrencias);
        printf("\n");
        aux = aux->prox;
    }
}

///busca por uma palavra específica na lista
Palavra *BuscarPalavra(Palavra *lista, char *pal){
    Palavra *aux = lista->prox;
    while (aux!=lista && strcmp(aux->letras,pal)<0)
        aux = aux->prox;

    if (aux!=lista && strcmp(aux->letras,pal)==0)
        return aux;
    return NULL;
}

