CC      = gcc
CFLAGS  = -g
RM      = rm -f


default: all

all: nyarlyeh

nyarlyeh: ./src/nyarlyeh.c
	$(CC) $(CFLAGS) -o nyarlyeh ./src/nyarlyeh.c

clean veryclean:
	$(RM) nyarlyeh
