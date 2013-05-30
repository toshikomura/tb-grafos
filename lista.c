#include"lista.h"

/*-------------------------------------------------------------------------------*/
/* FUNCAO QUE INICIA A LISTA ADJACENTE                                           */
/*-------------------------------------------------------------------------------*/
lista *Inicia_lista ( int qtd_vertices ) {

	lista *lista_adjacente = malloc( sizeof (lista) ); 
	// Valores iniciais para a lista
	lista_adjacente->primeiro = malloc( sizeof (no)*qtd_vertices );
	lista_adjacente->qtd_vertices = qtd_vertices;
	lista_adjacente->tam_atual = 0;

	return lista_adjacente;

} 


/*-------------------------------------------------------------------------------*/
/* FUNÇAO QUE PROCURA O VERTICE                                                  */
/*-------------------------------------------------------------------------------*/
int Procura_vertice ( lista *lista_adjacente, int v ) {

	int i = 0, tam_atual = lista_adjacente->tam_atual; 

	// Se nao tem nenhum vertice no vetor
	if ( tam_atual == 0) 
		return -1;

	no *bloquinho = lista_adjacente->primeiro;

	// Enquanto nao chega no final do vetor
	while ( i < tam_atual ) {
		if ( bloquinho[i].vertice == v) {
			return i;
		}
		i++;
	}

	// Senão o vertice ainda nao existe no vetor
	return -1;
	
}


/*-------------------------------------------------------------------------------*/
/* FUNCAO QUE INSERE VERTICES (V) QUE COMPLETAM UMA ARESTA    ( 2, V )           */
/*-------------------------------------------------------------------------------*/
sub_no *Completa_aresta ( sub_no *bloco, int w ) {

	sub_no *new_bloco;

	// Se nao existe o bloco
	if ( bloco == NULL ) {
		new_bloco = malloc ( sizeof (sub_no) );
		new_bloco->vertice = w;
		new_bloco->mais = NULL;
		return new_bloco;
	}

	// passa para o proximo bloco
	bloco->mais = Completa_aresta ( bloco->mais, w );
	
	return bloco;

}


/*-------------------------------------------------------------------------------*/
/* FUNCAO QUE INSERE VERTICES (U)     ( U, 3 )                                   */
/*-------------------------------------------------------------------------------*/
int Insere_vertice ( lista *lista_adjacente, int v, int w, int controle ) {

	int tam_atual = lista_adjacente->tam_atual; 
	no *bloquinho = lista_adjacente->primeiro;

	// Se o vertice ainda nao existe no vetor
	if ( controle == -1 ) {
		bloquinho[tam_atual].vertice = v;
		bloquinho[tam_atual].grau = 1;
		bloquinho[tam_atual].proximo = NULL;
		lista_adjacente->tam_atual++;
		bloquinho[tam_atual].proximo = Completa_aresta ( bloquinho[tam_atual].proximo, w );
	}
	// Se o vertice existe no vetor
	else {
		bloquinho[controle].grau++;		
		bloquinho[controle].proximo = Completa_aresta ( bloquinho[controle].proximo, w );
	}

}


/*-------------------------------------------------------------------------------*/
/* FUNCAO QUE FINALIZA A LISTA ADJACENTE                                         */
/*-------------------------------------------------------------------------------*/
/*
void Libera ( lista *lista_adjacente, int qtd_vertices) {

	int i;
	no *bloquinho = lista_adjacente->primeiro;
	sub_no *bloco, *bloco_aux;
	
	// percorre a lista
	for ( i = 0; i < qtd_vertices; i++ ) {
		bloco = bloquinho[i].proximo;
		// para cada vertice que forma aresta com v
		while ( bloco != NULL ) {
			bloco_aux = bloco;
			printf("aqui ");
			printf("%d\n", bloco->vertice );
			bloco = bloco->mais;
			if ( bloco_aux )
				free ( bloco_aux );
		}
	}

	free ( lista_adjacente->primeiro );
	free ( lista_adjacente );

}
*/
