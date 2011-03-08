CC = gcc
CFLAGS += -arch i386 -arch ppc

OBJS = main.o RestartShutdownLogout.o

all: macsleep

macsleep: $(OBJS)
	$(CC) $(CFLAGS) -framework Carbon -o $@ $(OBJS)

clean:
	-rm -f macsleep *.o *~ core
