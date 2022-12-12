# Declaratiile de variabile
CC = gcc
CFLAGS = -g -Wall -lm
 
# Regula de compilare
build: task1 task2 task3 task4

task1: task1.c
	$(CC) -o task1 task1.c task0.c $(CFLAGS)

task2: task2.c
	$(CC) -o task2 task2.c task0.c $(CFLAGS)

task3: task3.c
	$(CC) -o task3 task3.c task0.c $(CFLAGS)

task4: task4.c
	$(CC) -o task4 task4.c task0.c $(CFLAGS)


# Regulile de "curatenie" (se folosesc pentru stergerea fisierelor intermediare si/sau rezultate)
.PHONY : clean
clean :
	rm -f task1 task2 task3 task4
	rm -f *.out
	rm my_diff
