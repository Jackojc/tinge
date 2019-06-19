CXX=g++
STD=c++17

INCLUDE=-I..
LIBS=

BUILD_DIR=build
TARGET=test

WFLAGS=-Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=5 -Wundef -Wno-unused

CXXFLAGS=$(CXXFLAGS) -msse2 -march=native -m64

COMMAND=$(CXX) --std=$(STD) $(WFLAGS) $(INCLUDE)

all:
	mkdir -p $(BUILD_DIR)
	$(COMMAND) $(DEBUG_FLAGS) -c wip.cpp -o $(BUILD_DIR)/main.o
	$(COMMAND) $(DEBUG_FLAGS) build/*.o $(LIBS) -o $(BUILD_DIR)/$(TARGET)



