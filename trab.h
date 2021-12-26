#ifndef Trab_h
#define Trab_h
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Ocorrencia{
    int arquivo; //Posição do arquivo na lista de arquivos processados
    int qtdOcorrencias; // Qtd de vezes em que a palavra foi encontrada
    int *linhas; // Linhas onde a palavra foi encontrada
    struct Ocorrencia *prox; // Próxima Ocorrência 
}Ocorrencia;

typedef struct Palavra{
    char letras[50]; //a palavra em questão
    int qtdOcorrencias; //quantidade de arquivos que possuem a palavra
    Ocorrencia *ocorrencias; //lista contendo informações da ocorrência de uma palavra em um arquivo

    struct Palavra *prox;// próxima palavra encontrada em ordem alfabética)

}Palavra;

typedef struct Arquivo{
    char nomeArquivo[50]; //nome de um arquivo texto já processado
    struct Arquivo *prox; //ponteiro para o nome do próximo arquivo texto
}Arquivo;

typedef struct Indice{
    int qtdArquivos; //quantidade de arquivos de texto lidos até então
    Arquivo *arquivos; //lista contendo os nomes dos arquivos texto já processados
    int qtdPalavras;
    Palavra *palavras;//lista contendo todas as palavras já encontrada
}Indice;

Indice *CriaIndice(){
    Indice *ind=(Indice *) malloc(sizeof(Indice));
    ind->arquivos=NULL;
    ind->palavras=NULL;
    ind->qtdArquivos=0;
    ind->qtdPalavras=0;
}


Arquivo *CriaElementoArquivo(char *NomeArq){
    Arquivo *arq=(Arquivo *) malloc(sizeof(Arquivo));
    strcpy(arq->nomeArquivo,NomeArq);
    arq->prox=NULL;
    return arq;
}

void InsereArquivo(Arquivo *arq,char *NomeArq){
    if(arq!=NULL) InsereArquivo(arq->prox,NomeArq);
    else arq=CriaElementoArquivo(NomeArq);
}

int ArquivoLido(Arquivo *arq, char *NameArq){
    if(arq==NULL) return 0;
    if(strcmp(arq->nomeArquivo,arq)==1) return 1;
    return ArquivoLido(arq->prox, NameArq);
}

int* realocaLinOcorr(int* ptr, int* size, int t){
    int count,add;
    
    printf("Deseja adicionar quantas ocorrências ao arquivo %d: ",t);
    scanf("%d", &add);
    
    ptr = (int *) realloc(ptr, (*size + add)*sizeof(int) );
    if(ptr){
    
        for(count=0 ; count < add ; count++){
            printf("Numero [%d]: ",count+1);
            scanf("%d", &ptr[*size + count]);
        }
        *size += add;
    }else{
        printf("Espaço em memória insuficiente\n");
        free(ptr);
        exit(1);
    }
    return ptr;
}

void exibe(int* ptr, int size)
{
    int count;
    for(count=0 ; count<size ; count++)
    printf("%3d", ptr[count]);
  
}

int ExistePalavra(Palavra *palavra, char *word){
    if(palavra==NULL) return 0;
    if(strcmp(palavra->letras,word)) return 1;
    ExistePalavra(palavra->prox,word);
}

Ocorrencia *CriaOcorr(){
    Ocorrencia *ocorr=(Ocorrencia *) malloc(sizeof(Ocorrencia));
    ocorr->arquivo=0;
    ocorr->qtdOcorrencias=0;
    ocorr->linhas=NULL;
    ocorr->prox=NULL;
    return ocorr;
}

Ocorrencia *InsereOcorr(Ocorrencia *ocorr, int arq)
{
  Ocorrencia *p;
  p =  (Ocorrencia *) malloc(sizeof(Ocorrencia));
  p->arquivo=arq;
  //p->qtdOcorrencias=ocorr->qtdOcorrencias+1;
  p->linhas = realocaLinOcorr(p->linhas, &p->qtdOcorrencias, 2);
  p->prox=NULL;

  if(p==NULL){
    printf("Erro de alocação");
  }else{
    p->prox = ocorr;
    ocorr=p;    
  }
  return ocorr;
}

