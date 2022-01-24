#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "meu_indice.h"

int Menu(){
    int resp=0;
    printf("1 - Processar um arquivo\n");
    printf("2 - Salvar o indice\n");
    printf("3 - Ler um indice\n");
    printf("4 - Mostrar o indice\n");
    printf("5 - Fazer busca no indice\n");
    printf("6 - Encerrar\n");
    scanf("%d",&resp);
    return resp;
}

int MenuBusca(Indice ind){
        
        system("cls");
        int resp = 0;
        printf("1 - Busca simples\n");
        printf("2 - Busca composta (operador 'E')\n");
        printf("3 - Busca composta (operador 'OU')\n");
        scanf("%d", &resp);

        switch (resp)
        {
        case 1:
                buscaSimples(ind.iniciais);
                system("pause");
                break;
        case 2:
                break;

        
        default:
               Menu();
        }


}

int main(){
    int op;
    char nomeArq[50];
    Indice ind = CriarIndice();

    do{
        
        system("cls");
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
        case 5:
                MenuBusca(ind);
                break;
        }
    }while(op!=6);
    DestruirIndice(&ind);
}

