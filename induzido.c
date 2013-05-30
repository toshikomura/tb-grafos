#include"lista.h"

/*-------------------------------------------------------------------------------*/
/* FUNCAO QUE INSERE VERTICES (V) QUE COMPLETAM UMA ARESTA    ( 2, V )           */
/*-------------------------------------------------------------------------------*/
sub_no *Completa_aresta_i ( sub_no *bloco, int w, int valor, int first ) {

	sub_no *new_bloco;

	// Se nao existe o bloco
	if ( bloco == NULL ) {
		new_bloco = malloc ( sizeof (sub_no) );
		new_bloco->vertice = w;
		new_bloco->valor_ordem = valor;
		new_bloco->primeiro = first;
		new_bloco->mais = NULL;

		return new_bloco;
	}

	// passa para o proximo bloco
	bloco->mais = Completa_aresta_i ( bloco->mais, w, valor, first );
	
	return bloco;

}


/*-------------------------------------------------------------------------------*/
/* FUNCAO QUE INSERE VERTICES (U)     ( U, 3 )                                   */
/*-------------------------------------------------------------------------------*/
int Insere_vertice_i ( lista *lista_adjacente, int v, int w, int controle, int valor, int first) {

	int tam_atual = lista_adjacente->tam_atual; 
	no *bloquinho = lista_adjacente->primeiro;

	// Se o vertice ainda nao existe no vetor
	if ( controle == -1 ) {
		bloquinho[tam_atual].vertice = v;
		bloquinho[tam_atual].grau = 1;
		bloquinho[tam_atual].proximo = NULL;
		lista_adjacente->tam_atual++;
		bloquinho[tam_atual].proximo = Completa_aresta_i ( bloquinho[tam_atual].proximo, w, valor, first );
	}
	// Se o vertice existe no vetor
	else {
		bloquinho[controle].grau++;		
		bloquinho[controle].proximo = Completa_aresta_i ( bloquinho[controle].proximo, w, valor, first );
	}
}


/*-------------------------------------------------------------------------------*/
/* FUNCAO QUE CONSOME ESPACOS                                                    */
/*-------------------------------------------------------------------------------*/
void Consome_espacos ( char *valor ) {
		while ( *valor == 32 ) {
			scanf("%c", valor );
		}
}


/*-------------------------------------------------------------------------------*/
/* FUNCAO QUE FAZ A LEITURA DA ENTRADA                                           */
/*-------------------------------------------------------------------------------*/
int Leitura ( char *valor, int *vetor, int qtd_vertices ) {
	
	int i = 0, j = 0, l = 0, aux, k, 
	a_aux[6], b_aux[6];

	// passando de linha
	// isso só ocorre na primeira leitura
	if ( *valor == 10 )
		scanf("%c", valor );
	// enquanto nao acabar a linha
	while ( *valor != 10 ) {
		a_aux[i] = atoi ( valor );
		i++;
		scanf("%c", valor );
		// vencendo os espacos e lendo o segundo vertice, 
		// senao ele vai ler o numero de mais de uma casa decimal
		if ( *valor == 32 || *valor == 10 ) {
			// Calculando os valores do primeiro vertice
			aux = 0;
			for ( k = 0; k < i; k++ ) {
				aux = aux * 10;
				aux = aux + a_aux[ k ];
			}
			i = 0;
			a_aux[0] = aux;
			// atribuindo valores ao vetor de saida
			vetor[l] = a_aux[0];
			l++;
			// Final dos calculos
			// Se o que for pula linha
			if ( *valor != 10 ) {
				Consome_espacos ( valor );
				b_aux[j] = atoi ( valor );
				j++;
				scanf("%c", valor );
				// leitura para numero de mais de uma casa decimal
				while ( *valor != 32 && *valor != 10) {
					b_aux [j] = atoi ( valor );
					j++;
					scanf("%c", valor );
				} 
				//printf("sau do loop p %c\n", *valor );
				// Calculando os valores do segundo vertice
				aux = 0;
				for ( k = 0; k < j; k++ ) {
					aux = aux * 10;
					aux = aux + b_aux[ k ];
				}
				j = 0;
				b_aux[0] = aux;
				// atribuindo valores ao vetor de saida
				vetor[l] = b_aux[0];
				l++;
				// Final dos calculos
				Consome_espacos ( valor );
			}
		}
	}

	return l;

}


