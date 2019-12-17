#cleanup_makefile

CC	= g++
CFLAGS	= -g

all:	conv order1 order2 orderNames

conv:	convert.o conv.h
	$(CC) -o conv convert.o

order1:	calc.o order1.o conv.h
	$(CC) -o order1 order1.o calc.o

order2:	calc.o order2.o conv.h
	$(CC) -o order2 order2.o calc.o

orderNames:	calc.o orderNames.o conv.h
	$(CC) -o orderNames orderNames.o calc.o

convert.o:	cleanup_conv.cpp conv.h
		$(CC) $(CLAGS) -o convert.o -c cleanup_conv.cpp

order1.o:	cleanup_order1.cpp conv.h
		$(CC) $(CLAGS) -o order1.o -c cleanup_order1.cpp

order2.o:	cleanup_order2.cpp conv.h
		$(CC) $(CLAGS) -o order2.o -c cleanup_order2.cpp

calc.o:		cleanup_calc.cpp stdinc.h
		$(CC) $(CLAGS) -o calc.o -c cleanup_calc.cpp

orderNames.o:	cleanup_orderNames.cpp conv.h
		$(CC) $(CLAGS) -o orderNames.o -c cleanup_orderNames.cpp
