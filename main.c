#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "meu_indice.h"

int Menu(){
    int resp=0;
    printf("1 - Processar um arquivo\n");
    printf("2 - Salvar o indice\n");
    printf("3 - Ler um indice\n");
    printf("4 - Buscar no indice atual\n");
    printf("5 - Encerrar\n");
    scanf("%d",&resp);
    return resp;
}

int main(){
    int op;
    char nomeArq[50];
    Indice ind = CriarIndice();

    do{
        op = Menu();
        switch(op){
        case 1:
                printf("Digite o nome do arquivo texto:");
                scanf("%s",nomeArq);
                ProcessarArquivo(&ind,nomeArq);
                break;
        case 2:
                SalvarIndice(ind);
                printf("Indice atual salvo com sucesso!\n");
                break;
        case 3:
                DestruirIndice(&ind);
                printf("Indice atual destruido!\n");
                ind = LerIndice();
                break;
        case 4:
                MostrarIndice(ind);
                break;
        }
    }while(op!=5);
    DestruirIndice(&ind);
}

