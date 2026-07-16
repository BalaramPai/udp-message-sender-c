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