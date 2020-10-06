cc=gcc
CFLAGS=-g -Wall
OBJS=entropy_calculator_for_image_main.o
OBJDIR=./obj
BINDIR=../bin
TARGET=entropy_calculator


$(OBJDIR)/%.o: %.c
	$(CC) -o $(OBJDIR)/$@ %.c

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)

clean:
	rm -f *.o
	rm -f $(TARGET)