PROG = test

OBJS = test.o shanks_tonelli.o

CC = gcc
CPFLAGS = -Wall -Wpointer-arith -O2


test: test.o shanks_tonelli.o
	$(CC) $(CPFLAGS) -o test  test.o shanks_tonelli.o

test.o: shanks_tonelli.h test.h test.c
	$(CC) $(CPFLAGS) -c test.c

shanks_tonelli.o: shanks_tonelli.c shanks_tonelli.h
	$(CC) $(CPFLAGS) -o shanks_tonelli.o -c shanks_tonelli.c

clean:
	rm -f $(OBJS)