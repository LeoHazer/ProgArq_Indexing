#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "trab1.h"

// elemento *CriaLista()
// {
//     return NULL;
// }

int Menu()
{
    int select;
    printf("Escolha uma opcao\n");
    printf("[1]- Criar Indice para um Arquivo Texto\n");
    printf("[2]- Utilizar um Indice existente para realizar buscas por Palavras\n");
    printf("[3]- Encerrar Programa\n");
    printf("[4]- Ocorrencia\n");
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
        elemento *temp = buscaPalavra(lst, palavra);
        if (temp == lst)
        {
            Palavra plvr;
            strcpy(plvr.letras, palavra); //Copia a palavra
            plvr.qtdOcorrencias = 1; //Ocorrência inicial
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

//FAZ LEITURA DO ARQUIVO E CRIA UM INDICE
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

        printf("\nLINHA TESTE\n");
        while (feof(arq) == 0)
        {
            fgets(linha, 1000, arq);
            //puts(linha);
            geraLinha(lst, linha, contLinha, contPalavras);
            contLinha++;
        }
        printf("\nLINHA TESTE 2\n");
        fclose(arq);
    }
    return lst;
}

//FAZ 1 REGISTRO NO ARQUIVO BINARIO POR VEZ
void escreveArqBinario(FILE *arq, Palavra plvr)
{
    printf("\nDAT 1\n");
    int sizePalavra = strlen(plvr.letras)+1;
    printf("\nDAT 1.1\n");
    fwrite(&sizePalavra, sizeof(int), 1, arq);
    printf("\nDAT 1.2\n");
    fwrite(plvr.letras, sizeof(char), sizePalavra, arq);
    printf("\nDAT 1.3\n");
    fwrite(&plvr.qtdOcorrencias, sizeof(int), 1, arq);
    printf("\nDAT 1.4\n");
    fwrite(plvr.linhas, sizeof(int), plvr.qtdOcorrencias, arq);
    printf("\nDAT 2\n");
}

//FAZ LEITURA DE PALAVRA NO ARQUIVO BINARIO
Palavra readBinario(FILE *arq)
{

    Palavra novo;
    int sizePalavra;
    printf("\nread_bin1\n");
    fread(&sizePalavra, sizeof(int), 1, arq);
    fread(novo.letras, sizeof(char), sizePalavra, arq);
    fread(&novo.qtdOcorrencias, sizeof(int), 1, arq);
    novo.linhas = (int*) malloc(novo.qtdOcorrencias * sizeof(int));
    fread(novo.linhas,sizeof(int),novo.qtdOcorrencias,arq);
    printf("\nread_bin2\n");
    return novo;
}

//REGISTRA INDICE NO BINARIO
void escreveBinario(elemento *lst, int contPalavra)
{
    printf("\nBIN 1\n");
    FILE *arq = fopen("indice.dat", "wb");

    printf("\nBIN 2\n");
    fwrite(&contPalavra, sizeof(int), 1, arq);

    printf("\nBIN 3\n");
    elemento *temp = lst->prox;
    while (temp!= lst)
    {
        printf("\nBIN 4\n");
        escreveArqBinario(arq, temp->word);
        temp = temp->prox;
        printf("\nBIN 5\n");
    }
    fclose(arq);
    printf("\nBIN 6\n");
}

//INSERE NO FIM DA LISTA O ARQUIVO BINARIO LIDO
elemento *insereBinFim(int *contPalavra)
{
    printf("\nB_FIM1\n");
    elemento *lst = CriaLista();
    printf("\nB_FIM2\n");
    FILE *arq = fopen("indice.dat", "rb");
    printf("\nB_FIM3\n");
    fread(contPalavra, sizeof(int), 1, arq);
    for (int i = 0; i < (*contPalavra); i++)
    {
        printf("\nB_FIM4\n");
        insereFim(lst, readBinario(arq));
    }
    printf("\nB_FIM5\n");
    fclose(arq);
    return lst;
}


int main()
{

    char nArquivo[80], palvra[80];
    elemento *lista = CriaLista();
    elemento *aux;
    int contPalavra =0;
    int escolhe;

    do
    {

        escolhe = Menu();

        switch (escolhe)
        {
        case 1:

            destroiIndice(lista);
            printf("Digite o nome do arquivo txt: ");
            fgets(nArquivo, 80, stdin);

            if(nArquivo[strlen(nArquivo)-1]=='\n') nArquivo[strlen(nArquivo)-1]='\0';
            fflush(stdin);

            printf("\nTESTE1\n");
            lista = criaIndice(nArquivo, &contPalavra);
            printf("\nTESTE2\n");
            printf("\nTESTE3\n");
            escreveBinario(lista, contPalavra);
            printf("\nTESTE4\n");
            printf("Index criado com sucesso!!\n\n");
            Listar(lista);
            break;

        case 2:
            /***/
            system("cls");
            //destroiIndice(lista);
            lista = insereBinFim(&contPalavra);
            printf("Informe a palavra para buscar.\n");
            fflush(stdin);
            scanf("%s", palvra);

            aux = buscaPalavra(lista, palvra);
            if(aux == lista)
            {
                printf("[%s] nao foi encontrada!\n ", palvra);
            }
            else
            {
                mostraOcorrencia(aux->word);
            }

            break;

        case 3:
            DestruirLista(lista);
            exit(-1);
            break;

        case 4:
            system("cls");
            //destroiIndice(lista);
            Listar(lista);
            break;

        default:
            fprintf(stderr, "Opcao invalida!\n");
            break;
        }
    }
    while (escolhe >=1 && escolhe <=5);


    return 0;
}
