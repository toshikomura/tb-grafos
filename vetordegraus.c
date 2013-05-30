#include"lista.h"

void Imprime ( lista *lista_adjacente, int qtd_vertices ) {

	int i, j, aux,
	*vetor_de_graus = malloc ( sizeof (int)*qtd_vertices );
	no *bloquinho = lista_adjacente->primeiro;

	// coloca os graus dos vertices no vetor
	for (i = 0; i<lista_adjacente->tam_atual; i++) 
		vetor_de_graus[i] = bloquinho[i].grau;
	// percorre o vetor duas n*n vezes para ordena-lo em crescente
	for (j = 1; j<lista_adjacente->tam_atual; j++) {
		for (i = 1; i<lista_adjacente->tam_atual; i++) {
			if ( vetor_de_graus[i] < vetor_de_graus[i-1] ) {
				aux = vetor_de_graus[i];
				vetor_de_graus[i] = vetor_de_graus[i-1];
				vetor_de_graus[i-1] = aux; 
			}
		}			
	}
		
	// imprime o vetor
	for (i = 0; i<lista_adjacente->tam_atual; i++) 
		printf("%d ", vetor_de_graus[i]);
	printf("\n");
}


main () {

	int a, b, controle;
	int qtd_vertices;
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
	}

 	Imprime ( lista_adjacente, qtd_vertices );
//	Libera ( lista_adjacente, qtd_vertices );
}
