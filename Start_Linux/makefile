CC = gcc
CFLAGS = -g -Wall
LDFLAGS = -lGL -lX11 -lm
BINARIES = ./linux

raylibfolder = ./raylib
unityfolder = ./unity

# --------------------------
# Initiales Programm bauen (zum ausprobieren)
# --------------------------
mnist_initial: $(BINARIES)/libmnist_complete.a
	$(CC) -o mnist $(BINARIES)/libmnist_complete.a $(BINARIES)/libraylib.a ${LDFLAGS}

# --------------------------
# Selbst implementiertes Programm bauen
# --------------------------
mnist: main.o matrix.o neuralNetwork.o imageInput.o mnistVisualization.o $(BINARIES)/libraylib.a
	$(CC) $(CFLAGS) -I$(raylibfolder) -o mnist main.o matrix.o neuralNetwork.o imageInput.o mnistVisualization.o $(BINARIES)/libraylib.a ${LDFLAGS}

main.o: main.c
	$(CC) -c $(CFLAGS) main.c

matrix.o: matrix.c
	$(CC) -c $(CFLAGS) matrix.c

neuralNetwork.o: neuralNetwork.c
	$(CC) -c $(CFLAGS) neuralNetwork.c

imageInput.o: imageInput.c
	$(CC) -c $(CFLAGS) imageInput.c

mnistVisualization.o: mnistVisualization.c
	$(CC) -c $(CFLAGS) -I$(raylibfolder) imageInput.c

# --------------------------
# Unit Tests
# --------------------------
matrixTests: matrix.o matrixTests.c
	$(CC) $(CFLAGS) -I$(unityfolder) -o runMatrixTests matrixTests.c matrix.o $(BINARIES)/libunity.a

neuralNetworkTests: neuralNetwork.o neuralNetworkTests.c
	$(CC) $(CFLAGS) -I$(unityfolder) -o runNeuralNetworkTests neuralNetworkTests.c neuralNetwork.o $(BINARIES)/libunity.a

imageInputTests: imageInput.o imageInputTests.c
	$(CC) $(CFLAGS) -I$(unityfolder) -o runImageInputTests imageInputTests.c imageInput.o $(BINARIES)/libunity.a

# --------------------------
# Clean
# --------------------------
clean:
	rm -f *.o mnist runMatrixTests runNeuralNetworkTests runImageInputTests

