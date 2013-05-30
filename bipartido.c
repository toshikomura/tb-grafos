#include"lista.h"

/*-------------------------------------------------------------------------------*/
/* FUNCAO QUE PROCURA OS VERTICES NOS CONJUNTOS                                  */
/*-------------------------------------------------------------------------------*/
int Procura_nos_conj ( int *A, int *B, int vertice, int conj1ou2, int Acount, int Bcount ) {

	// Lembrando que o conjunto foi alterado quando o vertice foi inserido
	// RETORNANDO 
	// 0 o vertice ainda nao existe no conjunto
	// 1 o vertice ja existe no conjunto
	// 2 o o vertice ja existe em um dos conjuntos (1 por exemplo) 
	// e deveria ser inserido no outro conjunto (2 por exemplo)  

	int i;

	// Se foi inserido no conjunto 1 (A)
	if ( conj1ou2 == 2 ) {
		// percorre o conjunto 2 (B)
		for ( i = 0; i < Bcount; i++ ) {
			if ( B[ i ] == vertice ) {

				return 1;

			}
		}
		// percorre o conjunto 1 (A)
		for ( i = 0; i < Acount; i++ ) {
			if ( A[ i ] == vertice ) {

				return 2;

			}
		}

		return 0;

	}
	// Se foi inserido no conjunto 2 (B)
	else {
		if ( conj1ou2 == 1 ) {
			// percorre o conjunto 1 (A)
			for ( i = 0; i < Acount; i++ ) {
				if ( A[ i ] == vertice ) {

					return 1;

				}
			}
			// percorre o conjunto 2 (B)
			for ( i = 0; i < Bcount; i++ ) {
				if ( B[ i ] == vertice ) {

					return 2;

				}
			}

			return 0;

		}
	}
}


/*-------------------------------------------------------------------------------*/
/* FUNCAO QUE PROCURA O EDNERECO DE UM DETERMINADO VERTICE                       */
/*-------------------------------------------------------------------------------*/
no Procura_endereco ( lista *lista_adjacente, int vertice ) {

	int i = 0;
	no *bloquinho = lista_adjacente->primeiro;
	
	// enquanto nao econtrar o vertice 
	while ( bloquinho[i].vertice != vertice ) {
		i++;
	}

	return bloquinho[i];
}


/*-------------------------------------------------------------------------------*/
/* FUNCAO QUE INSERE O VERTICE NO CONJUNTO E VERIFICA SE O GRAFO E BIPARTIDO     */
/*-------------------------------------------------------------------------------*/
int Verifica ( lista *lista_adjacente, no bloquinho, int *A, int *B, int v, int conj1ou2 , int Acount, int Bcount ) {

	// Se 1 insere no conjunto 1 (A)
	if ( conj1ou2 == 1 ) {
		A[ Acount ] = v;
		// muda de conjunto
		conj1ou2 = 2;
		Acount++;
	}
	// Senao se 2 insere no conjunto 2 (B)
	else {
		if ( conj1ou2 == 2 ) {
			B[ Bcount ] = v;
			// muda de conjunto
			conj1ou2 = 1;
			Bcount++;
		}
	}	

	int achou;
	no bloquinho_aux;
	sub_no *bloco = bloquinho.proximo;	

	// percorre os vertices que formam aresta com (u)
	while ( bloco != NULL ) {
		achou = Procura_nos_conj ( A, B, bloco->vertice, conj1ou2, Acount, Bcount );
		// Se 2 e que o grafo nao e bipartido
		if ( achou == 2 ) return 0;
		// Se 0 insere o vertice no outro conjunto
		if ( achou == 0 ) {
			bloquinho_aux = Procura_endereco ( lista_adjacente, bloco->vertice );
			// Se o retorno da funcao for 0 e que o grafo nao e bipartido
			if ( Verifica ( lista_adjacente, bloquinho_aux, A, B, bloco->vertice, conj1ou2, Acount, Bcount ) == 0 ) {

				return 0;

			} 	
		}
		bloco = bloco->mais;
		
	}

	return 1;

}


/*-------------------------------------------------------------------------------*/
/* FUNCAO QUE CHECA SE O GRAFO E BIPARTIDO                                       */
/*-------------------------------------------------------------------------------*/
int Checa_bipartido ( lista *lista_adjacente, int qtd_vertices ) {

	int v, 
	*A = malloc ( sizeof (int)*qtd_vertices ),
	*B = malloc ( sizeof (int)*qtd_vertices );
	no *	bloquinho = lista_adjacente->primeiro;
	v = bloquinho[0].vertice;
	
	return Verifica ( lista_adjacente, bloquinho[0], A, B, v, 1, 0, 0 );	

}


main () {

	int a, b, controle, qtd_vertices, achou_bipartido, sem_vertices = 1;
	lista *lista_adjacente;

	scanf ("%d", &qtd_vertices);
	lista_adjacente = Inicia_lista ( qtd_vertices ); 

	// Enquanto o arquivo não acabar
	while ( scanf("%d", &a ) != EOF) {
		scanf("%d", &b );
		if ( a != b) {
			controle = Procura_vertice ( lista_adjacente, a );
			Insere_vertice ( lista_adjacente, a, b, controle );
			controle = Procura_vertice ( lista_adjacente, b );
			Insere_vertice ( lista_adjacente, b, a, controle );
		}
		sem_vertices = 0;
	}
	achou_bipartido = Checa_bipartido ( lista_adjacente, qtd_vertices );
	if ( ! sem_vertices ) {
		if ( achou_bipartido ) 
			printf("G é bipartido\n");
		else
			printf("G não é bipartido\n");
	}
	else
		printf("G é bipartido\n");
//	Libera ( lista_adjacente, qtd_vertices );
}
