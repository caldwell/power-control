CC = gcc
CFLAGS += -arch i386 -arch ppc

OBJS = main.o RestartShutdownLogout.o

all: macsleep

macsleep: $(OBJS)
	gcc $(CFLAGS) -framework Carbon -o macsleep $(OBJS)

clean:
	-rm -f macsleep *.o *~ core
