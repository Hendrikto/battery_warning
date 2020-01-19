# battery_warning
Issue a warning if the battery capacity drops too low.

## Build
```sh
make
```

Sensible defaults are chosen for the systemd service file during generation. It might be necessary to edit `battery_warning.service`.

## Install
```sh
sudo make install
```

## Uninstall
```sh
sudo make uninstall
```

## Usage
```sh
systemctl start battery_warning.service
systemctl enable battery_warning.service # optional
```

### Security

The included systemd service runs as root by default. You are advised to add a drop-in configuration file inside of `/etc/systemd/system/battery_warning.service.d/` to override this, which should contain something like the following:

```
[Service]
User=hendrik
```
