CC = gcc
CFLAGS += -Wall -Wextra -O3 -march=native

SUBSTITUTIONS += ";s/{{display}}/$(DISPLAY)/"

all: install

%: %.c
	$(CC) $(CFLAGS) $< -o $@

%: %.template
	sed $(SUBSTITUTIONS) $< > $@

clean:
	rm -f battery_warning battery_warning.service

install: battery_warning battery_warning.service
	sudo mv $< /usr/local/bin
	ln -rs $<.service ~/.config/systemd/user

uninstall:
	sudo rm -f /usr/local/bin/battery_warning
	rm -f ~/.config/systemd/user/battery_warning.service
