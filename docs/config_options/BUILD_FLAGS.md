# Custom Build Flags

the DDL framework supports adding custom build flags to the build process, allowing for fine-tuning of the build process.

available options are:

- `board_build.flags.common`: added to all build commands
- `board_build.flags.c`: added to C build commands only
- `board_build.flags.cpp`: added to C++ build commands only
- `board_build.flags.asm`: added to assembly build commands only
- `board_build.flags.link`: added to linker commands only


> [!TIP]
> build flags are added **after** the default flags, so you can override them if needed.

> [!IMPORTANT]
> only set extra build flags if you know what you're doing.
> incorrect build flags can cause the build to fail, or the firmware to behave incorrectly.


## Setting Custom Build Flags

platformio.ini:
```ini
[env:myenv]
# ...
board_build.flags.cpp =
	-fno-threadsafe-statics
	-fno-exceptions
```
