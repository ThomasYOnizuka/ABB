// arvore.c - implementação de árvore binária

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "arvore.h"

NO *pai(NO *raiz, NO *noI) {

    if( raiz == noI ) return NULL;

    if( raiz->valor > noI->valor ) {    // está para o lado esquerdo
        if( noI == raiz->esq )          // raiz é pai do noI
            return raiz;
        return pai( raiz->esq, noI );
    }
    else {                             // está para o lado  direito
        if( noI == raiz->dir )
            return raiz;
        return pai( raiz->dir, noI);
    }
}

NO *criaNo(int val) {
    NO *novoNo;

    novoNo = malloc( sizeof(NO));
    if(!novoNo) {
        printf("Erro de alocação de memória.\n");
        exit(-1);
    }
    novoNo->valor = val;
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    return novoNo;
}



NO *insereNo(NO *raiz, int val ) {

    int fb;

    if( raiz==NULL) {
       return criaNo(val);
    }
    if( val > raiz->valor )    // maior
        raiz->dir = insereNo( raiz->dir, val);
    else if (val < raiz->valor) {
        raiz->esq = insereNo( raiz->esq, val);
    }
    else return raiz;      // Chave duplicada não permitida

    fb = FB(raiz);

    if( fb>1 ) {
        if ( FB(raiz->dir) >= 0)
            raiz = rotacaoEsquerda(raiz);
        else
            raiz = rotacaoDuplaEsquerda(raiz);
    }
    if( fb<-1 ){
        if ( FB(raiz->esq) >= 0)
            raiz = rotacaoDireita(raiz);
        else
            raiz = rotacaoDuplaDireita(raiz);

    }

    return raiz;
}

NO *ehAVL( NO *raiz ) {
    int fb;
    NO *p;
    if(raiz==NULL) return NULL;
    fb = FB(raiz);
    if(fb>1 || fb<-1)
        return raiz;
    p = ehAVL( raiz->esq);
    if(p) return p;
    p = ehAVL(raiz->dir);
    if(p) return p;
    return NULL;
}   

NO *proximo(NO *raiz, NO *no) {
    NO *p;

    if(no->dir != NULL) {
        p = no->dir;
        while( p->esq != NULL )
            p = p->esq;
        return p;
    }

    p = pai(raiz, no);
    while(p != NULL && p->dir == no )
        no = p;
        p = (raiz, p );
    return p;
}

void imprimeERD(NO *raiz) {
    if(raiz!=NULL) {
        imprimeERD( raiz->esq );
        printf("%d\n",raiz->valor);
        imprimeERD( raiz->dir );
    }
}

void imprimeDRE(NO *raiz) {
    if(raiz!=NULL) {  
        imprimeDRE( raiz->dir );
        printf("%d\n",raiz->valor);
        imprimeDRE( raiz->esq );
    }
}

int altura(NO *no) {
    int aEsq, aDir;

    if( no==NULL )
        return -1;    
    aEsq = altura(no->esq);
    aDir = altura(no->dir);

    if(aEsq>aDir) 
        return aEsq+1;
    else
        return aDir+1;
}

int FB(NO *no) {  // Fator de Balanceamento
    if(!no) return 0;
    return altura( no->dir ) - altura( no->esq );
}

NO *rotacaoDireita( NO *raiz ){
    NO *novaRaiz;
    novaRaiz = raiz->esq;
    raiz->esq = novaRaiz->dir;
    novaRaiz->dir = raiz;
    return novaRaiz;
}
NO *rotacaoEsquerda( NO *raiz ){
    NO *novaRaiz;
    novaRaiz = raiz->dir;
    raiz->dir = novaRaiz->esq;
    novaRaiz->esq = raiz;
    return novaRaiz;
}
NO *rotacaoDuplaDireita( NO *raiz ) {
    raiz->esq = rotacaoEsquerda( raiz->esq );
    return rotacaoDireita( raiz );
}
NO *rotacaoDuplaEsquerda( NO *raiz ) {
    raiz->dir = rotacaoDireita( raiz->dir );
    return rotacaoEsquerda( raiz );
}
int profundidade(NO *raiz, NO *noI) {
    if(raiz==NULL) return -1;
    if( raiz->valor == noI->valor )
        return 0;
    if( raiz->valor > noI->valor )
        return profundidade( raiz->esq, noI) + 1;
    else
        return profundidade( raiz->dir, noI) + 1;
}

NO *removeNo( NO *raiz ) {
    NO *p, *q;

    if( raiz->esq==NULL) q=raiz->dir;
    else {
        p = raiz;
        q = raiz->esq;
        while( q->dir!=NULL ){
            p = q;
            q = q->dir;
        }
        if( p!= raiz) {
            p->dir = q->esq;
            q->esq = raiz->esq;
        }
        q->dir = raiz->dir;
    }
    free(raiz);
    return q;
}

void removeNoVal(NO **raiz, int valor) {
    NO *s, *p;
    
    s = busca(*raiz, valor);
    
    if( s==*raiz ){
        *raiz = removeNo(s);
    }
    else {
        p = pai(*raiz, s);
        if( s ==  p->esq){
            p->esq = removeNo(p->esq);
        }
        else   {
            p->dir  = removeNo(p->dir);
        }
    }
}

NO *busca( NO *no, int val ){
    if( no==NULL || no->valor == val ) 
        return no;
    if( no->valor > val )
        return busca( no->esq, val );
    else   
        return busca( no->dir, val );
}

void imprimeNivel(NO *raiz, int alturaDesejada, int alturaCorrente){
    if(raiz==NULL) return;

    if( alturaDesejada == alturaCorrente) {
        printf("%d ", raiz->valor);
        return;
    }   
    imprimeNivel(raiz->esq, alturaDesejada, alturaCorrente+1 );
    imprimeNivel(raiz->dir, alturaDesejada, alturaCorrente+1 );
}

void imprimeIrmaos(NO *raiz, NO *noI){
    int p;
    p = profundidade(raiz,noI);
    imprimeNivel(raiz, p, 0);
}


int main() {
    NO *raiz = NULL;  // árvore vazia
    NO *s,*t;

    // raiz = insereNo(raiz, 6);
    // raiz = insereNo(raiz, 7);
    // raiz = insereNo(raiz, 9);
    // raiz = insereNo(raiz, 12);
    // raiz = insereNo(raiz, 2);
    // raiz = insereNo(raiz, 15);
    // raiz = insereNo(raiz, 1); 
    // raiz = insereNo(raiz, 14);
    // raiz = insereNo(raiz, 8);
    // raiz = insereNo(raiz, 3);
    // raiz = insereNo(raiz, 4);
    // raiz = insereNo(raiz, 11);
    // raiz = insereNo(raiz, 10);
    // raiz = insereNo(raiz, 13);
    // raiz = insereNo(raiz, 5);

    raiz = insereNo(raiz, 1);
    raiz = insereNo(raiz, 2);
    raiz = insereNo(raiz, 3);
    raiz = insereNo(raiz, 4);
    raiz = insereNo(raiz, 5);
    raiz = insereNo(raiz, 6);
    raiz = insereNo(raiz, 7);
    raiz = insereNo(raiz, 8);
    raiz = insereNo(raiz, 9);
    raiz = insereNo(raiz, 10);
    raiz = insereNo(raiz, 11);


    s = ehAVL(raiz);
    if(s) {
        printf("Nó %d  FB: %d", s->valor, FB(s));
    }
    printf("\nAltura da árvore: %d\n\n", altura(raiz));
}

    return 0;
}
