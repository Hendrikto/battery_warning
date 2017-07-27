CC = gcc
CFLAGS += -Wall -Wextra -O3 -march=native

all: install

battery_warning: battery_warning.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f battery_warning

install: battery_warning
	sudo ln -rs $< /usr/local/bin
	sudo ln -rs $<.service /etc/systemd/system

uninstall:
	sudo rm -f /usr/local/bin/battery_warning
	sudo rm -f /etc/systemd/system/battery_warning.service
