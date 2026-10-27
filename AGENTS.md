# Agent notes

Code and comments are the record. When a change makes an existing doc wrong, update that doc in the same change. Do not add a doc or a comment that restates the code.

`README.md` is the user-facing doc. Keep its device, build, and recovery text aligned with the code. Leave implementation detail in the source.

`freeink-sdk/` is a submodule. Do not change it.

- Do not edit files under `freeink-sdk/`, including its nested `lucide` submodule.
- Do not move the pin. yomu builds against the commit recorded in the parent repository.
- If yomu needs a fix or a newer piece of SDK code, vendor it into `lib/` and point the build at that copy. `lib/EInkDisplay` is already vendored this way; `platformio.ini` symlinks the other hardware libraries from the submodule. Copy the library you need to change, switch its `lib_deps` entry off the symlink, and leave the submodule alone.
