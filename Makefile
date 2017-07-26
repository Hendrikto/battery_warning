all: install

install: battery_warning
	sudo ln -rs $< /usr/local/bin
	sudo ln -rs $<.service /etc/systemd/system

uninstall:
	sudo rm -r /usr/local/bin/battery_warning
	sudo rm -r /etc/systemd/system/battery_warning.service
