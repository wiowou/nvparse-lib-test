# CC=g++
# CFLAGS=-Wall -g
# LIBDIR=../libs
# INC=-I$(LIBDIR)
# ODIR=obj

# SRCS=main.cpp
# OBJS=$(subst .cpp,.o,$(SRCS))

# templatefill: $(ODIR)/main.o 
# 	@$(CC) -o templatefill $(ODIR)/main.o -static

# #use this as a template when adding a source file to the project
# $(ODIR)/main.o: main.cpp obdir
# 	@$(CC) -c $(CFLAGS) $(INC) main.cpp -o $@

# obdir:
# 	@mkdir -p $(ODIR)

# clean:
# 	@rm -f $(ODIR)/*.o

OUT = test
CC = g++
CFLAGS=
ODIR = obj
SDIR = ./src
INC = -I./libs

_OBJS = main.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJS))

$(ODIR)/%.o: $(SDIR)/%.cpp 
	$(CC) -c $(INC) -o $@ $< $(CFLAGS) 

$(OUT): $(OBJS) 
	$(CC) -o $(OUT) $(CFLAGS) $^ -static

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(OUT)
	rm -f test