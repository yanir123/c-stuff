CC = gcc
CFLAGS = -lm -fopenmp -O3
TARGET = main.c

default: svm

svm: svm.o utils.o $(TARGET)
	$(CC) $(CFLAGS) $(TARGET) -o svm.out svm.o utils.o

utils.o: ../utils/utils.c ../utils/utils.h
	$(CC) $(CFLAGS) -c ../utils/utils.c

svm.o: svm.c svm.h
	$(CC) $(CFLAGS) -c svm.c

clean: 
	$(RM) svm.out *.o *~