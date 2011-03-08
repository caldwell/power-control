all: power-control

power-control: power-control.o RestartShutdownLogout.o
power-control: LDLIBS += -framework Carbon
power-control: TARGET_ARCH += -arch i386 -arch ppc
power-control: CFLAGS += -std=gnu99
power-control: CFLAGS += -g
power-control: CFLAGS += -Wall

clean:
	-rm -f power-control *.o *~
