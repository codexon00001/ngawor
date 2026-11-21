CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic
SRC      = src/main.cpp src/AlatLaboratorium.cpp
TARGET   = inventaris

all: $(TARGET)

$(TARGET): $(SRC) src/AlatLaboratorium.hpp
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

test: $(TARGET)
	bash tests/uji_manual.sh

clean:
	rm -f $(TARGET)

.PHONY: all test clean
