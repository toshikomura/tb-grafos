all:
	gcc -c induzido.c
	gcc -c bipartido.c
	gcc -c completo.c
	gcc -c vetordegraus.c
	gcc -c lista.c
	gcc -o induzido induzido.o lista.o
	gcc -o bipartido bipartido.o lista.o
	gcc -o completo completo.o lista.o
	gcc -o vetordegraus vetordegraus.o lista.o
clean:
	rm -rf *.o
	rm induzido
	rm bipartido
	rm completo
	rm vetordegraus
cleanobjeto:
	rm -rf *.o
teste1:
	./induzido < teste
teste2:
	./bipartido < teste
teste3:
	./completo < teste
teste4:
	./vetordegraus < teste
