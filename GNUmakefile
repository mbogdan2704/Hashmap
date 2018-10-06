build:tema1.o t1.h hash.h t1_f.c
	gcc -Wall tema1.c t1_f.c -o tema1 -lhash -L.
tema1.o: tema1.c
	gcc -Wall -c tema1.c
t1_f.o: t1_f.c
	gcc -Wall -c t1_f.c
clean: 
	rm -f ./tema1
