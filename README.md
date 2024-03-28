# PlatformIO support for HUADA HC32F460 Series DDL

<p align="center">
    <a href="" alt="Version">
        <img src="https://img.shields.io/github/package-json/v/shadow578/framework-hc32f46x-ddl" />
    </a>
    <a href="https://github.com/shadow578/framework-hc32f46x-ddl/pulse" alt="Activity">
        <img src="https://img.shields.io/github/commit-activity/m/shadow578/framework-hc32f46x-ddl" />
    </a>
    <a href="https://github.com/shadow578/framework-hc32f46x-ddl/actions/workflows/ci.yaml">
        <img src="https://github.com/shadow578/framework-hc32f46x-ddl/actions/workflows/ci.yaml/badge.svg?branch=main" alt="ci status">
    </a>
</p>

This repository contains the [HUADA HC32F460 Series DDL](https://www.hdsc.com.cn/Category83-1487), adapted to work with [PlatformIO](https://platformio.org/) and [the hc32f46x platform](https://github.com/shadow578/platform-hc32f46x).

> [!TIP]  
> if you're searching for arduino support for HC32F460, take a look at [shadow578/framework-arduino-hc32f46x](https://github.com/shadow578/framework-arduino-hc32f46x/).

> [!NOTE]
> while the primary use-case of this framework is for use with [Marlin](https://github.com/shadow578/Marlin-H32), other use-cases should work too.


## Getting Started

to get started using the HC32F460 DDL, use the following in your `platformio.ini`:

current *development* version:
```ini
[env:my_env]
platform = https://github.com/shadow578/platform-hc32f46x.git
framework = ddl
board = generic_hc32f460
```

latest release versions:
```ini
[env:my_env]
platform = https://github.com/shadow578/platform-hc32f46x/archive/1.0.0.zip
platform_packages =
  framework-hc32f46x-ddl @ https://github.com/shadow578/framework-hc32f46x-ddl/archive/2.2.1.zip

framework = ddl
board = generic_hc32f460
```

> [!TIP]
> when pinning the version, check you're using the latest release(s) to benefit from the latest improvements.


### Examples

usage examples are available in the [examples](./examples) directory.
note that most of the official examples given by HUADA should be able to run with this framework with minimal changes.


## Configuration Options

the DDL framework supports multiple configuration options, which can be set in the `platformio.ini` file.
see the following list for a list of available configuration options and their documentation.

- [Device Driver Selection](./docs/config_options/DDL_SELECTION.md)
- [Middleware Selection](./docs/config_options/MIDDLEWARE_SELECTION.md)
- [Heap and Stack Configuration](./docs/config_options/HEAP_AND_STACK.md)
- [Boot Mode Configuration](./docs/config_options/BOOT_MODE.md)
- [Linker Script Options](./docs/config_options/LINKER_SCRIPT.md)
- [Custom Build Flags](./docs/config_options/BUILD_FLAGS.md)


## Files and Patches

mapping of HUADA DDL files to the files in this repository can be found in [docs/FILES_MAPPING.md](./docs/FILES_MAPPING.md).
more details on the patches applied to the DDL can be found in [docs/patches/README.md](./docs/patches/README.md).


## License

new code added to the DDL framework is licensed under the [GPL-3.0](./LICENSE) license, while the original DDL code is licensed under the BSD 3-Clause license.
files licensed under the BSD 3-Clause license have a header at the top of the file, specifying the license.

changes to the original DDL code are licensed under the GPL-3.0 license and documented in [docs/patches/README.md](./docs/patches/README.md).
