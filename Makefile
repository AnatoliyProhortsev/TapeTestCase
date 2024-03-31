CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = TapeTestCase

BIN = bin
SRC = src
EXECUTABLE = TapeSort

run:
	clear
	@echo "Executing.."
	./$(BIN)/$(EXECUTABLE)

build:
	@echo "Building.."
	@mkdir -p $(BIN)
	$(CXX) $(CXX_FLAGS) src/main.cpp src/Sorter.cpp src/Tape.cpp src/exceptions.cpp src/TapeInterface.h -o $(BIN)/$(EXECUTABLE)
	clear
	@echo "Build successful"

clean:
	clear
	@echo "Clearing.."
	@rm -rf $(BIN)/*