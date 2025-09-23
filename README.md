# Raspberry Pi Pico with ThreadX

A small example of using [ThreadX] on a [Raspberry Pi Pico][Pico].

The example is set up to use another Raspberry Pi Pico as a
[debug probe][debugprobe].

The purpose of this example is to support the development of the VS Code
[RTOS Views] plugin. The plugin is part of the [Cortex-Debug] plugin, but is
still missing support for ThreadX.

[Pico]: https://www.raspberrypi.com/products/raspberry-pi-pico/
[ThreadX]: https://threadx.io/
[debugprobe]: https://github.com/raspberrypi/debugprobe/
[Cortex-Debug]: https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug
[RTOS Views]: https://marketplace.visualstudio.com/items?itemName=mcu-debug.rtos-views
