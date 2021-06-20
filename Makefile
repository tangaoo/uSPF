.PHONY: all install uninstall clean update-orez

all:
	cd src; make
	cd example; make

install:

uninstall:

clean:
	cd src; make clean
	cd example; make clean

update-orez: