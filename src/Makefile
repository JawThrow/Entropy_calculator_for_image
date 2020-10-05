cc=gcc
CFLAGS=-g -Wall
OBJS=./obj/entropy_calculator_for_image_main.o
TARGET=../bin/entropy_calculator

$(TARGET): $(OBJS)	$(CC) -o $@ $(OBJS)

all: $(TARGET)

clean:	rm $(OBJS) $(TARGET)