# UDP String Sender in C

A simple UDP client written in **C** that sends command-line messages to a UDP receiver running on the local machine.

This project was built while learning **Socket Programming in C** and demonstrates how to create UDP sockets, prepare IPv4 socket addresses, and transmit data using the Berkeley Socket API.

The project was tested using:

- Netcat (Linux)
- Python UDP Server
- WSL (Ubuntu)

---

# Features

- UDP Client implementation in C
- IPv4 Socket Programming
- Command-line message input
- Dynamic message sending
- Compatible with any UDP receiver listening on the specified port
- Successfully tested using Netcat and Python

---

# Concepts Learned

## Networking

- Client and Server Architecture
- IPv4 Addressing
- Ports
- UDP Protocol
- Socket Programming
- Network Byte Order
- Loopback Address (127.0.0.1)

---

## Socket APIs

- socket()
- connect()
- send()
- htons()
- inet_addr()

---

## C Concepts

- Command Line Arguments (`argc`, `argv`)
- Structures
- Memory Initialization (`bzero`, `memset`)
- Memory Copy (`memcpy`)
- File Descriptors
- Error Handling (`perror`)
- String Manipulation

---

# Project Structure

```
NetworkStringSender/
│
├── sender.c          # UDP Client written in C
├── receiver.py       # Python UDP Receiver (for testing)
└── README.md
```

---

# Execution Flow

The program executes in the following order:

```
Program Starts
        │
        ▼
Validate Command Line Arguments
        │
        ▼
Create UDP Socket
        │
        ▼
Prepare sockaddr_in Structure
        │
        ├── Clear structure
        ├── Assign IP Address
        ├── Assign Port
        └── Assign Address Family
        │
        ▼
Connect UDP Socket
        │
        ▼
Prepare Message Buffer
        │
        ▼
Copy User Message
        │
        ▼
Append New Line
        │
        ▼
Send Message
        │
        ▼
Program Ends
```

---

# Networking Flow

```
                socket()
                    │
                    ▼
        Linux Kernel Creates Socket
                    │
                    ▼
            Socket File Descriptor
                    │
                    ▼
        sockaddr_in Structure
        ├── IP Address
        ├── Port
        └── Address Family
                    │
                    ▼
               connect()
                    │
                    ▼
              send()
                    │
                    ▼
          UDP Packet Created
                    │
                    ▼
          127.0.0.1 : 8888
                    │
                    ▼
             UDP Receiver
```

---

# Building

Compile using GCC.

```bash
gcc -Wall -Wextra sender.c -o sender
```

---

# Running

Run the sender by providing the message as a command-line argument.

```bash
./sender "Hello World"
```

Example

```bash
./sender "Networking in C is fun!"
```

---

# Testing Method 1 — Netcat

Netcat is an easy way to test UDP communication without writing another program.

## Terminal 1

Start a UDP listener.

```bash
nc -ukl 8888
```

Flags

- `-u` → UDP Mode
- `-k` → Keep Listening
- `-l` → Listen

---

## Terminal 2

Compile

```bash
gcc -Wall -Wextra sender.c -o sender
```

Run

```bash
./sender "Hello UDP"
```

Receiver Output

```
Hello UDP
```

Multiple executions can be tested without restarting Netcat because of the `-k` flag.

---

# Testing Method 2 — Python Receiver

Python Receiver

```python
from socket import *

serverSocket = socket(AF_INET, SOCK_DGRAM)

serverSocket.bind(('',8888))

while True:
    message,address = serverSocket.recvfrom(1024)
    print(message.decode("utf-8"))
```

Run Receiver

```bash
python3 receiver.py
```

Run Sender

```bash
./sender "Hello from C"
```

Expected Output

```
Hello from C
```

---

# Cross Language Communication

One interesting aspect of this project is that the sender is written in **C** while the receiver is written in **Python**.

```
C
│
│ UDP Packet
▼
Python
```

This demonstrates that network communication is language independent.

As long as both programs implement the UDP protocol correctly, they can communicate regardless of the programming language used.

---

# WSL Notes

The sender was developed inside **Ubuntu WSL**.

Testing was performed in two ways.

## Method 1 (Recommended)

Run both sender and receiver inside WSL.

```
WSL
├── sender.c
└── receiver.py
```

This avoids networking issues.

---

## Method 2

Sender

```
Ubuntu WSL
```

Receiver

```
Windows Python
```

Although modern versions of WSL generally forward localhost traffic correctly, Windows and WSL run in different networking environments.

Depending on the WSL version and firewall configuration, UDP packets may not always be delivered as expected.

If the Windows receiver is not receiving packets, try running the receiver inside WSL instead.

---

# Common Problems

## python command not found

Use

```bash
python3 receiver.py
```

instead of

```bash
python receiver.py
```

on Ubuntu.

---

## Receiver waits forever

This is normal.

```python
recvfrom()
```

is a blocking function.

It waits until a UDP packet arrives.

---

## Port Already In Use

Another application is already listening on port 8888.

Close the previous receiver or use another port.

---

## Firewall Issues

If testing across different machines, ensure the firewall allows UDP traffic on the chosen port.

---

# Running Across Different Devices

This project is not limited to communication on the local machine (`127.0.0.1`).

As long as both devices are connected to the same network (Wi-Fi or LAN), the sender can transmit UDP packets to another computer, laptop, tablet or phone.

## Step 1

Find the receiver's IPv4 address.

### Windows

```cmd
ipconfig
```

Look for

```
IPv4 Address
```

Example

```
192.168.0.111
```

---

### Linux / Ubuntu

```bash
hostname -I
```

or

```bash
ip addr
```

---

### Android (Termux)

```bash
ip addr
```

Look for the address under

```
wlan0
```

Example

```
192.168.0.188
```

---

## Step 2

Replace the loopback address

```c
servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
```

with the receiver's IP address.

Example

```c
servaddr.sin_addr.s_addr = inet_addr("192.168.0.188");
```

---

## Step 3

Start a UDP receiver on the destination device.

Examples

Netcat

```bash
nc -u -l 8888
```

Python

```bash
python3 receiver.py
```

---

## Step 4

Run the sender.

```bash
./sender "Hello from another device!"
```

The receiver should display the transmitted message.

---

## Requirements

For successful communication:

- Both devices should be connected to the same Wi-Fi or LAN.
- The receiver must be listening on the specified UDP port.
- Firewalls should allow UDP traffic on the chosen port.
- The sender must use the receiver's IPv4 address.

---

## Notes

`127.0.0.1` is the **loopback address**.

It always refers to the machine on which the program is currently running.

To communicate with another device, replace it with the IPv4 address of that device.

# Future Improvements

- Allow custom IP address from command line
- Allow custom port from command line
- Broadcast support
- Send files
- Send multiple packets
- Add timestamps
- Build a complete UDP chat application

---

# References

- Berkeley Socket API
- Linux Manual Pages
- Python socket module