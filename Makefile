CC = g++
CCFLAGES = -Wall -g

all: test

test: mvector.o matrix.o test.o

lib: mvector.o matrix.o

%.o: %.cc
	$(CC) -c $(CCFLAGES) $< -o $@

clean:
	rm -f *.o test
