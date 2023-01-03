IDIR=./include
ODIR=./obj
SDIR=./src

CC= g++ -std=c++11
CCFLAGS= -Wall -Werror -pedantic -I$(IDIR)

_DEPS= Buyer.hpp CommandHandler.hpp define.hpp UTKala.hpp \
Seller.hpp User.hpp

DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ= main.o Buyer.o CommandHandler.o define.o UTKala.o \
Seller.o User.o

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
