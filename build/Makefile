INC_DIR = ../code/include/
SRC_DIR = ../code/src/
MAIN_DIR = ../code/
CXX = g++

Application: Booth.o Edge.o Graph.o Node.o Patron.o main.cpp
	$(CXX) Booth.o Edge.o Graph.o Node.o Patron.o main.cpp -o Fair.exe

Booth.o: $(SRC_DIR)Booth.cpp $(INC_DIR)Booth.h
	$(CXX) $(SRC_DIR)Booth.cpp $(INC_DIR)Booth.h -c

Edge.o: $(SRC_DIR)Edge.cpp $(INC_DIR)Edge.h
	$(CXX) $(SRC_DIR)Edge.cpp $(INC_DIR)Edge.h -c

Graph.o: $(SRC_DIR)Graph.cpp $(INC_DIR)Graph.h
	$(CXX) $(SRC_DIR)Graph.cpp $(INC_DIR)Graph.h -c

Node.o: $(SRC_DIR)Node.cpp $(INC_DIR)Node.h
	$(CXX) $(SRC_DIR)Node.cpp $(INC_DIR)Node.h -c

Patron.o: $(SRC_DIR)Patron.cpp $(INC_DIR)Patron.h
	$(CXX) $(SRC_DIR)Patron.cpp $(INC_DIR)Patron.h -c

clean:
	rm *.o Fair.exe

cleancsv:
	rm *.csv
