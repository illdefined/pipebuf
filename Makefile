CPPFLAGS += -D_GNU_SOURCE

DESTDIR ?= /
PREFIX ?= usr/local

pipebuf: pipebuf.c

bin := $(DESTDIR)$(PREFIX)/bin

install: $(bin)/pipebuf

$(bin)/pipebuf: $(bin) pipebuf
	cp -p $(@F) $(@D)

$(bin):
	mkdir -p $@

.PHONY: install
