#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/libtrab.h"

int max(int a, int b){
	return a>b?a:b;
}

int altura(tavl *arv){
	if(arv == NULL){
		return -1;
	}
	else{
		return arv->h;
	}
}

int compara(titem *a, titem *b){
    double fc;
    int c = a->tipo;
    //printf("%s", a->nome);
    //printf("%s", b->nome);
    switch(c){
        case 1:
            return strcmp(a->nome, b->nome);
            break;
        case 2:
            fc = a->latitude - b->latitude;
            if(fc > 0){
                return 1;
            }
            else if(fc < 0){
                return -1;
            }
            else{
                return 0;
            }
            break;
        case 3:
            fc = a->longitude - b->longitude;
            if(fc > 0){
                return 1;
            }
            else if(fc < 0){
                return -1;
            }
            else{
                return 0;
            }
            break;
        case 4:
            return a->codigo_uf - b->codigo_uf;
            break;
        case 5:
            return a->ddd - b->ddd;
            break;
    }
}

void _re(tavl ** parv){
	tavl * x = *parv;
	tavl * y = x->dir;
	tavl * a = x->esq;
	tavl * b = y->esq;
	tavl * c = y->dir;

    y->pai = x->pai;
	x->dir = b;
    if(b != NULL)
        b->pai = x;
	y->esq = x;
    x->pai = y;
	*parv = y;
	x->h = max(altura(a), altura(b)) + 1;
	y->h = max(altura(x), altura(c)) + 1;
}

void _rd(tavl ** parv){
	tavl * y = *parv;
	tavl * x = y->esq;
	tavl * a = x->esq;
	tavl * b = x->dir;
	tavl * c = y->dir;

    x->pai = y->pai;
	y->esq = b;
    if(b != NULL)
        b->pai = y;
	x->dir = y;
    y->pai = x;
	*parv = x;
	y->h = max(altura(b), altura(c)) + 1;
	x->h = max(altura(a), altura(y)) + 1;
}

void _avl_rebalancear(tavl ** parv){
	int fb;
	int fbf;
	tavl *filho;
	fb = altura((*parv)->esq) - altura((*parv)->dir);
	if(fb == -2){
		filho = (*parv)->dir;
		fbf = altura(filho->esq) - altura(filho->dir);
		if(fbf <= 0){
			_re(parv);
		}
		else{
			_rd(&(*parv)->dir);
			_re(parv);
		}
	}
	else if(fb == 2){
		filho = (*parv)->esq;
		fbf = altura(filho->esq) - altura(filho->dir);
		if(fbf >= 0){
			_rd(parv);
		}
		else{
			_re(&(*parv)->esq);
			_rd(parv);
		}
	}
}

void _avl_insere(traiz * praiz, tavl ** parv, titem *item){
    if(*parv == NULL){
        (*parv) = (tavl *)malloc(sizeof(tavl));
        (*parv)->item = NULL;
		insereLista(&(*parv)->item, item);
        (*parv)->pai = NULL;
        (*parv)->esq = NULL;
        (*parv)->dir = NULL;
        (*parv)->h = 0;
	}
	else{
        int cmp = compara((*parv)->item, item);
        if(cmp > 0){
            if((*parv)->esq == NULL){
                (*parv)->esq = (tavl *)malloc(sizeof(tavl));
                (*parv)->esq->item = NULL;
                insereLista(&(*parv)->esq->item, item);
                (*parv)->esq->pai = *parv;
                (*parv)->esq->esq = NULL;
                (*parv)->esq->dir = NULL;
                (*parv)->esq->h = 0;
            }
            else{
                _avl_insere(praiz, &(*parv)->esq, item);
            }
        }
        else if(cmp < 0){
            if((*parv)->dir == NULL){
                (*parv)->dir = (tavl *)malloc(sizeof(tavl));
                (*parv)->dir->item = NULL;
                insereLista(&(*parv)->dir->item, item);
                (*parv)->dir->pai = *parv;
                (*parv)->dir->esq = NULL;
                (*parv)->dir->dir = NULL;
                (*parv)->dir->h = 0;
            }
            else{
                _avl_insere(praiz, &(*parv)->dir, item);
            }
        }
        else{
            insereLista(&(*parv)->item, item);
        }
    }
	(*parv)->h = max(altura((*parv)->esq), altura((*parv)->dir)) + 1;
	_avl_rebalancear(parv);
    // talvez tenha que fazer balanceamento pros 2 lados
}

void avl_insere(traiz *parv, titem *item){
    _avl_insere(parv, &parv->raiz, item);
}

tavl ** percorre_esq(tavl ** parv){
	tavl * aux = *parv;
	if(aux->esq == NULL){
		return parv;
	}
	else{
		while (aux->esq->esq != NULL)
            aux = aux->esq;
        return &(aux->esq);
	}
}

tavl ** procura_sucessor(tavl ** arv){
    tavl * aux = *arv;
    if(aux->dir != NULL){
        return percorre_esq(&aux->dir);
    }
    else{
        tavl * aux2 = aux->pai;
        while(aux2 != NULL && aux == aux2->dir){
            aux = aux2;
            aux2 = aux2->pai;
        }
        if (aux2 == NULL){
            return NULL;
        }
        return &(aux->pai);
    }
}

// void avl_remove(tavl ** parv, titem reg){
// 	int cmp;
// 	tavl *aux;
// 	tavl ** sucessor;
// 	if(*parv != NULL){
// 		cmp = (*parv)->item.item - reg.item;
// 		if(cmp > 0){
// 			avl_remove(&(*parv)->esq, reg);
// 		}
// 		else if(cmp < 0){
// 			avl_remove(&(*parv)->dir, reg);
// 		}
// 		else{
// 			if((*parv)->esq == NULL && (*parv)->dir == NULL){
// 				free(*parv);
// 				*parv = NULL;
// 			}
// 			else if((*parv)->esq == NULL || (*parv)->dir == NULL){
// 				aux = *parv;
// 				if((*parv)->esq == NULL){
// 					*parv = (*parv)->dir;
// 				}
// 				else{
// 					*parv = (*parv)->esq;
// 				}
// 				free(aux);
// 			}
// 			else{
// 				sucessor = percorre_esq(&(*parv)->dir);
// 				(*parv)->item = (*sucessor)->item;
// 				avl_remove(&(*parv)->dir, (*sucessor)->item);
// 			}
// 		}
// 		if(*parv != NULL){
// 			(*parv)->h = max(altura((*parv)->esq), altura((*parv)->dir)) + 1;
// 			_avl_rebalancear(parv);
// 		}
// 	}
// }

void avl_destroi(tavl *parv){
	if(parv != NULL){
		avl_destroi(parv->esq);
		avl_destroi(parv->dir);
        destroiLista(&(parv->item));
		free(parv);
	}
}