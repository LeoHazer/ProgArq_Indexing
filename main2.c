#include "trab.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

int qtdArquivos=0;

int Menu()
{
    int select;
    printf("\n\nEscolha uma opcao\n");
    printf("[1]- Procesar um Arquivo Texto\n");
    printf("[2]- Salvar Indice Atual\n");
    printf("[3]- Ler um Indice\n");
    printf("[4]- Mostrar Indice atual\n");
    printf("[5]- Encerrar\n");
    printf("\nEscolha: ");
    scanf("%d", &select);
    getchar();
    printf("\n");
    return select;
}

int main(){

    char nArq[80],word[80];
    Indice *ind=CriaIndice();
    int countW=0;
    int op;

    do{
        op=Menu();

        switch(op){
            case 1:
                printf("Digite o nome do arquivo txt: ");
                fgets(nArq, 80, stdin);

                if(nArq[strlen(nArq)-1]=='\n') 
                    nArq[strlen(nArq)-1]='\0';

                if(ArquivoLido(ind->arquivos, nArq)==0){
                    InsereArquivo(ind->arquivos, nArq);
                    ind->qtdArquivos++;
                    printf("\nArquivo Inserido com sucesso\n");
                    LerPalavrasArquivo(ind->palavras, nArq);
                }else
                   printf("\nEsse Arquivo Ja foi Lido!\n");
                break;
            case 2:
                SalvaIndice(ind);
                break;
            case 3:
                ind=DestruirIndice(ind);
                LerIndice(ind);
                break;
            case 4:
                ImprimeIndice(ind);
                break;
            case 5:
                ind=DestruirIndice(ind);
                break;
            default:
                printf("\nA opcao digitada eh invalida!\n");
                
        }
    }while(op!=5);

    return 0;
}

// int main() {
//     //Arquivo *arq=NULL;
//     Indice *ind;

//     ind = CriaIndice();
//     Ocorrencia *ocorr;
//     //ImprimeArq(ind->arquivos);
//     printf("\n");
//     InsereArquivo(ind->arquivos, "Arquivo 1");
//     InsereArquivo(ind->arquivos, "Arquivo 2");
//     InsereArquivo(ind->arquivos, "Arquivo 3");
//     //ImprimeArq(ind->arquivos);

//     ind->palavras=InserePalavra(ind->palavras, "Palavra 1");
//     //ind->palavras->ocorrencias=InsereOcorr(ocorr, 1);

//     ind->palavras=InserePalavra(ind->palavras, "Palavra 2");
//     //ind->palavras->ocorrencias=InsereOcorr(ocorr, 2);
//     //ImprimePalavras(ind->palavras);

//     ImprimeIndice(ind);
    
//     printf("\n\n");

//     printf("\nHello World\n");
//     return 0;
// }