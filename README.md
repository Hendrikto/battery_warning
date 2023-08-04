# battery_warning
Issue a warning if the battery capacity drops too low.

## Build
```sh
make
```

Sensible defaults are chosen for the systemd service file during generation. It might be necessary to edit `battery_warning@.service`.

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
systemctl start battery_warning@<username>.service
systemctl enable battery_warning@<username>.service # optional
```

### Security

It is advisable to run the battery warning service as a non-privileged user.
