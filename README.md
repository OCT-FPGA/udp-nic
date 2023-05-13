## UDP File Transfer
This is a simple program that allows for file transfer over UDP. The program consists of three parts:

sender: This program reads a file and sends it over UDP to the receiver. It uses AES encryption to protect the file during transmission.

receiver: This program receives the file over UDP and saves it to disk. It uses AES decryption to recover the original file.

packet_capture: This program captures UDP packets on a specified interface and prints their payload size.

### Requirements
OpenSSL library (libssl-dev)
OpenSSL crypto library (libcrypto-dev)
PCAP library (libpcap-dev)

### Installation
To build the programs, use the following commands:

```bash
$ make
```
Usage
To use the programs, first start the packet capture program on the receiving machine:

```bash
$ sudo ./packet_capture
```
Next, start the receiver program on the receiving machine:

```bash
$ sudo ./receiver <filename>
```
Finally, start the sender program on the sending machine:

```bash
$ sudo ./sender <filename> <receiver_ip>
```

The file will be transmitted over UDP and saved to disk on the receiving machine. The packet capture program will print the size of each received packet.

Note: Make sure that the receiver machine is running the packet capture program and that the receiver IP address is correct.
