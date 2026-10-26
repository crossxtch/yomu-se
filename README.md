# yomu

XTCH reader for the Xteink X3, X4, and X4 Classic. This checkout is `yomu-se`. On the device the name is yomu. Books are `.xtc` and `.xtch` files on the SD card: pre-rendered page bitmaps. `.xtc` is 1-bit black and white. `.xtch` is 2-bit grayscale. This firmware blits them. It does not lay out text or scale pages.

One firmware binary per device. Pages are rendered for that panel:

| Device     | Panel (landscape) | UI / pages (portrait) |
| ---------- | ----------------- | --------------------- |
| X3         | 792×528           | 528×792               |
| X4         | 800×480           | 480×800               |
| X4 Classic | 800×480           | 480×800               |

## Layout

```
src/main.cpp          boot + loop
src/core/             screen stack, input, settings, power, list UI
src/screens/          home, browser, reader, chapters, settings, update
src/platform/         chip workarounds
lib/hal               hardware wrappers
lib/Gfx               portrait framebuffer + UI text
lib/Xtch              XTC/XTCH container + page blit
lib/EpdFont           Ubuntu UI fonts
reference/            CrossPoint submodule (lookup only)
freeink-sdk/          display and board support
```

Settings and per-book progress live in `/.yomu` on the SD card. A card that still has `/.crossxtch` is renamed to `/.yomu` on boot.
Boot and runtime logs go to the Serial console only (no SD log file).

Firmware update from SD (same idea as CrossPoint):

- Settings → **Update firmware** → pick a `.bin` → confirm.
- Recovery picker: hold **up + power** at wake on the X3 and X4. On the X4 Classic hold **down + power** (up is the GPIO0 strap). Back returns to home.

Flash the matching env's `.bin`. The X4 Classic is a separate ESP32-S3 image from the C3 X4, even though the page size matches. The stock Xteink updater is gone once this firmware is installed.

## Build

Default env is `x3`. Separate binary per device — do not combine them.

```bash
pio run              # env:x3
pio run -e x4
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

GitHub Actions builds `yomu-x3.bin`, `yomu-x4.bin`, and `yomu-x4c.bin` and attaches them to a GitHub Release for that tag.

Optional `platformio.local.ini` for a local upload port (gitignored).

`reference/` is the CrossPoint Reader tree. Do not build it as this product.

```bash
git submodule update --init --recursive
```
