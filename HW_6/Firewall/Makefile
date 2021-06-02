CFLAGS= -g -Wall -c -fpic
CLINK=$(CC)
CC     = g++
CPPLIBS = -fpic -shared
CLIBS = -shared
RM = rm -rf *.o *.exe
CPPS = ip.cpp field.cpp port.cpp string.cpp
OBJ = ip.o field.o port.o string.o
LIB = libfirewall.so


firewall.exe: $(LIB) $(OBJ) $(CPPS) main.o
	$(CC)  -g -Wall $(OBJ) main.o -o firewall.exe -L. -lfirewall -L. -linput

libfirewall.so: $(OBJ)
	$(CLINK) $(CLIBS) $(OBJ) -o $(LIB)

port.o: port.cpp port.h field.o
	$(CC) $(CFLAGS)   port.cpp

ip.o:  ip.h ip.cpp field.o
	$(CC) $(CFLAGS)   ip.cpp

field.o: string.cpp  field.cpp field.h
	$(CC) $(CFLAGS)   field.cpp

string.o: string.cpp string.h
	$(CC) $(CFLAGS)   string.cpp

main.o: main.cpp string.h ip.h input.h port.h
		$(CC) -g -Wall -c -c -fpic main.cpp

clean:
	$(RM) $(LIB)