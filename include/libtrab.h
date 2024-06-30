#ifndef __LIBTRAB_H__
#define __LIBTRAB_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define TAM 16811

typedef struct _item{
    char nome[MAX];
    double latitude;
    double longitude;
    int codigo_uf;
    int ddd;
    int codigo_ibge;
    int tipo;
    struct _item *prox;
}titem;

typedef struct _cidade{
    int codigo_ibge;
    char nome[MAX];
    double latitude;
    double longitude;
    int capital;
    int codigo_uf;
    int siafi_id;
    int ddd;
    char fuso_horario[MAX];
}tcidade;

typedef struct _hash{
    tcidade *cidades;
    int tamanho; // 16811 por ser primo
    int atual;
}thash;

typedef struct _avl{
	titem *item;

    struct _avl *pai;
	struct _avl *esq;
	struct _avl *dir;
	int h;
}tavl;

typedef struct _raiz{
    tavl *raiz;
}traiz;

typedef struct _resultado{
    int codigo;
    int quant;
    struct _resultado *prox;
}tresultado;

//arquivo main.c
void lerArquivo(FILE* arquivo, thash* hash ,traiz* avl_nome, traiz* avl_lat, traiz* avl_long, traiz* avl_uf, traiz* avl_ddd);
void interface(thash *hash_cod, traiz *avl_nome, traiz *avl_lat, traiz *avl_long, traiz *avl_uf, traiz *avl_ddd);

//arquivo hash.c
int h1(int codigo_ibge, int tamanho);
int h2(int codigo_ibge, int tamanho);
tcidade buscaIBGE(thash *hash, int codigo_ibge);
thash* criarHash(int tamanho);
void insereHash(thash *hash, tcidade cidade);
void liberaHash(thash *hash);

//arquivo avl.c
int compara(titem *a, titem *b);
void _re(tavl ** parv);
void _rd(tavl ** parv);
void _avl_rebalancear(tavl ** parv);
void _avl_insere(traiz * praiz, tavl ** parv, titem *item);
void avl_insere(traiz * parv, titem *item);
tavl ** procura_sucessor(tavl ** arv);
void avl_destroi(tavl *parv);

//arquivo listaEncadeada.c
void insereLista(titem **lista, titem *item);
void destroiLista(titem **lista);
void insereListaRes(tresultado **lista, int codigo);

//arquivo rangeQuery.c
tavl * buscaMenor(tavl ** avl, titem *itemMenor);
void retornaIntervalo(tavl ** avl, titem *itemMaior, tresultado ** res);


#endif