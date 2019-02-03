
#CC = i686-w64-mingw32-g++
#CC = i686-w64-mingw32-gcc
CC = g++
OPT = -I../lua/include -L../lua/lib
LIB = -llua

TARGETS = call.exe from_lua.exe get_table.exe return_multi.exe

all : $(TARGETS)

%.exe : %.cpp
	$(CC) $(OPT) -o $@ $< $(LIB)

clean:
	rm *.exe
