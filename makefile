PROJ_NAME = trab2
CC_FLAGS=-c -w -Wall -g -lm

DIR_ENTRADA_1=./entrada/entrada7.csv
DIR_ENTRADA_2=./entrada/entrada10.csv
DIR_ENTRADA_3=./entrada/entrada50.csv
DIR_ENTRADA_4=./entrada/entrada100.csv

DIR_SAIDA_1=./saida/saida7.csv
DIR_SAIDA_2=./saida/saida10.csv
DIR_SAIDA_3=./saida/saida50.csv
DIR_SAIDA_4=./saida/saida100.csv

DIR_RESP_1=./resposta/saida7.csv
DIR_RESP_2=./resposta/saida10.csv
DIR_RESP_3=./resposta/saida50.csv
DIR_RESP_4=./resposta/saida100.csv

$(PROJ_NAME): main.o aresta.o PQ.o grafo.o
	@ gcc -o $(PROJ_NAME) main.o aresta.o PQ.o grafo.o -lm

main.o: main.c
	@ gcc -o main.o main.c $(CC_FLAGS)

aresta.o: aresta.c
	@ gcc -o aresta.o aresta.c $(CC_FLAGS)

PQ.o: PQ.c
	@ gcc -o PQ.o PQ.c $(CC_FLAGS)

grafo.o : grafo.c
	@ gcc -o grafo.o grafo.c $(CC_FLAGS)


clean:
	@ rm -rf *.o $(PROJ_NAME) saida/*

rmpromper: clean
	@ rm -rf $(PROJ_NAME)

run1:
	@ ./$(PROJ_NAME) $(DIR_ENTRADA_1) $(DIR_SAIDA_1)

run2:
	@ ./$(PROJ_NAME) $(DIR_ENTRADA_2) $(DIR_SAIDA_2)

run3:
	@ ./$(PROJ_NAME) $(DIR_ENTRADA_3) $(DIR_SAIDA_3)

run4:
	@ ./$(PROJ_NAME) $(DIR_ENTRADA_4) $(DIR_SAIDA_4)

runAll: run1 run2 run3 run4

val1:
	@ valgrind --leak-check=full ./$(PROJ_NAME) $(DIR_ENTRADA_1) $(DIR_SAIDA_1)

val2:
	@ valgrind --leak-check=full ./$(PROJ_NAME) $(DIR_ENTRADA_2) $(DIR_SAIDA_2)

val3:
	@ valgrind --leak-check=full ./$(PROJ_NAME) $(DIR_ENTRADA_3) $(DIR_SAIDA_3)

val4:
	@ valgrind --leak-check=full ./$(PROJ_NAME) $(DIR_ENTRADA_4) $(DIR_SAIDA_4)

valAll: val1 val2 val3 val4

diff1:
	@ ./$(PROJ_NAME) ${DIR_ENTRADA_1} ${DIR_SAIDA_1}
	@ diff ${DIR_SAIDA_1} ${DIR_RESP_1}

diff2:
	@ ./$(PROJ_NAME) ${DIR_ENTRADA_2} ${DIR_SAIDA_2}
	@ diff ${DIR_SAIDA_2} ${DIR_RESP_2}

diff3:
	@ ./$(PROJ_NAME) ${DIR_ENTRADA_3} ${DIR_SAIDA_3}
	@ diff ${DIR_SAIDA_3} ${DIR_RESP_3}

diff4:
	@ ./$(PROJ_NAME) ${DIR_ENTRADA_4} ${DIR_SAIDA_4}
	@ diff ${DIR_SAIDA_4} ${DIR_RESP_4}

diffAll: diff1 diff2 diff3 diff4
	