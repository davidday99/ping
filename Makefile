SRC = src
INC = inc
OBJ = obj
ODIR = bin
ONAME = ping

SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(addprefix $(OBJ)/, $(notdir $(SRCS:.c=.o)))

CC = gcc
DEBUGGER = gdb
RM      = rm -rf
MKDIR   = @mkdir -p $(@D)
CFLAGS = -I$(INC) -g3

all: $(ODIR)/$(ONAME)

debug:
	$(DEBUGGER) --tui $(ODIR)/$(ONAME)

clean:
	-$(RM) $(OBJ)
	-$(RM) $(ODIR)
	-$(RM) $(EOBJ)

$(ODIR)/$(ONAME): $(OBJS)
	$(MKDIR)
	$(CC) -o $(ODIR)/$(ONAME) $^ $(CFLAGS)

$(OBJ)/%.o: $(SRC)/%.c
	$(MKDIR)   
	$(CC) -o $@ $^ -c $(CFLAGS)

.PHONY: clean

