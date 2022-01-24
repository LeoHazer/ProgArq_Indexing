/****************************
Lista circular duplamente encadeada com sentinela - a melhor de todas!!!
****************************/

typedef struct ocorrencia{
    int numArquivo;
    int qtdLinhas;
    int *linhas;
    struct ocorrencia *prox,*ant;
}Ocorrencia;

///cria uma lista apenas com o sentinela (ele terá numArquivo -1, pois ele não tem ocorrências)
Ocorrencia *CriarListaOcorrencias(){
    Ocorrencia *sentinela = (Ocorrencia*)malloc(sizeof(Ocorrencia));
    sentinela->numArquivo = -1;
    sentinela->prox = sentinela;
    sentinela->ant = sentinela;
    return sentinela;
}

///destroi uma lista de ocorrência
Ocorrencia *DestruirListaOcorrencias(Ocorrencia *lista){
    Ocorrencia *aux = lista;

    lista->ant->prox = NULL;
    while (aux!=NULL){
        lista = lista->prox;
        free(aux->linhas);
        free(aux);
        aux = lista;
    }

    return NULL;
}

///insere uma ocorrência no fim da lista (tanto na leitura do binário quanto na leitura do texto)
void InserirOcorrenciaFim(Ocorrencia *inicio, int numArquivo, int qtdLinhas, int *linhas){
    Ocorrencia *novo = (Ocorrencia*)malloc(sizeof(Ocorrencia));

    novo->numArquivo = numArquivo;
    novo->qtdLinhas = qtdLinhas;
    novo->linhas = linhas;

    novo->prox = inicio;
    novo->ant = inicio->ant;

    inicio->ant->prox = novo;
    inicio->ant = novo;
}

///salva as ocorrência no arquivo binário
void SalvarOcorrencias(Ocorrencia *lista, FILE *arq){
    Ocorrencia *oc = lista->prox;

    while (oc!=lista){
        fwrite(&(oc->numArquivo),sizeof(int),1,arq);
        fwrite(&(oc->qtdLinhas),sizeof(int),1,arq);
        fwrite(oc->linhas,sizeof(int),oc->qtdLinhas,arq);

        oc = oc->prox;
    }
}

///lê as ocorrência do arquivo binário
void LerOcorrencias(Ocorrencia *lista, int qtd, FILE *arq){
    int numArquivo,qtdLinhas;
    int *linhas;

    for (int i=0;i<qtd;i++){
        fread(&numArquivo,sizeof(int),1,arq);
        fread(&qtdLinhas,sizeof(int),1,arq);
        linhas = (int*)malloc(sizeof(int)*qtdLinhas);
        fread(linhas,sizeof(int),qtdLinhas,arq);

        InserirOcorrenciaFim(lista,numArquivo,qtdLinhas,linhas);
    }
}

///mostra as ocorrências na tela
void MostrarOcorrencia(Ocorrencia *lista){
    Ocorrencia *aux = lista->prox;
    while (aux!=lista){
        printf("No arquivo %d existem %d ocorrencias nas linhas:",aux->numArquivo,aux->qtdLinhas);
        for (int i=0;i<aux->qtdLinhas;i++){
            printf(" %d",aux->linhas[i]);
        }
        printf("\n");
        aux = aux->prox;
    }
}
