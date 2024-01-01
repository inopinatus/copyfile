.PHONY: all install uninstrall clean

PREFIX ?= /usr/local
BINDIR ?= $(PREFIX)/bin
MANDIR ?= $(PREFIX)/share/man/man1
INSTALL ?= install

SOURCES = copyfile.c

all: copyfile

copyfile: $(SOURCES)
	$(CC) -o $@ $<

install: copyfile
	$(INSTALL) -v -C -m 755 copyfile $(BINDIR)/copyfile
	$(INSTALL) -v -C -m 644 copyfile.1 $(MANDIR)/copyfile.1

uninstall:
	rm -f $(BINDIR)/copyfile
	rm -f $(MANDIR)/copyfile.1

clean:
	rm -f copyfile
