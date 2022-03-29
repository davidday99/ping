SRC = src
INC = inc
OBJ = obj
ODIR = bin
ONAME = ping

SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(addprefix $(OBJ)/, $(notdir $(SRCS:.c=.o)))

CC = gcc
DEBUGGER = gdb-multiarch
RM      = rm -rf
MKDIR   = @mkdir -p $(@D)
CFLAGS = -I$(INC) -g3 -MMD -MP
LDFLAGS = -g3

all: $(ODIR)/$(ONAME)
	sudo chown root:root $<
	sudo chmod u+s $<

debug:
	$(DEBUGGER) --tui $(ODIR)/$(ONAME)

clean:
	-$(RM) $(OBJ)
	-$(RM) $(ODIR)

$(ODIR)/$(ONAME): $(OBJS)
	$(MKDIR)
	$(CC) -o $(ODIR)/$(ONAME) $^ $(LDFLAGS) 

$(OBJ)/%.o: $(SRC)/%.c
	$(MKDIR)   
	$(CC) -o $@ $< -c $(CFLAGS)

-include $(OBJS:.o=.d)

.PHONY: clean

