EXEC=main
CC=gcc

all:  $(EXEC)


main: fonction.o  fonction_reseau_exo2.o exo3.o exo4.o exo6.o Djikstra.o exo7.o main.o
	@$(CC) -o main fonction.o fonction_reseau_exo2.o exo3.o exo4.o exo6.o Djikstra.o exo7.o main.o -lm

fonction.o: fonction.c structure1.h
	@$(CC) -o fonction.o -c fonction.c -lm 
fonction_reseau_exo2.o: fonction_reseau_exo2.c structure_reseau.h
	@$(CC) -o fonction_reseau_exo2.o -c fonction_reseau_exo2.c -lm
exo3.o: exo3.c exo3.h
	 @$(CC) -o exo3.o -c exo3.c -lm 
exo4.o: exo4.c exo4.h
	 @$(CC) -o exo4.o -c exo4.c -lm 
exo6.o: exo6.c exo6.h
	 @$(CC) -o exo6.o -c exo6.c -lm 
exo7.o: exo7.c exo7.h
	 @$(CC) -o exo7.o -c exo7.c -lm 
Djikstra.o: Djikstra.c Djikstra.h
	 @$(CC) -o Djikstra.o -c Djikstra.c -lm 
main.o: main.c fonction.h fonction_reseau_exo2.h exo3.h exo4.h exo6.h Djikstra.h exo7.h
	@$(CC) -o main.o -c main.c -lm 
clean:	
	@rm -f *.o
	@rm -f $(EXEC)
PHONY:
	@rm -f *.cha *.res *.fig 


