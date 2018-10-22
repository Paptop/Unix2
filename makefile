CC = g++
CFLAGS = -std=c++11 -g -Wall
TARGET = ijsh

all: $(TARGET) 

$(TARGET): pcall.cpp main.cpp
	$(CC) $(CFLAGS) -o $(TARGET) pcall.cpp main.cpp

clean:
	$(RM) $(TARGET)
