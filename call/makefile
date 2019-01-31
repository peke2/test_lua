
CC = i686-w64-mingw32-g++
OPT = -I../lua/include -L../lua/lib
LIB = lua51

TARGETS = call.exe

all : $(TARGETS)

%.exe : %.cpp
	$(CC) $(OPT) $< -o $@
	#$(CC) $(OPT) -l$(LIB) $< -o $@

clean:
	rm *.exe
