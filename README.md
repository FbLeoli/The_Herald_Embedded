# _The Embedded Project_

I don't even know what I will do in this project but, for now, I'm trying to use the ESP 32 as a HTTP Server.
Next, I will try to turn this server in a WebSocket Server, and then so on.

Below is short explanation of remaining files in the project folder.

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
