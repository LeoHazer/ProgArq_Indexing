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

elemento *CriaLista()
{
    elemento *novo = (elemento*) malloc(sizeof(elemento));
    strcpy(novo->word.letras, "");
    novo->word.qtdOcorrencias = 0;
    novo->word.linhas = NULL;
    novo->prox = novo->ant = novo;
    return novo;
}


/**
 PREPARA MEMÓRIA PARA UM NOVO ELEMENTO NA LISTA*/
elemento *CriaElemento(Palavra nWord)
{
    elemento *resp=(elemento*) malloc(sizeof(elemento));
    resp->word = nWord;
    resp->prox = resp->ant = NULL;

    return resp;
}




/**
 BUSCA PALAVRA NA LISTA*/
elemento *Existe(elemento *lista, char word[])
{
    if(lista==NULL) return NULL;
    return (lista->word.letras == word)? lista: Existe(lista->prox, word);
}


elemento *buscaPalavra(elemento *lista, char *bPalavra)
{
    elemento *temp = lista->prox;
    //printf("\nResultado da busca pela palavra: %s\n", bPalavra);
    while (temp!=lista && strcmp(temp->word.letras, bPalavra)!=0 )
    {
        temp = temp->prox;
        //printf("%s\n", temp->word.letras);
    }
    return temp;
}

/**
 ADICIONA NOVA LINHA NAS OCORRÊNCIAS DA PALAVRA GERADA*/
void criaLinha(elemento *tmp, int addLinha)
{
    tmp->word.linhas = (int*) realloc(tmp->word.linhas, (tmp->word.qtdOcorrencias+1)*sizeof(int));
    tmp->word.linhas[tmp->word.qtdOcorrencias] = addLinha;
    tmp->word.qtdOcorrencias++;
}

/*EXIBE A OCORRÊNCIA DAS PALAVRAS*/
void mostraOcorrencia(Palavra plvr)
{
    printf("PALAVRA: %s\nOCORRENCIA: %i\nLINHAS: ", plvr.letras, plvr.qtdOcorrencias);
    for (int i = 0; i < plvr.qtdOcorrencias; i++)
    {
        printf(" %d", plvr.linhas[i]);
    }printf("\n\n");

}


/**
 LISTAR PALAVRAS DO ÍNDICE*/
void Listar(elemento *lista)
{
    elemento *temp = temp->prox;
    while (temp != lista)
    {
        mostraOcorrencia(temp->word);
        temp = temp->prox;
    }

}

//Destrói Lista e retorna NULL no final
void DestruirLista(elemento *lista){
	elemento *aux= lista;
	lista->ant->prox=NULL;

	while(aux!=NULL){
		lista=lista->prox;
		free(aux);
		aux=lista;
	}
}

/**
 DESTRUIR O ÍNDICE*/

void destroiIndice(elemento *lst)
{
    elemento *temp = lst;
    lst->ant->prox = NULL;

    while (temp != NULL)
    {
        lst = lst->prox;
        free(temp->word.linhas);
        free(temp);
        temp = lst;
    }

}



/**
 ORDEM ALFABÉTICA*/
void ordemAlfabetica(elemento *lst, Palavra plvr)
{
    elemento *novo = CriaElemento(plvr);
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
 INSERE PALAVRA NO FINAL DA LISTA */

void insereFim(elemento *lst, Palavra plvr)
{ 
    elemento *novo = CriaElemento(plvr);
    novo->prox = lst;
    novo->ant = lst->ant;
    lst->ant->prox = novo;
    lst->ant = novo;
}
#endif // Trab1_h
