#include"lista.h"

/*-------------------------------------------------------------------------------*/
/* FUNCAO QUE CHECA SE O GRAFO E COMPLETO   */
/*-------------------------------------------------------------------------------*/
int Checa_completo ( lista *lista_adjacente, int qtd_vertices ) {

	int i;
	no *bloquinho = lista_adjacente->primeiro;
	
	for (i = 0; i<lista_adjacente->tam_atual; i++) {
		if ( bloquinho[i].grau != qtd_vertices - 1 )
			return 0;
	}

	return 1;

}


main () {

	int a, b, controle, qtd_vertices, achou_completo, sem_vertices = 1;
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
	if ( ! sem_vertices ) {
		achou_completo = Checa_completo ( lista_adjacente, qtd_vertices );
		if ( achou_completo ) 
			printf("G é completo\n");
		else 
			printf("G não é completo\n");
	}
	else 
		printf("G não é completo\n");
//	Libera ( lista_adjacente, qtd_vertices );
}
