
#CC = i686-w64-mingw32-g++
CC = g++
OPT = -I../lua/include -L../lua/lib
#LIB = -llua
LIB = lua53.dll

TARGETS = call.exe from_lua.exe

all : $(TARGETS)

%.exe : %.cpp
	#$(CC) $(OPT) $< -o $@
	$(CC) $(OPT) $(LIB) $< -o $@

clean:
	rm *.exe
