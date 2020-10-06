cc=gcc
CFLAGS=-g -Wall
OBJDIR=./obj
OBJS=entropy_calculator_for_image_main.o
SRCDIR=.
BINDIR=../bin
TARGET=entropy_calculator


$(OBJDIR)/$(OBJS): $(SRCDIR)/*.c
	$(CC) -o $@ $<

$(BINDIR)/$(TARGET): $(OBJDIR)/$(OBJS)
	$(CC) -c -o $@ $<

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(BINDIR)/$(TARGET)