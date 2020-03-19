

calc: main.o
	gcc main.o -o calc


main.o : main.c add.h sub.h mul.h div.h
	gcc -c main.c -o main.o

clean:
	rm -rf *.o
