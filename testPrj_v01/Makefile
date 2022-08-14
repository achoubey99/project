CC = g++

MKDIR_P = mkdir -p
THREADS = -pthread
LFLAGS = -o
CFLAGS = -c -g
INC = ./inc
IFLAG = -I$(INC)
BIN = ./bin
OBJ = ./obj
SRC = ./src

.PHONY: directories

all: directories Server Client

directories: ${OBJ} $(BIN)

${OBJ}:
	${MKDIR_P} ${OBJ}

${BIN}:
	${MKDIR_P} ${BIN}


Server: $(OBJ)/MainServer.o $(OBJ)/Server.o
	$(CC) $(LFLAGS) $(BIN)/Server $(OBJ)/MainServer.o $(OBJ)/Server.o

$(OBJ)/Server.o: $(SRC)/Server.cpp
	$(CC) $(CFLAGS) $(IFLAG) $(SRC)/Server.cpp 
	mv *.o $(OBJ)

$(OBJ)/MainServer.o: $(SRC)/MainServer.cpp
	$(CC) $(CFLAGS) $(IFLAG) $(SRC)/MainServer.cpp 
	mv *.o $(OBJ)

Client: $(OBJ)/MainClient.o $(OBJ)/Client.o
	$(CC) $(LFLAGS) $(BIN)/Client $(OBJ)/MainClient.o $(OBJ)/Client.o $(THREADS)

$(OBJ)/MainClient.o: $(SRC)/MainClient.cpp
	$(CC) $(CFLAGS) $(IFLAG) $(SRC)/MainClient.cpp 
	mv *.o $(OBJ)

$(OBJ)/Client.o: $(SRC)/Client.cpp
	$(CC) $(CFLAGS) $(IFLAG) $(SRC)/Client.cpp 
	mv *.o $(OBJ)


clean:
	rm -f *.o a.out
	rm -f $(OBJ)/*.o
	rm -f $(BIN)/Server $(BIN)/Client
	rm -r $(BIN) $(OBJ)
	@echo "Cleaning Done!"