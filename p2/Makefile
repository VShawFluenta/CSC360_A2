CC=gcc
CFLAGS=-I -g -Wall
LDFLAGS=-pthread
OBJECTS = main2.o Queue.o
TARGET = ACS

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

include depends

depends:
	$(CC) -MM $(OBJECTS:.o=.c) > depends

clean:
	rm $(TARGET) *.o
	rm main2.o