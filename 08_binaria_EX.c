#include <stdio.h>

#include <stdlib.h>

typedef struct arvore {
  int info;
  struct arvore * esq;
  struct arvore * dir;
}
Arvore;

Arvore * cria_arv_vazia(void);
Arvore * arv_constroi(int c, Arvore * e, Arvore * d);
int verifica_arv_vazia(Arvore * a);
Arvore * arv_libera(Arvore * a);
int arv_pertence(Arvore * a, char c);
void arv_imprime(Arvore * a);

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

void structure90(Arvore * root, int level) {
  int i;

  if (root == NULL) {
    padding('\t', level);
    puts("~");
  } else {
    structure90(root -> dir, level + 1);
    padding('\t', level);
    printf("%d\n", root -> info);
    structure90(root -> esq, level + 1);
  }
}

void structureWithLevel(Arvore * root, int level) {
  if (root != NULL) {
    printf("%d\t NLV: %d \t", root -> info, level);
    if (root -> esq == NULL && root -> dir == NULL) {
      printf("No folha\n");
    } else {
      printf("\n");
      structureWithLevel(root -> esq, level + 1);
      structureWithLevel(root -> dir, level + 1);
    }
  }
}

void structureInOrdem(Arvore * root, int level) {
  if (root != NULL) {
    structureInOrdem(root -> esq, level + 1);
    printf("%d\t ", root -> info, level);
    structureInOrdem(root -> dir, level + 1);
  }
}

void structurePreOrdem(Arvore * root, int level) {
  if (root != NULL) {
    printf("%d\t ", root -> info, level);
    structurePreOrdem(root -> esq, level + 1);
    structurePreOrdem(root -> dir, level + 1);
  }
}

void structurePosOrdem(Arvore * root, int level) {
  if (root != NULL) {
    structurePosOrdem(root -> esq, level + 1);

    structurePosOrdem(root -> dir, level + 1);
    printf("%d\t ", root -> info, level);
  }
}

Arvore * insert(Arvore * a, int num)
{
    if (a == NULL){
    	printf("\nInserindo %d  ", num);
        return arv_constroi(num, cria_arv_vazia(), cria_arv_vazia());
	}
	
    if (num < a->info)
        a->esq = insert(a->esq, num);
    else if (num > a->info)
        a->dir = insert(a->dir, num);
 
    return a;
}

Arvore * busca_binaria (Arvore* r, int k) {
    if (r == NULL || r->info == k)
       return r;
    if (r->info > k)
       return busca_binaria (r->esq, k);
    else
       return busca_binaria (r->dir, k);
}

Arvore * removeraiz (Arvore * r) {  
    Arvore *p, *q;
    if (r->esq == NULL) {
       q = r->dir;
       free (r);
       return q;
    }
    p = r; q = r->esq;
    while (q->dir != NULL) {
       p = q; q = q->dir;
    }

    if (p != r) {
       p->dir = q->esq;
       q->esq = r->esq;
    }
    q->dir = r->dir;
    free (r);
    return q;
}


int min_arvore(Arvore * a) {
  if (a == NULL)
    return 0;

  int res = a -> info;
  int auxa = min_arvore(a -> dir);
  int auxb = min_arvore(a -> esq);
  if (auxa <= res && auxa <= auxb) {
    res = auxa;
  }
  if (auxb <= res && auxb <= auxa) {
    res = auxb;
  }
  return res;
}


int max_arvore(Arvore * a) {
  if (a == NULL)
    return 0;

  int res = a -> info;
  int auxa = max_arvore(a -> dir);
  int auxb = max_arvore(a -> esq);
  if (auxa >= res && auxa >= auxb) {
    res = auxa;
  }
  if (auxb >= res && auxb >= auxa) {
    res = auxb;
  }
  return res;
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

  for (i = 0; i < 1000; i++){
  a =insert (a, i);
}
   structureInOrdem(a,0);

 aux = max_arvore(a);
 printf("\n \n Maior %d", aux);
 
  aux = min_arvore(a);
 printf("\n \n Menor %d", aux);

 a1 = busca_binaria(a, 999);
 printf("\n\n Encontrado: %d", a1->info);

  return 0;
}
