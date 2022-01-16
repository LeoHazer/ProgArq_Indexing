#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lista_arquivos.h"
#include "lista_palavras.h"
#define NOME_ARQ_INDICE "indice.dat"

typedef struct indice{
    int qtdArquivos;
    Arquivo *arquivos;
    int qtdPalavras;
    Palavra *iniciais[26];
}Indice;

///criaum indice vazio
Indice CriarIndice(){
    Indice resp;
    resp.qtdArquivos = 0;
    resp.arquivos = CriarListaArquivos();
    resp.qtdPalavras = 0;
    for(int i=0;i<26;i++)
        resp.iniciais[i] = CriarListaPalavras();
    return resp;
}

///destroi o indice (de fato, destroi apenas as listas)
void DestruirIndice(Indice *ind){
    ind->qtdArquivos = 0;
    ind->arquivos = DestruirListaArquivos(ind->arquivos);

    ind->qtdPalavras = 0;
    //ind->palavras = DestruirListaPalavras(ind->palavras);//trocar pra iniciais
}

///lê um indice de um arquivo binário
Indice LerIndice(){
    Indice resp = CriarIndice();

    FILE *arq = fopen(NOME_ARQ_INDICE,"rb");

    fread(&resp.qtdArquivos,sizeof(int),1,arq);
    LerArquivos(resp.arquivos,resp.qtdArquivos,arq);
    printf("O indice lido tem %d arquivos\n",resp.qtdArquivos);

    fread(&resp.qtdPalavras,sizeof(int),1,arq);
    //LerPalavras(resp.palavras,resp.qtdPalavras,arq); // mexer
    printf("O indice lido tem %d palavras\n",resp.qtdPalavras);

    fclose(arq);

    return resp;
}

///salva um indice num arquivo binario
void SalvarIndice(Indice ind){
    FILE *arq = fopen(NOME_ARQ_INDICE,"wb");

    fwrite(&ind.qtdArquivos,sizeof(int),1,arq);
    SalvarArquivos(ind.arquivos,arq);

    fwrite(&ind.qtdPalavras,sizeof(int),1,arq);
    //SalvarPalavras(ind.palavras,arq);//mexer

    fclose(arq);
}


///mostra as informações do indice na tela
void MostrarIndice(Indice ind){
    printf("\n%d Arquivos no indice:\n",ind.qtdArquivos);
    MostrarArquivos(ind.arquivos);
    printf("\n%d Palavras no indice:\n",ind.qtdPalavras);
    //MostrarPalavras(ind.palavras);// mexer
    printf("\n");
}


///processa uma linha de um arquivo texto//Alterar
void ProcessarLinha(Indice *ind, char *linha, int numLinha){
    char *pal = strtok(linha," ");
    while (pal){
        //Palavra *palavra = BuscarPalavra(ind->palavras,pal); mexer

        // if (palavra==NULL){//palavra nao encontrada (primeiraocorrencia no indice)
        //     palavra = InserirPalavraOrdem(ind->palavras,pal);
        //     ind->qtdPalavras++;
        // }

        //AcrescentaNovaOcorrencia(palavra,numLinha,ind->qtdArquivos);//nova ocorrência independente de ser a primeira vez da palavra ou não

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

