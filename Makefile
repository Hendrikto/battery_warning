all: install

install: battery_warning
	sudo ln -rs $< /usr/local/bin

uninstall:
	sudo rm -r /usr/local/bin/battery_warning
