all: install

install: battery_warning
	sudo ln -rs $< /usr/local/bin
	sudo ln -rs $<.service /etc/systemd/system

uninstall:
	sudo rm -f /usr/local/bin/battery_warning
	sudo rm -f /etc/systemd/system/battery_warning.service
