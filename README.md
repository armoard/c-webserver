# C-WebServer

A simple web server written in C that utilizes sockets to handle HTTP requests. This project supports both Linux and Windows platforms.

Currently, it focuses on processing HTTP methods and the request body, in the future im going to try adding support for authorization headers and additional request information.

---

## Requirements

To compile and run the project, you need:

- **Linux**:
   - `GCC` (GNU Compiler Collection)
   - `Make` (build automation tool)

- **Windows**:
   - `GCC` (MinGW or MSYS2)
   - `ws2_32` library (required for Windows sockets)

---

## Installing the Requirements

### **Linux**
If **GCC** or **Make** are not installed, you can install them with the following commands:

#### Debian-based systems (Ubuntu, Debian, etc.):
```bash
sudo apt update
sudo apt install build-essential
```
### **Windows**

Go to the MinGW-w64 official website and download the installer, follow the instructions to install MinGW-w64.

## Compilation and Execution

### **Linux**

Open a terminal in the project directory, and execute the command: 

    make run

For cleaning the objects, you can run:

    make clean

### **Windows**

Open a terminal in the project directory.  
Compile the server using GCC:
```bash
gcc webserverwindows.c server.c helpers/csv_utils.c helpers/hex_utils.c 
    helpers/encode_utils.c helpers/binary_text.c helpers/string_inspect.c 
    helpers/convert_bytes.c -o webserver.exe -lws2_32

Run the server:
    ./webserver.exe
```

## Running the Server

Once the server is running, it listens on port 8080 by default,open your browser and navigate to:

    http://localhost:8080

You can change the default port in config.h