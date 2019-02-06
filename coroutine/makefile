
CC = g++
OPT = -I../lua/include -L../lua/lib
LIB = -llua

TARGETS = co.exe simple.exe

all : $(TARGETS)

%.exe : %.cpp
	$(CC) $(OPT) -o $@ $< $(LIB)

clean:
	rm *.exe
