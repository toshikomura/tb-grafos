#include<stdio.h>
#include<stdlib.h>

typedef struct sub_no {
	int vertice;
	int valor_ordem;
	int primeiro;
	struct sub_no *mais;
} sub_no;

typedef struct no {
	int vertice;
	int grau;
	sub_no *proximo;
} no;

typedef struct lista {
	no  *primeiro;
	int qtd_vertices;
	int tam_atual;
} lista;

lista *Inicia_lista ( int qtd_vertices );
int Procura_vertice ( lista *lista_adjacente, int v );
sub_no *Completa_aresta ( sub_no *bloco, int w );
int Insere_vertice ( lista *lista_adjacente, int v, int w, int controle );
//void Libera ( lista *lista_adjacente, int qtd_vertices);
