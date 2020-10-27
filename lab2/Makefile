#C compiler
CCOMP = gcc

#C linker
LOADER = gcc

# optymalization options
OPT = -O3

# localization of header files
INC = -I./inc

# libraries
LIB = -L../lib -lrt -lpthread

all: exercise02_lab2 exercise03_lab2 exercise04_lab2
# dependancies and commands
exercise02_lab2: exercise02_lab2.o tmeas.o
	$(LOADER) $(OPT) exercise02_lab2.o tmeas.o -o exercise02_lab2 $(LIB)
exercise03_lab2: exercise03_lab2.o tmeas.o
	$(LOADER) $(OPT) exercise03_lab2.o tmeas.o -o exercise03_lab2 $(LIB)
exercise04_lab2: exercise04_lab2.o tmeas.o
	$(LOADER) $(OPT) exercise04_lab2.o tmeas.o -o exercise04_lab2 $(LIB)
# how to obtain a file myprogram.o
exercise02_lab2.o:
	$(CCOMP) -c $(OPT) exercise02_lab2.c $(INC)
exercise03_lab2.o:
	$(CCOMP) -c $(OPT) exercise03_lab2.c $(INC)
exercise04_lab2.o:
	$(CCOMP) -c $(OPT) exercise04_lab2.c $(INC)
tmeas.o: tmeas.c
	$(CCOMP) -c $(OPT) tmeas.c $(INC)

clean:
	rm -f *.o
