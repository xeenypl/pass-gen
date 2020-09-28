CC = gcc
CCFLAGS = -Wall -Wextra -pedantic -O3

PREFIX = /usr/local

pass-gen: pass-gen.c
	$(CC) $(CCFLAGS) -o pass-gen pass-gen.c

.PHONY: install
install: pass-gen
	cp pass-gen $(PREFIX)/bin/

.PHONY: uninstall
uninstall:
	rm $(PREFIX)/bin/pass-gen

