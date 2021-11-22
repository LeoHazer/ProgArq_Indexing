#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trab1.h"

elemento *CriaLista()
{
    return NULL;
}

int Menu()
{
    int select;
    printf("Escolha uma opcao\n");
    printf("[1]- Criar Indice para um Arquivo Texto\n");
    printf("[2]- Utilizar um Indice existente para realizar buscas por Palavras\n");
    printf("[3]- Encerrar Programa\n");
    scanf("%d", &select);
    getchar();
    return select;
}

//Prepara a linha lida do arquivo
void geraLinha(elemento *lst, char *linha, int contLinha, int *contPalavra)
{
    char *palavra  = strtok(linha, " ,.\n");
    while (palavra != NULL)
    {
        elemento *temp = Existe(lst, palavra);
        if (temp == lst)
        {
            Palavra plvr;
            strcpy(plvr.letras, palavra); //Copia a palavra
            plvr.qtdOcorrencias = 1; //Ocorr�ncia inicial
            plvr.linhas = (int*)malloc(sizeof(int));
            plvr.linhas[0] = contLinha; //Numero da linha
            ordemAlfabetica(lst, plvr);
            (*contPalavra)++;

        }
        else
        {
            criaLinha(temp, contLinha);
        }
        palavra = strtok(NULL, " ,.\n");
    }

}

//FAZ LEITURA DO ARQUIVO E CRIA UM �NDICE
elemento *criaIndice(char *nomeArq, int *contPalavras)
{

    char linha[1000], *palavra;
    int contLinha = 1;
    elemento *lst = CriaLista();
    FILE *arq = fopen(nomeArq, "r");

    if (arq == NULL)
    {
        fprintf(stderr, "Erro ao acessar arquivo");
    }
    else
    {

        while (feof(arq) == 0)
        {
            fgets(linha, 1000, arq);
            geraLinha(lst, linha, contLinha, contPalavras);
            contLinha++;
        }
        fclose(arq);
    }
    return lst;
}

//FAZ REGISTRO NO ARQUIVO BIN�RIO
void escreveArqBinario(FILE *arq, Palavra plvr)
{
    int sizePalavra = strlen(plvr.letras)+1;
    fwrite(&sizePalavra, sizeof(int), 1, arq);
    fwrite(plvr.letras, sizeof(char), sizePalavra, arq);
    fwrite(&plvr.qtdOcorrencias, sizeof(int), 1, arq);
    fwrite(plvr.linhas, sizeof(int), plvr.qtdOcorrencias,arq);
}

//FAZ LEITURA DE PALAVRA NO ARQUIVO BIN�RIO
Palavra readBinario(FILE *arq)
{
    Palavra novo;
    int sizePalavra;
    fread(&sizePalavra, sizeof(int), 1, arq);
    fread(novo.letras, sizeof(char), sizePalavra, arq);
    fread(&novo.qtdOcorrencias, sizeof(int), 1, arq);
    novo.linhas = (int*) malloc(sizeof(int)*novo.qtdOcorrencias);
    fread(novo.linhas,sizeof(int),novo.qtdOcorrencias,arq);
    return novo;
}

//REGISTRA �NDICE NO BIN�RIO
void escreveBinario(elemento *lst, int contPalavra)
{
    FILE *arq = fopen("indice.dat", "wb");

    fwrite(&contPalavra, sizeof(int), 1, arq);

    elemento *temp = lst->prox;
    while (temp!= lst)
    {
        escreveArqBinario(arq, temp->word);
        temp = temp->prox;
    }
    fclose(arq);
}

//INSERE NO FIM DA LISTA O ARQUIVO BIN�RIO LIDO
elemento *insereBinFim(int *contPalavra)
{
    elemento *lst = CriaLista();
    FILE *arq = fopen("indice.dat", "rb");
    fread(contPalavra, sizeof(int), 1, arq);
    for (int i = 0; i < (*contPalavra); i++)
    {
        insereFim(lst, readBinario(arq));
    }
    fclose(arq);
    return lst;
}






int main()
{

    char nArquivo[80], palvra[80];
    elemento *lista = CriaLista();
    int contPalavra =0;
    int escolhe;

    while ( (escolhe = Menu() != 3) )
    {
        switch (escolhe)
        {
        case 1:
            printf("Digite o nome do arquivo txt: ");
            fgets(nArquivo, 80, stdin);

            if(nArquivo[strlen(nArquivo)-1]=='\n') nArquivo[strlen(nArquivo)-1]='\0';
            fflush(stdin);

            lista = criaIndice(nArquivo, &contPalavra);
            Listar(lista);
            escreveBinario(lista, contPalavra);
            break;
        case 2:
            /***/
            lista = insereBinFim(&contPalavra);
            printf("Insira a palavra para busca: \n");
            fgets(palvra, 80, stdin);
            fflush(stdin);

            elemento *tmp = Existe(lista, palvra);
            if (tmp == lista)
            {
                printf(" %s nao encontrada!\n",palvra);
            }
            else
            {
                mostraOcorrencia(tmp->word);
            }
            break;
        case 3:
            DestruirLista(lista);



        default:
            fprintf(stderr, "Opcao invalida!\n");
            break;
        }
    }



    return 0;
}
