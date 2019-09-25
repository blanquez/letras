INC = include
OBJ = obj
SRC = src
BIN = bin
CXX = g++
CPPFLAGS = -std=c++11 #-Wall -g


all: $(BIN)/letras

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/Doxyfile
	
# ************ Compilación de módulos ************

$(BIN)/letras: $(OBJ)/letras.o
	$(CXX) -o $(BIN)/letras -I./$(INC) $(OBJ)/letras.o

$(OBJ)/letras.o : $(SRC)/letras.cpp
	$(CXX) $(CPPFLAGS) -I./$(INC) -c -o $(OBJ)/letras.o $(SRC)/letras.cpp

# ************ Limpieza ************
clean :
	echo "Limpiando..."
	rm -f $(OBJ)/*.o

mrproper : clean
	rm -f $(BIN)/* doc/html/*
