CC = gcc
CFLAGS = -lm -fopenmp -O3
TARGET = main.c

default: knn

knn: knn.o utils.o $(TARGET)
	$(CC) $(CFLAGS) $(TARGET) -o knn.out knn.o utils.o

utils.o: ../utils/utils.c ../utils/utils.h
	$(CC) $(CFLAGS) -c ../utils/utils.c

knn.o: knn.c knn.h
	$(CC) $(CFLAGS) -c knn.c

clean: 
	$(RM) knn.out *.o *~