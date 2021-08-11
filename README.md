# The Herald

## _An ESP-32 project to convert Alphanumeric Characters to Morse_

The project is an HTTP server, using the esp-idf API, produced by Espressif itself, which will be located directly on the ESP-32, and uses two peripherals: wi-fi, to locate itself on the network and receive the information posted on the server, and low-energy bluetooth, to transfer this information via a GATT table to nearby devices. The project focuses mainly on ESP, due to the character of the subject, so if it were implemented, the HTTP client side could be developed, through a web page, and the bluetooth client, a device that would handle the received information and transform it into planned vibrations. In this case, the terminal was used to demonstrate the HTTP methods and the nRF Connect application, to observe the BLE information.
As for the design organization, only the ESP-IDF API was used, together with the text editor VSCode and the Espressif extension. Several components were used to separate and modularize the project, as is Espressif's recommendation. One for the HTTP server, another for bluetooth and the third for wi-fi management. Below, the project's file tree:

```
📦components
 ┣ 📂ble
 ┃ ┣ 📂include
 ┃ ┃ ┗ 📜ble.h
 ┃ ┣ 📜CMakeLists.txt
 ┃ ┣ 📜Kconfig.projbuild
 ┃ ┗ 📜ble.c
 ┣ 📂httpServer
 ┃ ┣ 📂include
 ┃ ┃ ┗ 📜httpServer.h
 ┃ ┣ 📜CMakeLists.txt
 ┃ ┣ 📜Kconfig.projbuild
 ┃ ┗ 📜httpServer.c
 ┗ 📂wifiStation
 ┃ ┣ 📂include
 ┃ ┃ ┗ 📜wifiStation.h
 ┃ ┣ 📜CMakeLists.txt
 ┃ ┣ 📜Kconfig.projbuild
 ┃ ┗ 📜wifiStation.c
 📦main
 ┣ 📂include
 ┃ ┣ 📜info.h
 ┃ ┗ 📜translate.h
 ┣ 📜CMakeLists.txt
 ┣ 📜chip_info.c
 ┣ 📜main.c
 ┗ 📜translate.c
 📜CMakeLists.txt
 📜README.md -> This is the file that you're currently reading
```

This project does not contains Makefile and component.mk files, used for the legacy Make based build system.
They are not used or needed when building with CMake and idf.py.
