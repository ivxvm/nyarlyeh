CC      = gcc
CFLAGS  = -g
RM      = rm -f


default: all

all: nyarlyeh

nyarlyeh: nyarlyeh.c
	$(CC) $(CFLAGS) -o nyarlyeh nyarlyeh.c

clean veryclean:
	$(RM) nyarlyeh
