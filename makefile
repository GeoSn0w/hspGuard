CC = gcc
TARGET = hspGuard

all : $(TARGET)

$(TARGET) : hspGuard.c
	$(CC) hspGuard.c -o $(TARGET)

clean :
	rm -rf $(TARGET)