/*-------------------------------------------------------------------------------*/
/* FUNCAO QUE TESTA SE O VERTICE EXISTE NO CONJUNTO DADO                         */
/*-------------------------------------------------------------------------------*/
int Vertice_no_conj ( int *vetor,  int vertice, int tam_conj ) {

	int i;

	// percorre o conjunto
	for ( i = 0; i < tam_conj; i++ ) {
		if ( vetor[i] == vertice )
			return 1; 
	}

	return 0;

}


/*-------------------------------------------------------------------------------*/
/* FUNCAO QUE DETERMINA QUAL E O SUBGRAFO INDUZIDO SABENDO O CONJ DE VERTICES    */
/*-------------------------------------------------------------------------------*/
void	Induzido ( lista *lista_adjacente, int *vetor, int qtd_vertices, int tam_conj, int valor_ordem ) {

	int i, valor = 1;
	no *bloquinho;
	sub_no *bloco;

	// enquanto nao chegar na última aresta inserida
	while ( valor != valor_ordem ) {
		bloquinho = lista_adjacente->primeiro;
		// percorre a lista
		for ( i = 0; i < qtd_vertices; i++ ) {
			bloco = bloquinho[i].proximo;
			// se o vertice (u) escolhido existe no conjunto
			if ( Vertice_no_conj ( vetor, bloquinho[i].vertice, tam_conj ) ) {
				// percorre todos os vertices que (u) forma uma aresta
				while ( bloco != NULL ) {
					// se este vertice tambem pertence ao conjunto
					if ( Vertice_no_conj ( vetor, bloco->vertice, tam_conj ) ) {
						// teste para evitar a impressao inversa da aresta ( u, v ) para ( v, u )
						if ( bloco->primeiro && bloco->valor_ordem == valor )
							printf("%d %d\n", bloquinho[i].vertice, bloco->vertice ); 
					}
					bloco = bloco->mais;
				}
			}		
		}
		valor++;
	}

}


/*-------------------------------------------------------------------------------*/
/* FUNCAO QUE FINALIZA A LISTA ADJACENTE                                         */
/*-------------------------------------------------------------------------------*/
/*
void Libera_i (lista *lista_adjacente, int *vetor, int qtd_vertices ) {

	int i;
	no *bloquinho = lista_adjacente->primeiro;
	sub_no *bloco, *bloco_aux;
	
	// percorre a lista
	for ( i = 0; i < qtd_vertices; i++ ) {
		bloco = bloquinho[i].proximo;
		// para cada vertice que forma aresta com v
		while ( bloco != NULL ) {
			bloco_aux = bloco;
			bloco = bloco->mais;
			free ( bloco_aux );
		}
	}

	free ( lista_adjacente->primeiro );
	free ( lista_adjacente );
	free ( vetor );

}
*/

main () {

	char valor;
	int a, b, controle, first = 1, qtd_vertices, tam_conj, i, valor_ordem = 1;
	lista *lista_adjacente;
	no *bloquinho;

	scanf ("%d", &qtd_vertices);
	int *vetor = malloc ( sizeof (int)*qtd_vertices ); // vetor auxiliar p/ leitura
	lista_adjacente = Inicia_lista ( qtd_vertices ); 

	// Enquanto o arquivo nao acabar
	while ( scanf("%c", &valor ) != EOF ) {
		tam_conj = Leitura ( &valor, vetor, qtd_vertices );
		// Se primeira vez
		if ( first == 1 ) {
			first = 0;
		}
		else {
			if ( a != b) {
				controle = Procura_vertice ( lista_adjacente, a );
				Insere_vertice_i ( lista_adjacente, a, b, controle, valor_ordem, 1 );
				controle = Procura_vertice ( lista_adjacente, b );
				Insere_vertice_i ( lista_adjacente, b, a, controle, valor_ordem, 0 );
			}
			valor_ordem++;
		}
		// atribui valores aos vertices que formam aresta
		a = vetor[0];
		b = vetor[1];
	}
	// imprime o conjunto
	for ( i = 0; i < tam_conj; i++ ) {
		printf( "%d ", vetor[i] );
	}
	printf( "\n" );
	Induzido ( lista_adjacente, vetor , qtd_vertices, tam_conj, valor_ordem );
//	Libera_i ( lista_adjacente, vetor, qtd_vertices );
}
