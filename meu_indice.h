#include "lista_arquivos.h"
#include "lista_palavras.h"
#define NOME_ARQ_INDICE "indice.dat"
#include <ctype.h>

typedef struct indice{
    int qtdArquivos;
    Arquivo *arquivos;
    int qtdPalavras;
    Palavra *iniciais[26];
}Indice;

///criaum indice vazio
Indice CriarIndice(){
    Indice resp;
    int i;
    resp.qtdArquivos = 0;
    resp.arquivos = CriarListaArquivos();
    resp.qtdPalavras = 0;

    for (int i = 0; i < 26; i++)
    {
        resp.iniciais[i] = CriarListaPalavras();
    }


    return resp;
}


int MenuBusca(Indice *ind){

        system("cls");
        int resp = 0;
        int indice  = 0;
        printf("1 - Busca simples\n");
        printf("2 - Busca composta (operador 'E')\n");
        printf("3 - Busca composta (operador 'OU')\n");
        scanf("%d", &resp);

        switch (resp)
        {
        case 1:
                indice = buscaSimples(&ind->iniciais);
                if(buscaSimples(&ind->iniciais) != 0){
                    //MostrarIndice(ind);
                    MostrarPalavras(ind->iniciais[indice]);
                }

                system("pause");
                break;
        case 2:
                break;


        default:
               exit(-1);
        }
return 0;

}






///destroi o indice (de fato, destroi apenas as listas)
void DestruirIndice(Indice *ind){
    ind->qtdArquivos = 0;
    ind->arquivos = DestruirListaArquivos(ind->arquivos);

    ind->qtdPalavras = 0;
   // ind->palavras = DestruirListaPalavras(ind->iniciais);
}

///lê um indice de um arquivo binário
Indice LerIndice(){
    Indice resp = CriarIndice();

    FILE *arq = fopen(NOME_ARQ_INDICE,"rb");

    fread(&resp.qtdArquivos,sizeof(int),1,arq);
    LerArquivos(resp.arquivos,resp.qtdArquivos,arq);
    printf("O indice lido tem %d arquivos\n",resp.qtdArquivos);

    fread(&resp.qtdPalavras,sizeof(int),1,arq);
   // LerPalavras(resp.palavras,resp.qtdPalavras,arq);
     //Fazer um for para os indices das iniciais(?)

    for (int i = 0; i < 26; i++)
    {
        LerPalavras(resp.iniciais[i],resp.qtdPalavras,arq);
    }


    printf("O indice lido tem %d palavras\n",resp.qtdPalavras);

    fclose(arq);

    return resp;
}

///salva um indice num arquivo binario
void SalvarIndice(Indice ind){
    FILE *arq = fopen(NOME_ARQ_INDICE,"wb");

    Palavra novo = **ind.iniciais;
    fwrite(&ind.qtdArquivos,sizeof(int),1,arq);
    SalvarArquivos(ind.arquivos,arq);
    fwrite(&ind.qtdPalavras,sizeof(int),1,arq);
  //SalvarPalavras(ind.palavras,arq); FAZER LAÇO PARA CADA LETRA (ind)
    for (int i = 0; i < 26; i++)
    {
        SalvarPalavras(ind.iniciais[i], arq);
    }

    fclose(arq);
}


///mostra as informações do indice na tela
void MostrarIndice(Indice ind){
    printf("\n%d Arquivos no indice:\n",ind.qtdArquivos);
    MostrarArquivos(ind.arquivos);
    printf("\n%d Palavras no indice:\n",ind.qtdPalavras);
  //  MostrarPalavras(ind.palavras); -  FAZER LAÇO PARA CADA LETRA (ind)
  for (int i = 0; i < 26; i++)
  {
      MostrarPalavras(ind.iniciais[i]);
  }

    printf("\n");
}


///processa uma linha de um arquivo texto
void ProcessarLinha(Indice *ind, char *linha, int numLinha){

    linha = tolower(linha);
    char *pal = strtok(linha," ");
    int indice = 0;

    while (pal){
        indice = pal[0] - 97;
        printf("Valor index: %d\n", indice);
        printf("%c\n", pal[0]);

        Palavra *palavra = BuscarPalavra(ind->iniciais[indice], pal);
        printf("retorno busca %d\n", palavra);


        if (palavra==NULL){//palavra nao encontrada (primeira ocorrencia no indice)
            printf("insere palavra %d\n", ind->iniciais[indice]);
            palavra = InserirPalavraOrdem(ind->iniciais[indice], pal);
            printf("insere palavra2\n");
           // palavra = InserirPalavraOrdem(ind->palavras,pal);
            ind->qtdPalavras++;
            printf("laco\n");
        }

        printf("ocorr\n");
        AcrescentaNovaOcorrencia(palavra ,numLinha,ind->qtdArquivos);//nova ocorrência independente de ser a primeira vez da palavra ou não

        pal = strtok(NULL," ");
    }
}

///processa um arquivo texto
void ProcessarArquivo(Indice *ind, char *nomeArq){
    if (BuscarArquivo(ind->arquivos,nomeArq)){
        printf("Arquivo <%s> ja foi processado!\n",nomeArq);
        return;
    }

    InserirArquivoFim(ind->arquivos,nomeArq);
    ind->qtdArquivos++;

    FILE *arq = fopen(nomeArq,"r");
    if (arq==NULL){
        printf("Arquivo <%s> nao pode ser lido!",nomeArq);
        return;
    }

    int contLinha=1;
    char linha[1000];
    while(fscanf(arq," %[^\n]s",linha)>0){//lê a linha inteira (infelizmente tem que ter um espaço em branco no começo para funcionar no Windows 10)
        ProcessarLinha(ind,linha,contLinha++);
    }
    fclose(arq);
}
