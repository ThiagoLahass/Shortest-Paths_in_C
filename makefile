PROJ_NAME = trab
CC_FLAGS=-c -w -Wall -g -lm

$(PROJ_NAME): main.o aresta.o PQ.o grafo.o
	gcc -o $(PROJ_NAME) main.o aresta.o PQ.o grafo.o -lm

main.o: pq/main.c
	gcc -o main.o pq/main.c $(CC_FLAGS)

aresta.o: pq/aresta.c
	gcc -o aresta.o pq/aresta.c $(CC_FLAGS)

PQ.o: pq/PQ.c
	gcc -o PQ.o pq/PQ.c $(CC_FLAGS)

grafo.o : pq/grafo.c
	gcc -o grafo.o pq/grafo.c $(CC_FLAGS)





clean:
	rm -rf *.o
	rm -rf $(PROJ_NAME)

rmpromper: clean
	rm -rf $(PROJ_NAME)

run:
	./$(PROJ_NAME) ./entrada/entrada7.csv saida.txt

val:
	valgrind --leak-check=full ./$(PROJ_NAME) ./entrada/entrada7.csv saida.txt
	
	