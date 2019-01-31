
#CC = i686-w64-mingw32-g++
CC = g++
OPT = -I../lua/include -L../lua/lib
LIB = lua

TARGETS = call.exe

all : $(TARGETS)

%.exe : %.cpp
	#$(CC) $(OPT) $< -o $@
	$(CC) $(OPT) -l$(LIB) $< -o $@

clean:
	rm *.exe
