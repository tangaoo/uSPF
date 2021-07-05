CC = gcc

CFLAGS 	+=  -Wall -O2 -fPIC -I./
CFLAGS  +=  -I../dep/install/include/ttlib_micro 

INSTALL = /usr/bin/install -c

TARGET=libuspf.a

prefix=/usr/local
includedir=$(prefix)/include
libdir=$(prefix)/lib

lib_header_files = $(wildcard *.h)
c_files = $(wildcard *.c)
objects = $(c_files:.c=.o)

$(TARGET): $(objects)
	ar -rc $(TARGET) $^ 

# 编译动态库
#   $(CC) $(LDFLAGS) $^ -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: install uninstall clean

install:
	mkdir -p $(includedir)/uspf
	cp $(lib_header_files) $(includedir)/uspf
	$(INSTALL) $(TARGET) $(libdir)

uninstall:
	rm -rf $(includedir)/uspf
	rm -f $(libdir)/$(TARGET)

clean:
	rm -f $(objects) $(TARGET)