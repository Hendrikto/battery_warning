CC = gcc
CFLAGS += -Wall -Wextra -O3 -march=native

all: battery_warning battery_warning.service install

battery_warning: battery_warning.c
	$(CC) $(CFLAGS) $< -o $@

%: %.template
	sed "s/{{user}}/$(USER)/;s/{{display}}/$(DISPLAY)/" $< > $@

clean:
	rm -f battery_warning battery_warning.service

install: battery_warning battery_warning.service
	sudo mv $< /usr/local/bin
	sudo ln -rs $<.service /etc/systemd/system

uninstall:
	sudo rm -f /usr/local/bin/battery_warning
	sudo rm -f /etc/systemd/system/battery_warning.service
