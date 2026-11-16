# Power Off

Safe shutdown app for CardputerZero. Flipping the power switch while Linux is running can corrupt the
SD card; this app shuts the system down cleanly first.

| Key | Action |
| --- | --- |
| `4` / `Enter` | Power off now (`systemctl poweroff`) |
| `8` | Back, without powering off |
| `ESC` (hold) | Exit |

When the green activity light stays off, it is safe to flip the power switch.

No sudo is needed: apps launched from APPLaunch run in the active seat session, where logind/polkit
allow a normal shutdown. If that is refused, the app says so and suggests `sudo poweroff`.

Built from the same LVGL/CMake template as [Jiggler](https://github.com/intGus/jiggler).

## Build

```shell
sudo apt install crossbuild-essential-arm64
cmake --workflow --preset cp0-cross-package   # -> dist/PowerOff_<version>_m5stack1_arm64.deb
```

Install on the device: `sudo apt install ./PowerOff_0.1.0_m5stack1_arm64.deb`

## License

MIT. See `LICENSE` and the asset licenses in `assets/fonts/`.
