# yomu

XTC reader for the Xteink X3 and X4 Classic. This checkout is `yomu-se`. On the device the name is yomu. Books are `.xtc` files on the SD card: pre-rendered 1-bit page bitmaps. This firmware blits them. It does not lay out text or scale pages. Panel refresh is black and white only: FAST, HALF, and FULL.

One firmware binary per device. Pages are rendered for that panel:

| Device     | Panel (landscape) | UI / pages (portrait) |
| ---------- | ----------------- | --------------------- |
| X3         | 792×528           | 528×792               |
| X4 Classic | 800×480           | 480×800               |

## Layout

```
src/main.cpp          boot + loop
src/core/             screen stack, input, settings, power, list UI
src/screens/          home, browser, reader, chapters, settings, update
src/platform/         chip workarounds
lib/hal               hardware wrappers
lib/Gfx               portrait framebuffer + UI text
lib/Xtch              XTC container + page blit
lib/EpdFont           Ubuntu UI fonts
freeink-sdk/          display and board support
```

Settings and per-book progress live in `/.yomu` on the SD card. A card that still has `/.crossxtch` is renamed to `/.yomu` on boot.
Boot and runtime logs go to the Serial console only (no SD log file).

Firmware update from SD (same idea as CrossPoint):

- Settings → **Update firmware** → pick a `.bin` → confirm.
- Recovery picker: hold **up + power** at wake on the X3. On the X4 Classic hold **down + power** (up is the GPIO0 strap). Back returns to home.

Flash the matching env's `.bin`. The X3 is an ESP32-C3 image and the X4 Classic is an ESP32-S3 image. The stock Xteink updater is gone once this firmware is installed.

## Build

Default env is `x3`. Separate binary per device — do not combine them.

```bash
pio run              # env:x3
pio run -e x4c
pio run -e x3 -t upload
pio device monitor
```

## Release

Bump `[yomu] version` in `platformio.ini` to match the tag, push `develop`, then:

```bash
git tag -a v0.1.0 -m "v0.1.0"
git push origin v0.1.0
```

GitHub Actions builds `yomu-x3.bin` and `yomu-x4c.bin` and attaches them to a GitHub Release for that tag.

Optional `platformio.local.ini` for a local upload port (gitignored).

`freeink-sdk/` is a submodule.

```bash
git submodule update --init --recursive
```
