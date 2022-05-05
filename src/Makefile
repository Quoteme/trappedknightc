CC=gcc
CFLAGS=-I.
LDIR =./lib
DESTDIR=/usr/local
PREFIX=/bin

trappedknight: trappedknight.c
	$(CC) -g -o $@ trappedknight.c

.PHONY: clean install

install:
	mkdir -p $(DESTDIR)$(PREFIX)
	install -m 755 trappedknight $(DESTDIR)$(PREFIX)

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/trappedknight

clean:
	-rm trappedknight

.PHONY: clean install uninstall
# vim: tabstop=2 shiftwidth=2 noexpandtab
