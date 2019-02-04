
CC = g++
OPT = -I../lua/include -L../lua/lib
LIB = -llua

TARGETS = co.exe

all : $(TARGETS)

%.exe : %.cpp
	$(CC) $(OPT) -o $@ $< $(LIB)

clean:
	rm *.exe
