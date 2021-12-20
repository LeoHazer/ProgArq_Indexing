#ifndef Trab1_h
#define Trab1_h
#include <string.h>

// Struct Ocorrencia Ocorrencia
typedef struct Ocorrencia Ocorrencia;

// Struct Palavra Palavra
typedef struct Palavra Palavra;

// Struct Arquivo
typedef struct Arquivo Arquivo;

// Struct elemento
typedef struct elemento elemento;

// Struct Indice
typedef struct Indice Indice;

// Struct elemento
typedef struct elemento elemento;



// Criando Lista
elemento *CriaLista();

// Verifica Existência de um elemento na lista
elemento *Existe(elemento *lista, char word[]);

//Procura Palavra na Lista
elemento *buscaPalavra(elemento *lista, char *bPalavra);

// Adciona linha nas ocorrencias
void criaLinha(elemento *tmp, int addLinha);

// Mostra a ocorrência de uma palavra
void mostraOcorrencia(Palavra plvr);

// Listando Palavras do índice
void Listar(elemento *lista);

void DestruirLista(elemento *lista);
void destroiIndice(elemento *lst);

// Colocando em Ordem alfabética
void ordemAlfabetica(elemento *lst, Palavra plvr);

// Inserindo no Fim da Lista
void insereFim(elemento *lst, Palavra plvr);

#endif // Trab1_h
