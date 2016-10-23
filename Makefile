CC = gcc
CXX = g++
TARGET = CG_EXE
LDFLAGS += -lGL -lGLU -lglut -lX11
FILE = ${file}

.PHONY: all clean run

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(FILE)
	$(CXX) $< -o $(TARGET) $(LDFLAGS)

run: clean all

clean:
	$(RM) $(TARGET)
