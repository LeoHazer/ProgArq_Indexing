#ifndef Trab1_h
#define Trab1_h
#include <string.h>


/**
 STRUCT PALAVRA */
typedef struct Palavra
{
    char letras[50];
    int qtdOcorrencias;
    int *linhas;
} Palavra;

/**
 STRUCT ELEMENTO */
typedef struct elemento
{
    Palavra word;
    struct elemento *prox,*ant;
} elemento;



/**
 CRIA LISTA COM SENTINELA - OPCIONAL
 */

/**
 PREPARA MEMÓRIA PARA UM NOVO ELEMENTO NA LISTA*/
elemento *CriaElemento(char word[])
{
    elemento *resp=(elemento*) malloc(sizeof(elemento));
    strcpy(resp->word.letras, word);
    resp->word.qtdOcorrencias=1;
    resp->prox=NULL;
    resp->ant=NULL;
    return resp;
}




/**
 BUSCA PALAVRA NA LISTA*/
elemento *Existe(elemento *lista, char word[])
{
    if(lista==NULL) return NULL;
    return (lista->word.letras == word)? lista: Existe(lista->prox, word);
}

/**
 ADICIONA NOVA LINHA NAS OCORR�NCIAS DA PALAVRA GERADA*/
void criaLinha(elemento *tmp, int addLinha)
{
    tmp->word.linhas = (int*) realloc(tmp->word.linhas, (tmp->word.qtdOcorrencias+1)*sizeof(int));
    tmp->word.linhas[tmp->word.qtdOcorrencias] = addLinha;
    tmp->word.qtdOcorrencias++;
}

/*EXIBE A OCORR�NCIA DAS PALAVRAS*/
void mostraOcorrencia(Palavra plvr)
{
    printf("PALAVRA: %s | OCORR�NCIA: %i | LINHAS: ", plvr.letras, plvr.qtdOcorrencias);
    for (int i = 0; i < plvr.qtdOcorrencias; i++)
    {
        printf(" %d", *plvr.linhas);
        printf("\n\n");
    }

}




/**
 LISTAR PALAVRAS DO �NDICE*/
void Listar(elemento *lista)
{
    if(lista!=NULL)
    {
        printf("%s\n",lista->word.letras);
        Listar(lista->prox);
    }
}

//Destr�i Lista e retorna NULL no final
elemento *DestruirLista(elemento *lista)
{
    if(lista!=NULL)
    {
        DestruirLista(lista->prox);
        free(lista);
    }
    return NULL;
}

/**
 DESTRUIR O ÍNDICE*/


/**
 ORDEM ALFABÉTICA*/
void ordemAlfabetica(elemento *lst, Palavra plvr)
{
    elemento *novo = CriaElemento(plvr.letras);
    elemento *tmp = lst->prox;
    while (tmp!=lst && strcmp(plvr.letras, tmp->word.letras)>0)
    {
        tmp = tmp->prox;
    }

    novo->prox = tmp;
    novo->ant = tmp->ant;
    tmp->ant->prox = novo;
    tmp->ant = novo;
}




/**
 INSERE NO FINAL DA LISTA */

void insereFim(elemento *lst, Palavra plvr)
{
    elemento *novo = CriaElemento(plvr.letras);
    novo->prox = lst;
    novo->ant = lst->ant;
    lst->ant->prox = novo;
    lst->ant = novo;
}
#endif // Trab1_h
