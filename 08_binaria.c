#include <stdio.h>

#include <stdlib.h>

typedef struct arvore {
  int info;
  struct arvore * esq;
  struct arvore * dir;
}
Arvore;

Arvore * cria_arv_vazia(void) {
  return NULL;
}

void padding(char ch, int n) {
  int i;
  for (i = 0; i < n; i++)
    putchar(ch);
}

Arvore * arv_constroi(int c, Arvore * e, Arvore * d) {
  Arvore * a = (Arvore * ) malloc(sizeof(Arvore));
  a -> info = c;
  a -> esq = e;
  a -> dir = d;
  return a;
}

int verifica_arv_vazia(Arvore * a) {
  return (a == NULL);
}

Arvore * arv_libera(Arvore * a) {
  if (!verifica_arv_vazia(a)) {
    arv_libera(a -> esq);
    arv_libera(a -> dir);
    free(a);
  }
  return NULL;
}

void structure_in_ordem(Arvore * root, int level) {
  if (root != NULL) {
    structure_in_ordem(root -> esq, level + 1);
    printf("%d\t ", root -> info, level);
    structure_in_ordem(root -> dir, level + 1);
  }
}

Arvore * insert(Arvore * a, int num) {
  if (a == NULL) {
    printf("\nInserindo %d  ", num);
    return arv_constroi(num, cria_arv_vazia(), cria_arv_vazia());
  }

  if (num < a -> info)
    a -> esq = insert(a -> esq, num);
  else if (num > a -> info)
    a -> dir = insert(a -> dir, num);

  return a;
}

Arvore * busca_binaria(Arvore * r, int k) {
  if (r == NULL || r -> info == k)
    return r;
  if (r -> info > k)
    return busca_binaria(r -> esq, k);
  else
    return busca_binaria(r -> dir, k);
}

Arvore * remove_raiz(Arvore * r) {
  Arvore * p, * q;
  if (r -> esq == NULL) {
    q = r -> dir;
    free(r);
    return q;
  }
  p = r;
  q = r -> esq;
  while (q -> dir != NULL) {
    p = q;
    q = q -> dir;
  }

  if (p != r) {
    p -> dir = q -> esq;
    q -> esq = r -> esq;
  }
  q -> dir = r -> dir;
  free(r);
  return q;
}

int min_arvore(Arvore * a) {
  if (a == NULL)
    return 0;
  int res = a -> info;
  int aux = min_arvore(a -> esq);
  if (aux <= res) {
    res = aux;
  }
  return res;
}

int max_arvore(Arvore * a) {
  if (a == NULL)
    return 0;
  int res = a -> info;
  int aux = max_arvore(a -> dir);
  if (aux >= res) {
    res = aux;
  }
  return res;
}

int arv_bin_check(Arvore * a) {
  if (a == NULL)
    return 1;

  if (a -> esq != NULL && max_arvore(a -> esq) > a -> info)
    return 0;

  if (a -> dir != NULL && min_arvore(a -> dir) < a -> info)
    return 0;

  return 1;
}

int main(int argc, char * argv[]) {
  Arvore * a, * a1;
  a = cria_arv_vazia();

  int aux;

  int arr[1000], i;

  //  for (i = 0; i < 10000; i++){
  //  	int random = rand() % 10000;
  //  a =insert (a, random);
  //}
  //   structureInOrdem(a,0);

  for (i = 0; i < 1000; i++) {
    a = insert(a, i);
  }

  structure_in_ordem(a, 0);

  aux = max_arvore(a);
  printf("\n \n Maior %d", aux);

  aux = min_arvore(a);
  printf("\n \n Menor %d", aux);

  a1 = busca_binaria(a, 999);
  printf("\n\n Encontrado: %d", a1 -> info);
  
  aux = arv_bin_check(a);
  printf("\n \n E arvore binaria  %d", aux);

  return 0;
}
