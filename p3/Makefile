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

p3.c: p3.o tmeas.o
	$(LOADER) $(OPT) p3.o tmeas.o -o p3 $(LIB)

# how to obtain a file myprogram.o

p3.o:
	$(CCOMP) -c $(OPT) p3.c $(INC)
tmeas.o: tmeas.c
	$(CCOMP) -c $(OPT) tmeas.c $(INC)

clean:
	rm -f *.o