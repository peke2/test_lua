
#CC = i686-w64-mingw32-g++
#CC = i686-w64-mingw32-gcc
CC = g++
OPT = -I../lua/include -L../lua/lib
LIB = -llua

TARGETS = seed1.exe seed2.exe seed3.exe seed4.exe seed5.exe xorshift.exe

all : $(TARGETS)

%.exe : %.cpp
	$(CC) $(OPT) -o $@ $< $(LIB)

clean:
	rm *.exe
