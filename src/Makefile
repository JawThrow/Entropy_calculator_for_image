cc=gcc
CFLAGS=-g -Wall
# object file top path
OBJDIR=./obj
# object files
OBJS=entropy_calculator_for_image_main.o

# source top path
SRCDIR=.

# bin path
BINDIR=../bin
TARGET=$(BINDIR)/entropy_calculator

vpath %.o $(addprefix $(OBJDIR)/, $(OBJS))
vpath %.c $(SRCDIR)
vpath %.h $(SRCDIR)

all: $(TARGET)

$(TARGET): $(OBJDIR)/$(OBJS)
	$(CC) -o $@ $^

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -c -o $@ $^

clean:
	rm -f $(OBJDIR)/$(OBJS)
	rm -f $(TARGET)