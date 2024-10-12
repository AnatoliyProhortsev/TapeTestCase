CXX = g++
CXXFLAGS = -std=c++17
CXXFLAGS_TEST = -std=c++17 -lgtest
TARGET = TapeTestCase

BIN = bin
BUILD = build
SRC = src
EXECUTABLE = TapeSort

IO_EX = TapeIOException
LOAD_EX = TapeLoadException
EMPTY_EX = EmptyTapeException
CONFIG_EX = BadConfigException
EXCEPTIONS_OBJ = $(IO_EX).o $(LOAD_EX).o $(EMPTY_EX).o $(CONFIG_EX).o
EXCEPTIONS_DIR = $(SRC)/Exceptions

all: clean build run

run:
	clear
	@echo "Executing.."
	@mkdir -p $(BIN)/tmp
	@cd $(BIN); ./$(EXECUTABLE) tmp ../tapes/testTape.txt 1000

createCommonTape:
	@cd $(BIN); ./tapeGenerator 100000 ../tapes/testTape.txt

build: tapeGenerator main
	@echo "\n-Building executable\n"
	cd $(BUILD); $(CXX) $(CXX_FLAGS) -o ../$(BIN)/$(EXECUTABLE) exec.o
	@echo "\n\nBuild successful!"

main: slowTape.o
	@echo "\n--Building main\n"
	$(CXX) $(CXX_FLAGS) -c $(SRC)/main.cpp -o $(BUILD)/main.o
	cd $(BUILD); ld -r -o exec.o slowTapeR.o main.o; rm slowTapeR.o main.o

clean:
	clear
	@echo "Clearing.."
	@find $(BUILD) -maxdepth 1 -type f -delete
	@find $(BIN) -maxdepth 1 -type f -delete
	@rm -rf $(BIN)/*
	@rm -rf $(BUILD)/*

tapeGenerator:
	@echo "\n--Building TapeGenerator"
	$(CXX) $(CXX_FLAGS) $(SRC)/TapeGenerator.cpp -o $(BIN)/tapeGenerator

slowTape.o: exceptions.o
	@echo "\n--Building SlowTape"
	$(CXX) $(CXX_FLAGS) -c $(SRC)/slowTape.cpp -o $(BUILD)/slowTape.o
	@cp $(SRC)/TapeInterface.hpp $(BUILD)/
	@cd $(BUILD); ld -r -o slowTapeR.o slowTape.o exceptions.o; rm slowTape.o exceptions.o

exceptions.o:
	@echo "\n--Building exceptions"
	$(CXX) $(CXX_FLAGS) -c $(EXCEPTIONS_DIR)/$(IO_EX).cpp -o $(BUILD)/$(IO_EX).o
	$(CXX) $(CXX_FLAGS) -c $(EXCEPTIONS_DIR)/$(LOAD_EX).cpp -o $(BUILD)/$(LOAD_EX).o
	$(CXX) $(CXX_FLAGS) -c $(EXCEPTIONS_DIR)/$(EMPTY_EX).cpp -o $(BUILD)/$(EMPTY_EX).o
	$(CXX) $(CXX_FLAGS) -c $(EXCEPTIONS_DIR)/$(CONFIG_EX).cpp -o $(BUILD)/$(CONFIG_EX).o
	@mkdir -p $(BUILD)
	cd build; ld -r -o exceptions.o $(EXCEPTIONS_OBJ); rm $(EXCEPTIONS_OBJ)
