## UDP Encrypt-Decrypt with 100 GbE NIC
This repository contains the necessary source files for sending and receiving UDP packets with a specified size through the 100 GbE network in OCT. It should be noted that the transmission and reception of UDP packets is executed by the host, rather than the FPGA as explained in the [udp-network-demo](https://github.com/OCT-FPGA/udp-network-demo). 
Additionally, software-based AES encryption and decryption can be used to encrypt and decrypt messages, similar to the approach taken in the udp-network-demo. There are three programs in this repository:

sender: This program reads a file, optionally encrypts and sends it over UDP to the receiver. 

receiver: This program receives the file over UDP and optionally decrypts. 

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
$ ./receiver <number_of_packets> <decrypt|no-decrypt> 
```
Finally, start the sender program on the sending machine:

```bash
$ ./sender <number_of_packets> <encrypt|no-encrypt> <receiver IP>
```

The packet capture program will print the size of each received packet.

Note: Make sure that the receiver machine is running the packet capture program and that the receiver IP address is correct.
