CC=gcc
CFLAGS=-I -g -Wall
LDFLAGS=-pthread
OBJECTS = main2.o
TARGET = ASC

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	rm $(TARGET) *.o