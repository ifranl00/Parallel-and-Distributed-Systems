#C compiler
CCOMP = gcc

#C linker
LOADER = gcc

# optymalization options
OPT = -O3

# localization of header files
INC = -I./inc


# libraries
LIB = -L../lib -lrt -lpthread -lm

# dependancies and commands

p2.c: p2.o tmeas.o
	$(LOADER) $(OPT) p2.o tmeas.o -o p2 $(LIB)

# how to obtain a file myprogram.o

p2.o:
	$(CCOMP) -c $(OPT) p2.c $(INC)
tmeas.o: tmeas.c
	$(CCOMP) -c $(OPT) tmeas.c $(INC)

clean:
	rm -f *.o