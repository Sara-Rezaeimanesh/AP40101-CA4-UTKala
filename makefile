IDIR=./include
ODIR=./obj
SDIR=./src

CC= g++ -std=c++11
CCFLAGS= -Wall -Werror -pedantic -I$(IDIR)

_DEPS= Book.hh Document.hh Library.hh Magazine.hh \
Person.hh Professor.hh Reference.hh Student.hh

DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ= main.o Book.o Document.o Library.o Magazine.o Person.o \
Professor.o Reference.o Student.o

OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all clean

all: dir main
	echo $(OBJ)

dir:
	mkdir -p $(ODIR)

main: $(OBJ)
	$(CC) $(CCFLAGS) $^ -o $@

$(ODIR)/%.o: $(SDIR)/%.cc $(DEPS)
	$(CC) $(CCFLAGS) -c $< -o $@

$(ODIR)/main.o: main.cc $(DEPS)
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -f $(ODIR)/*.o ./main
