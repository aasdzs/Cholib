TARGET = public
CC = gcc
CFLAGS = -W -Wall 
RM = rm -f

#OBJECTS = main.o benchmark.o bignum.o gf2n.o sagetest.o word.o
OBJECTS = main.c benchmark.c bignum.c gf2n.c sagetest.c word.c

.SUFFIXES : .c .o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

run:
	./$(TARGET)

clean:
	$(RM) *.o $(TARGET)

del:
	$(RM) *.txt $(TARGET)


