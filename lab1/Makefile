#C compiler
CCOMP = gcc

#C linker
LOADER = gcc

# optymalization options
OPT = -O3

# localization of header files
INC = -I./inc

# libraries
LIB = -L../lib -lrt

# dependancies and commands
myprogram: myprogram.o tmeas.o
	$(LOADER) $(OPT) myprogram.o tmeas.o -o myprogram $(LIB)

# how to obtain a file myprogram.o
myprogram.o: 
	$(CCOMP) -c $(OPT) myprogram.c

tmeas.o: tmeas.c tmeas.h
	$(CCOMP) -c $(OPT) tmeas.c

clean:
	rm -f *.o
