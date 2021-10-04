#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo {
 int num;
 struct nodo *izq;
 struct nodo *der;
};

struct nodo* r = NULL;

struct nodo* nuevoNodo(int num) {
  struct nodo* n = malloc(sizeof(struct nodo));
  n->num = num;
  n->der = NULL;
  n->izq = NULL;

  return n;
}

void insertar(int num){
  struct nodo* actual = r;
  struct nodo* anterior;
  while(actual){
    if(actual->num == num){
      return;
    }
    if(actual->num < num){
      anterior = actual;
      actual = actual-> der;
    } else {
      anterior = actual;
      actual = actual-> izq;
    }
  }
  actual = nuevoNodo(num);
  if(r == NULL){
    r = actual;
  } else {
    if(anterior->num < num){
      anterior->der = actual;
    } else {
      anterior->izq = actual;
    }
  }
}

void arbolLatexAux(struct nodo* actual, char arbol[110]){
  if (actual == NULL){
    return;
  }
  strcat(arbol, "{");
  strcat(arbol, "\"$");
  char numeroInt[2];
  sprintf(numeroInt, "%c", 'A'+actual->num-1);
  strcat(arbol, numeroInt);
  strcat(arbol, "$\"");
  if(actual->izq || actual->der){
    strcat(arbol, "->{");
  }
  arbolLatexAux(actual->izq, arbol);
  if(actual->der){
    strcat(arbol, ",");
  }
  arbolLatexAux(actual->der, arbol);
  strcat(arbol, "}");
  if(actual->izq || actual->der){
    strcat(arbol, "}");
  }
}

void arbolLatex(char arbol[110]){
  struct nodo* actual = r;
  arbolLatexAux(actual, arbol);
}

void borrarArbolAux(struct nodo* actual){
    if (actual == NULL) return;
    borrarArbolAux(actual->izq);
    borrarArbolAux(actual->der);
    free(actual);
}

void borrarArbol(){
  struct nodo* actual = r;
  borrarArbolAux(actual);
  r = NULL;
}