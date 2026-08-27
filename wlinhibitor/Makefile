CC = cc
CFLAGS = -Wall -Wextra -O2
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin

TARGET = wlinhibitor
PROTOCOL_XML = protocols/idle-inhibit-unstable-v1.xml
PROTOCOL_HEADER = idle-inhibit.h
PROTOCOL_SOURCE = idle-inhibit.c

OBJECTS = wlinhibitor.o idle-inhibit.o

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $(OBJECTS) `pkg-config --libs wayland-client`

idle-inhibit.h: $(PROTOCOL_XML)
	wayland-scanner client-header $< $@

idle-inhibit.c: $(PROTOCOL_XML)
	wayland-scanner private-code $< $@

.c.o:
	$(CC) $(CFLAGS) `pkg-config --cflags wayland-client` -c $< -o $@

wlinhibitor.o: wlinhibitor.c idle-inhibit.h

idle-inhibit.o: idle-inhibit.c idle-inhibit.h

install: $(TARGET)
	mkdir -p $(BINDIR)
	install -m 755 $(TARGET) $(BINDIR)/$(TARGET)

uninstall:
	rm -f $(BINDIR)/$(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS) $(PROTOCOL_HEADER) $(PROTOCOL_SOURCE)
