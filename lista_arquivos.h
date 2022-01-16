/****************************
Lista circular duplamente encadeada com sentinela - a melhor de todas!!!
****************************/

typedef struct arquivo{
    char nome[50];
    struct arquivo *prox,*ant;
}Arquivo;

///cria uma lista apenas como sentinela
Arquivo *CriarListaArquivos(){
    Arquivo *sentinela = (Arquivo*)malloc(sizeof(Arquivo));
    sentinela->prox = sentinela;
    sentinela->ant = sentinela;
    return sentinela;
}

///destroi a lista
Arquivo *DestruirListaArquivos(Arquivo *lista){
    Arquivo *aux = lista;

    lista->ant->prox = NULL;
    while (aux!=NULL){
        lista = lista->prox;
        free(aux);
        aux = lista;
    }

    return NULL;
}

///insere um nome de arquivo no fim da lista
void InserirArquivoFim(Arquivo *inicio, char *nomeArq){
    Arquivo *novo = (Arquivo*)malloc(sizeof(Arquivo));

    strcpy(novo->nome,nomeArq);

    novo->prox = inicio;
    novo->ant = inicio->ant;

    inicio->ant->prox = novo;
    inicio->ant = novo;
}


///lê (de um arquivo binário) os nomes do arquivos que fazem parte do índice
void LerArquivos(Arquivo *lista, int qtd, FILE *arq){
    char nomeArquivo[50];
    int qtdLetras;

    for (int i=0;i<qtd;i++){
        fread(&qtdLetras,sizeof(int),1,arq);
        fread(nomeArquivo,sizeof(char),qtdLetras,arq);
        InserirArquivoFim(lista,nomeArquivo);
    }
}

///salva o nome dos arquivos que fazem parte do indice em um arquivo binário
void SalvarArquivos(Arquivo *lista, FILE *arq){
    Arquivo *arquivo = lista->prox;

    while (arquivo!=lista){
        int tamNome = strlen(arquivo->nome)+1;
        fwrite(&tamNome,sizeof(int),1,arq);
        fwrite(arquivo->nome,sizeof(char),tamNome,arq);

        arquivo = arquivo->prox;
    }
}

///mostra os nomes dos arquivos na tela
void MostrarArquivos(Arquivo *lista){
    int cont=1;
    Arquivo *aux = lista->prox;
    while (aux!=lista){
        printf("%d <%s>\n",cont++,aux->nome);
        aux = aux->prox;
    }
}

///busca na lista se existem algum arquivo com o nome especificado
Arquivo *BuscarArquivo(Arquivo *lista, char *nomeArq){
    Arquivo *aux = lista->prox;
    while (aux!=lista && strcmp(nomeArq,aux->nome)<0)
        aux = aux->prox;

    if (aux!=lista && strcmp(nomeArq,aux->nome)==0)
        return aux;
    return NULL;
}

