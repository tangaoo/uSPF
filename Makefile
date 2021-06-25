.PHONY: all install uninstall clean run

all:
	cd uSPF; make
	cd example; make

install:

uninstall:

clean:
	cd uSPF; make clean
	cd example; make clean

run:
	cd example; make run 