Ocorrencia *InsereOcorrencia(Ocorrencia *ocorr, int arq)
{
  Ocorrencia *p;
  p =  (Ocorrencia *) malloc(sizeof(Ocorrencia));
  p->arquivo=arq;
  //p->qtdOcorrencias=ocorr->qtdOcorrencias+1;
  p->linhas = realocaLinOcorr(p->linhas, &p->qtdOcorrencias, arq);
  p->prox=NULL;

  if(p==NULL){
    printf("Erro de alocação");
  }else{
    p->prox = ocorr;
    ocorr=p;    
  }
  return ocorr;
}

void ImprimeOcorr(Ocorrencia *arq, int qtdArqvs){
  Ocorrencia *ptr;
  if (arq == NULL)
  {
    printf("--- fim da lista1 ---\n\n");
    //return;
  }
  // Caso a lista nao esteja vazia
  ptr = arq;
  printf("\nIndice do orquivo: %d\n",ptr->arquivo);
  printf("Total de ocorrências no orquivo: %d\n",ptr->qtdOcorrencias);
  //printf("Nas seguintes linhas: \n");

  ///*
  int i=0;
  while (i < qtdArqvs) {
     printf("Ocorrências no orquivo: ");
     exibe(ptr->linhas, ptr->qtdOcorrencias);
     ptr = ptr->prox;
     i+=1;
  }
  //*/
  printf("\n\n");
}


Palavra *CriaPalavra(){
    Palavra *palavra=(Palavra *) malloc(sizeof(Palavra));
    strcpy(palavra->letras, "");
    palavra->prox=NULL;
    palavra->qtdOcorrencias=0;
    palavra->ocorrencias = CriaOcorr();
    return palavra;
}

Palavra *InserePalavra(Palavra *structPalavra, char* palavra){
    Palavra *p;
    p =  (Palavra *) malloc(sizeof(Palavra));

    if(ExistePalavra(structPalavra,palavra)==0){//Verificando se a palavra já existe
        //Se não existir retorna NULL
        strcpy(p->letras, palavra);
        p->qtdOcorrencias+=1;
        p->prox=NULL;

        if(p==NULL){
            printf("Erro de alocação");
        }else{
            p->prox = structPalavra;
            structPalavra=p;    
        }
        structPalavra->ocorrencias=InsereOcorr(structPalavra->ocorrencias, 1);
    }else{//Se existir já retorna o ponteiro equivalente a essa palavra
        p=structPalavra;
        while(!strcmp(p->letras,palavra)){
            p=p->prox;
        }
        p->qtdOcorrencias++;//Incremento de Ocorrencia
        p->ocorrencias=InsereOcorr(p->ocorrencias,1);// Adicionando ocorrencia
    }
    return structPalavra;
}

void ImprimePalavras(Palavra *arq){
    Palavra *ptr;
    if (arq == NULL){
        printf("\n--- fim da lista de palavras---\n\n");
        //return;
    }
    // Caso a lista nao esteja vazia
    ptr = arq;
    int i=0;
    while (ptr != NULL) {
        printf("palavra = %s\n",ptr->letras);
        ImprimeOcorr(ptr->ocorrencias, 1);
        ptr = ptr->prox;
        i+=1;
    }
    printf("\n\n");
}

// Arquivo *InsereArquivo(Arquivo *arq, char* nomeArq)
// {
//   Arquivo *p;
//   p =  (Arquivo *) malloc(sizeof(Arquivo));
//   strcpy(p->nomeArquivo, nomeArq);
//   p->prox=NULL;

//   if(p==NULL){
//     printf("Erro de alocação");
//   }else{
//     p->prox = arq;
//     arq=p;    
    
//   }
//   return arq;
// }

void ImprimeArq(Arquivo *arq){
    Arquivo *ptr;
    if (arq == NULL){
        printf("--- fim da lista1 ---\n\n");
        //return;
    }
    // Caso a lista nao esteja vazia
    ptr = arq;
    int i=0;
    while (ptr != NULL) {
        printf("Info = %s\n",ptr->nomeArquivo);
        ptr = ptr->prox;
        i+=1;
    }
    printf("\n--- fim da lista de arquivos---\n\n\n");
}

void ImprimeIndice(Indice *indice){
    printf("\nlISTA DE ARQUIVOS: \n\n");
    ImprimeArq(indice->arquivos);
    printf("\nLISTA DE PALAVRAS: \n\n");
    ImprimePalavras(indice->palavras);
    printf("--- fim da lista de palavras---\n\n");
}

void LerPalavrasArquivo(Palavra *palavra, char *NameArq){//Precisa fazer adicionar em ordem alfabética
    FILE *arq=fopen(NameArq,"rt");
    if(arq!=NULL){
        char word[1000];
        while(fread(word,sizeof(char),1,arq)==1){
            InserePalavra(palavra,word);
        }
    }
}

void SalvaIndice(Indice *ind){
    FILE *indice=fopen("indice.dat","wb");
    fprintf(indice,"%d",&ind->qtdArquivos);//Imprimindo quantidade de arquivos que foram abertos

    Arquivo *arq=ind->arquivos;

    while(arq!=NULL){//Percorrendo todos os arquivos do indice
        fprintf(indice,"%d",strlen(arq->nomeArquivo)+1);//Imprimindo no arquivo o tamanho do nome do arquivo
        fprintf(indice,"%s\0",arq->nomeArquivo);//Imprimindo o nome do arquivo com \0
        arq=arq->prox;
    }

    fprintf(indice,"%d",&ind->qtdPalavras);//Imprimindo quantidade de palavras encontradas
    Palavra *plv=ind->palavras;
    while(plv!=NULL){//Percorrendo todas as palavras no indice
        fprinf(indice,"%d",strlen(plv->letras)+1);//Imprimindo o tamanho da palavra +1
        fprintf(indice, "%s\0", plv->letras);//Imprimindo a palacvra
        fprintf(indice, "%d", plv->qtdOcorrencias);//Imprimindo quantidade de ocorrencias

        Ocorrencia *ocr=plv->ocorrencias;
        while(ocr!=NULL){//Percorrendo todas as ocorrencias da palavra
            fprintf(indice,"%d",ocr->arquivo);//Printando o numero do arquivo da ocorrencia
            fprintf(indice,"%d",ocr->qtdOcorrencias);//Quantidade de ocorrencias nesse mesmo arquivo

            for(int i=0;i<ocr->qtdOcorrencias;i++){
                fprintf(indice,"%d",ocr->linhas[i]);//Printando o números das linhas em que houve a ocorrencia
            }
            ocr=ocr->prox;
        }
        plv=plv->prox;
    }
    fclose(indice);
}

void DestruirArquivos(Arquivo *arq){
    if(arq==NULL) return;

    Arquivo *aux;
    while(arq!=NULL){
        aux=arq;
        arq=arq->prox;
        free(aux);
    }
}

void DestruirPalavras(Palavra *plv){
    if(plv==NULL) return;

    Palavra *aux;
    while(plv!=NULL){
        aux=plv;
        plv=plv->prox;
        free(aux);
    }
}

Indice *DestruirIndice(Indice *ind){
    DestruirArquivos(ind->arquivos);
    DestruirPalavras(ind->palavras);
    free(ind);
    return NULL;
}

void LerIndice(Indice *ind){
    FILE *idc=fopen("indice.dat","rb");
    fscanf(idc,"%d",&ind->qtdArquivos);

    Arquivo *arq=ind->arquivos;

    for(int i=0;i<ind->qtdArquivos;i++){
        arq=(Arquivo *) malloc(sizeof(Arquivo));
        arq->prox=NULL;
        int aux;
        fscanf(idc,"%d",&aux);
        fread(arq->nomeArquivo,sizeof(char),aux,idc);
        arq=arq->prox;
    }

    Palavra *plv=ind->palavras;

    fscanf(idc,"%d",&ind->qtdPalavras);

    for(int i=0;i<ind->qtdPalavras;i++){
        plv=CriaPalavra();
        int aux;
        fscanf(idc,"%d",&aux);
        fread(plv->letras,sizeof(char),aux,idc);
        fscanf(idc,"%d",&plv->qtdOcorrencias);
        Ocorrencia *ocr=plv->ocorrencias;
        for(int j=0;j<plv->qtdOcorrencias;j++){
            if(j>0) ocr=CriaOcorr();
            fscanf(idc,"%d",&ocr->arquivo);
            fscanf(idc,"%d",&ocr->qtdOcorrencias);
            for(int k=0;k<ocr->qtdOcorrencias;k++){
                fscanf(idc,"%d",ocr->linhas[k]);
            }
            ocr=ocr->prox;
        }
        plv=plv->prox;
    }
}

#endif // Trab1_h
