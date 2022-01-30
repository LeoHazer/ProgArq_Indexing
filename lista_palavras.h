/****************************
Lista circular duplamente encadeada com sentinela - a melhor de todas!!!
****************************/

#include "lista_ocorrencias.h"
#include <ctype.h>
//#include "meu_indice.h"

typedef struct palavra{
    char letras[50];
    int qtdOcorrencias;
    Ocorrencia *ocorrencias;
    struct palavra *prox,*ant;
}Palavra;

///cria uma lista de palavras apenas com o sentinela (ele não terá ocorrências)
Palavra *CriarListaPalavras(){
    Palavra *sentinela = (Palavra*)malloc(sizeof(Palavra));
    sentinela->prox = sentinela;
    sentinela->ant = sentinela;
    sentinela->ocorrencias = NULL;
    return sentinela;
}

//Retorna o indice da letra inicial da palavra
int geraIndice(char *letra, int tam){

char alfa[26];

//Vetor de alfabeto para comparar
for(int i = 0; i < 26; i++){
    alfa[i] = (97 + i);
}

        int esq = 0 ;
        int dir = tam - 1;
        while (esq <= dir)
        {
            int meio = esq + (dir - esq) / 2;

        int res = -1000;   //Valor aleatorio
        if (letra == (alfa[meio]))
            res = 0;


            // Checa se está no meio
            if (res == 0)
                return meio;


            // Se 'letra' é maior, ignora a metade esquerda
            if (letra > (alfa[meio]))
                esq = meio + 1;


            // Se 'letra' é menor, ignora a metade direita
            else
                dir = meio - 1;
        }

        return -1;

}



///destroi a lista de palavras
Palavra *DestruirListaPalavras(Palavra *lista){
    Palavra *aux = lista;

    lista->ant->prox = NULL;
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
void InserirPalavraFim(Palavra *inicio, char *letras, int qtdOcorrencias){
    Palavra *novo = (Palavra*)malloc(sizeof(Palavra));

    strcpy(novo->letras,letras);
    novo->qtdOcorrencias = qtdOcorrencias;
    novo->ocorrencias = CriarListaOcorrencias();

    novo->prox = inicio;
    novo->ant = inicio->ant;

    inicio->ant->prox = novo;
    inicio->ant = novo;
}

///insere uma palavra em ordem alfabética na lista (para quando ler do arquivo texto)
Palavra *InserirPalavraOrdem(Palavra *lista, char *letras){
    Palavra *novo = (Palavra*)malloc(sizeof(Palavra));

    strcpy(novo->letras,letras);
    novo->qtdOcorrencias = 0;
    novo->ocorrencias = CriarListaOcorrencias();

    Palavra *aux = lista->prox;

    while (aux!=lista && strcmp(aux->letras,letras)<0)
        aux = aux->prox;

    novo->prox = aux;
    novo->ant = aux->ant;

    aux->ant->prox = novo;
    aux->ant = novo;

    return novo;
}

///acrescenta uma nova ocorrência para a palavra
void AcrescentaNovaOcorrencia(Palavra *palAtual, int numLinha, int numArquivo){
    Ocorrencia *oc = palAtual->ocorrencias->ant; //verificar qual foi a última ocorrência da palavra
    if (oc->numArquivo==numArquivo){//outra ocorrência no mesmo arquivo
        oc->qtdLinhas++;
        oc->linhas = (int*) realloc(oc->linhas,sizeof(int) * oc->qtdLinhas);
        oc->linhas[oc->qtdLinhas-1] = numLinha;
    }else{//ocorrência num arquivo novo
        int *linhas = (int*)malloc(sizeof(int));
        linhas[0] = numLinha;
        InserirOcorrenciaFim(palAtual->ocorrencias,numArquivo,1,linhas);//insere uma nova ocorrência no final da lista
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

        LerOcorrencias(lista->ant->ocorrencias,qtdOcorencias,arq);
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
        printf("buscaP1\n\n");

    if (aux!=lista && strcmp(aux->letras,pal)==0)

        return aux;
    return NULL;
}

//Busca simples na lista
int buscaSimples (Palavra *lista[])
{
    char plvr[15];
    int indice = 0;
    Arquivo *arq;
    Ocorrencia *ocrr;


    printf("Digite a palavra para busca: \n");
    fflush(stdin);
    gets(plvr);


    char *pal = strtok(plvr," ");
    printf("bSimples\n");
    while (pal)
    {
        pal = tolower(pal);
        indice = plvr[0] - 97;
        printf("Palavra digitada: %s\n", plvr);
        printf("index da palavra: %i\n", indice);


        if (BuscarPalavra(lista[indice], pal))
        {
            printf("ACHOU!!\n");
        }
        printf("bSimples_2\n");
        pal = strtok(NULL," ");
        printf("index bSim: %d%\n", indice);

        return indice;
    }

return 0;

}
