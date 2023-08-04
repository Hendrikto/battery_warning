CC = gcc
CFLAGS += -Wall -Wextra -O3 -march=native
DISPLAY ?= :0

prefix = /usr/local
systemd_prefix = /etc
substitutions = "s/{{display}}/$(DISPLAY)/g\
	;s\#{{prefix}}\#$(prefix)\#g"
nagbar_path = /usr/bin/i3-nagbar

DEFINES += -D NAGBAR_PATH=\"$(nagbar_path)\"

all: battery_warning battery_warning.service

%: %.c
	$(CC) $(CFLAGS) $(DEFINES) $< -o $@

%: %.template
	sed $(substitutions) $< > $@

clean:
	rm -f battery_warning battery_warning.service

install: battery_warning battery_warning.service
	install -D -m 755 $< $(DESTDIR)$(prefix)/bin/$<
	install -D -m 644 $<.service $(DESTDIR)$(systemd_prefix)/systemd/system/$<.service

uninstall:
	rm -f $(DESTDIR)$(prefix)/bin/battery_warning $(DESTDIR)$(systemd_prefix)/systemd/system/battery_warning.service
