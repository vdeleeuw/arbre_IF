#variables de compilation
CC=gcc
CFLAGS=
LDFLAGS=-lm -lGL -lGLU -lglut
EXEC=opengl

#compilation
all: ./bin/$(EXEC)

./bin/opengl: ./obj/actions.o ./obj/arbre.o ./obj/axes.o ./obj/init.o ./obj/normale.o ./obj/pave.o ./obj/switch_blend.o ./obj/VM_init.o ./obj/ppm.o ./obj/main.o 
	$(CC) -o $@ $^ $(LDFLAGS)

./obj/ppm.o: ./src/ppm.c
	$(CC) -o $@ -c $< $(CFLAGS)

./obj/actions.o: ./src/actions.c
	$(CC) -o $@ -c $< $(CFLAGS)

./obj/arbre.o: ./src/arbre.c
	$(CC) -o $@ -c $< $(CFLAGS)

./obj/axes.o: ./src/axes.c
	$(CC) -o $@ -c $< $(CFLAGS)

./obj/init.o: ./src/init.c
	$(CC) -o $@ -c $< $(CFLAGS)

./obj/normale.o: ./src/normale.c
	$(CC) -o $@ -c $< $(CFLAGS)

./obj/pave.o: ./src/pave.c
	$(CC) -o $@ -c $< $(CFLAGS)

./obj/switch_blend.o: ./src/switch_blend.c
	$(CC) -o $@ -c $< $(CFLAGS)

./obj/VM_init.o: ./src/VM_init.c
	$(CC) -o $@ -c $< $(CFLAGS)

./obj/main.o: ./src/main.c ./src/actions.h ./src/ppm.h ./src/axes.h ./src/init.h ./src/normale.h ./src/pave.h ./src/switch_blend.h ./src/VM_init.h ./src/touches.h
	$(CC) -o $@ -c $< $(CFLAGS)

#nettoyeur
clean:
	rm -rf ./obj/*.o

mrproper: clean
	rm -rf ./bin/$(EXEC)


