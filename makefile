IDIR=./include
ODIR=./obj
SDIR=./src

CC= g++ -std=c++11
CCFLAGS= -Wall -Werror -pedantic -I$(IDIR)

_DEPS= Buyer.hpp User.hpp CommandHandler.hpp define.hpp \
Seller.hpp UTKala.hpp OutputHandler.hpp

DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ= main.o User.o Buyer.o CommandHandler.o \
Seller.o UTKala.o OutputHandler.o

OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

.PHONY: all clean

all: dir main
	echo $(OBJ)

dir:
	mkdir -p $(ODIR)

main: $(OBJ)
	$(CC) $(CCFLAGS) $^ -o $@

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) $(CCFLAGS) -c $< -o $@

$(ODIR)/main.o: main.cpp $(DEPS)
	$(CC) $(CCFLAGS) -c $< -o $@

clean:
	rm -f $(ODIR)/*.o ./main
