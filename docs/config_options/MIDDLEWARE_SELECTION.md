# Middleware Selection

middleware is a collection of libraries that provide additional functionality to the HC32F460.
this can include things like sd card support, audio codec support, and more.


## Enabling / Disabling Middleware

middleware must be enabled before they can be used.
this is done by setting the `mw` option in the board configuration, either in the board definition file, or in the platformio.ini file.

middleware not specified will be disabled by default.


platformio.ini:
```ini
[env:my_env]
# ...
board_build.mw.sd_card = true
```

board.json:
```json
{
  // ...
  "build": {
    // ...
    "mw": {
      "sd_card": "true"
    }
  }
}
```


## List of Available Middleware

the following middleware are available in the HC32F460 DDL framework:

| middleware | description                    |
| ---------- | ------------------------------ |
| `sd_card`  | sd card / sdmmc middleware     |
| `w25qxx`   | w25qxx flash memory middleware |
| `wm8731`   | wm8731 audio codec middleware  |

> [!TIP]
> middleware is placed in the `middleware` directory of the HC32F460 DDL framework.
