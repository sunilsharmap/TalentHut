CXX           = g++
RM            = -rm -f
INCPATH       = -I./
CXXFLAGS      = -g -std=gnu++1z -Wall -Wextra $(INCPATH)
TARGET        = AppLogger
OBJ           = main.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) -o $(TARGET) $(OBJ) $(CXXFLAGS)

$(OBJ): Makefile main.cpp logger.hpp

clean:
	$(RM) $(TARGET) $(OBJ) *.log

.PHONY: all, clean
