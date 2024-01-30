Basic arduino set up
===

Install the arduino cli

`snap install arduino-cli`
`arduino-cli config init`
`arduino-cli config add board_manager.additional_urls https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json`
`arduino-cli core update-index`
`arduino-cli core install esp32:esp32`

Plug in device. Update local cache of available platforms


Install the esp32 core


