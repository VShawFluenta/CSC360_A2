CC=gcc
CFLAGS=-I -g -Wall
LDFLAGS=-pthread
OBJECTS = main2.o
TARGET = ACS

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

clean:
	rm $(TARGET) *.o
	rm main2.o