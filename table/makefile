CC = g++
OPT = -I../lua/include -L../lua/lib
LIB = -llua

TARGETS = get_table.exe enum_table.exe

all : $(TARGETS)

%.exe : %.cpp
	$(CC) $(OPT) -o $@ $< $(LIB)

clean:
	rm *.exe
