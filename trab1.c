#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "trab1.h"

// elemento *CriaLista()
// {
//     return NULL;
// }

int Menu()
{
    int select;
    printf("\n\nEscolha uma opcao\n");
    printf("[1]- Criar Indice para um Arquivo Texto\n");
    printf("[2]- Utilizar um Indice existente para realizar buscas por Palavras\n");
    printf("[3]- Encerrar Programa\n");
    printf("\nEscolha: ");
    scanf("%d", &select);
    getchar();
    printf("\n");
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

       // printf("\nLINHA TESTE\n");
        while (feof(arq) == 0)
        {
            fgets(linha, 1000, arq);
            //puts(linha);
            geraLinha(lst, linha, contLinha, contPalavras);
            contLinha++;
        }
        printf("Index criado com sucesso!!");
        fclose(arq);
    }
    return lst;
}

//FAZ 1 REGISTRO NO ARQUIVO BINARIO POR VEZ
void escreveArqBinario(FILE *arq, Palavra plvr)
{
    int sizePalavra = strlen(plvr.letras)+1;
    fwrite(&sizePalavra, sizeof(int), 1, arq);
    fwrite(plvr.letras, sizeof(char), sizePalavra, arq);
    fwrite(&plvr.qtdOcorrencias, sizeof(int), 1, arq);
    fwrite(plvr.linhas, sizeof(int), plvr.qtdOcorrencias, arq);
}

//FAZ LEITURA DE PALAVRA NO ARQUIVO BINARIO
Palavra readBinario(FILE *arq)
{

    Palavra novo;
    int sizePalavra;
    fread(&sizePalavra, sizeof(int), 1, arq);
    fread(novo.letras, sizeof(char), sizePalavra, arq);
    fread(&novo.qtdOcorrencias, sizeof(int), 1, arq);
    novo.linhas = (int*) malloc(novo.qtdOcorrencias * sizeof(int));
    fread(novo.linhas,sizeof(int),novo.qtdOcorrencias,arq);
    return novo;
}

//REGISTRA INDICE NO BINARIO
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

//INSERE NO FIM DA LISTA O ARQUIVO BINARIO LIDO
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

    setlocale(LC_ALL, "portuguese");

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

            system("cls");
            destroiIndice(lista);
            printf("Digite o nome do arquivo txt: ");
            fgets(nArquivo, 80, stdin);

            if(nArquivo[strlen(nArquivo)-1]=='\n') nArquivo[strlen(nArquivo)-1]='\0';
            fflush(stdin);

            lista = criaIndice(nArquivo, &contPalavra);
            escreveBinario(lista, contPalavra);
            
            Listar(lista);
            system("pause");
            break;

        case 2:
           
            system("cls");
            lista = insereBinFim(&contPalavra);
            printf("\n\nInforme a palavra para buscar: ");
            fflush(stdin);
            scanf("%s", palvra);
            printf("\n");
            aux = buscaPalavra(lista, palvra);
            if(aux == lista)
            {
                printf("\n\n[%s] nao foi encontrada!\n ", palvra);
            }
            else
            {
                mostraOcorrencia(aux->word);
            }
            system("pause");
            break;

        case 3:
            DestruirLista(lista);
            printf("\n\nFim do programa!\n");
            exit(-1);
            break;

        default:
            fprintf(stderr, "Opção invalida!\n");
            break;
        }
    }
    while (escolhe !=4);

    return 0;
}