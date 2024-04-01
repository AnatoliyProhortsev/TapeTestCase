CXX = g++
CXXFLAGS = -std=c++17
CXXFLAGS_TEST = -std=c++17 -lgtest
TARGET = TapeTestCase

BIN = bin
SRC = src
EXECUTABLE = TapeSort
TESTS_EXECUTABLE = TapeSortTest

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

tests:
	@echo "Building tests.."
	@mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) src/test.cpp src/Sorter.cpp src/Tape.cpp src/exceptions.cpp src/TapeInterface.h -o $(BIN)/$(TESTS_EXECUTABLE) -lgtest

clean:
	clear
	@echo "Clearing.."
	@rm -rf $(BIN)/*