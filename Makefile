CC = gcc
CXX = g++
TARGET = CG_EXE
LDFLAGS += -lGL -lGLU -lglut -lX11

.PHONY: all

all: $(TARGET)
	./$(TARGET)

$(TARGET): ${file}
	$(CXX) $< -o $(TARGET) $(LDFLAGS)
