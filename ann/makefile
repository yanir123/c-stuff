CC = gcc
CFLAGS = -lm -fopenmp -O3
TARGET = main.c

default: ann

ann: ann.o utils.o $(TARGET)
	$(CC) $(CFLAGS) $(TARGET) -o ann.out ann.o utils.o

utils.o: ../utils/utils.c ../utils/utils.h
	$(CC) $(CFLAGS) -c ../utils/utils.c

ann.o: ann.c ann.h
	$(CC) $(CFLAGS) -c ann.c

clean: 
	$(RM) ann.out *.o *~