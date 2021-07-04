CC = gcc

CFLAGS   =  -Wall -O2 -I./ 
CFLAGS  +=  -I../dep/install/include/ttlib_mirco 

# LDFLAGS = -lttlib_mirco  -L../dep/install/lib -lpthread
LDFLAGS = -luspf -L../uSPF 
LDFLAGS += -lttlib_mirco  -L../dep/install/lib
LDFLAGS += -lpthread

INSTALL = /usr/bin/install -c

TARGET=example

prefix=/usr/local
includedir=$(prefix)/include
libdir=$(prefix)/lib

lib_header_files = $(wildcard *.h)
c_files = $(wildcard *.c)
objects = $(c_files:.c=.o)

$(TARGET): $(objects)
	$(CC)  $^ -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: install uninstall clean

install:
	mkdir -p $(includedir)/uspf_demo
	cp $(lib_header_files) $(includedir)/uspf_demo
	$(INSTALL) $(TARGET) $(libdir)

uninstall:
	rm -rf $(includedir)/uspf_demo
	rm -f $(libdir)/$(TARGET)

clean:
	rm -f $(objects) $(TARGET)

run:
	./$(TARGET)