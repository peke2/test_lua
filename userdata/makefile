CC = g++
OPT = -I../lua/include -L../lua/lib
LIB = -llua

TARGETS = userdata.exe

all : $(TARGETS)

%.exe : %.cpp
	$(CC) $(OPT) -o $@ $< $(LIB)

clean:
	rm *.exe
