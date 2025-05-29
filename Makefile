CC = gcc
CFLAGS = -Wall -Iincs
OBJ = obj/main.o obj/search.o
TARGET = build/program

all: $(TARGET)

$(TARGET): $(OBJ)
	mkdir -p build obj
	$(CC) $(OBJ) -o $(TARGET)

obj/main.o: src/main.c incs/search.h
	mkdir -p obj
	$(CC) $(CFLAGS) -c src/main.c -o obj/main.o

obj/search.o: src/search.c incs/search.h
	mkdir -p obj
	$(CC) $(CFLAGS) -c src/search.c -o obj/search.o

clean:
	rm -rf obj/*.o $(TARGET)

run:
	cd build && ./program