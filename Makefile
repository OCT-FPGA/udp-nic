# Makefile for compiling the sender, receiver, and packet_capture programs

CC = gcc
CFLAGS = -Wall
LIBS = -lpcap
LDFLAGS = -lssl -lcrypto

all: sender receiver packet_capture

sender: sender.c
	$(CC) sender.c -o sender $(CFLAGS) $(LDFLAGS) 

receiver: receiver.c
	$(CC) receiver.c -o receiver $(CFLAGS) $(LDFLAGS)

packet_capture: packet_capture.c
	$(CC) packet_capture.c -o packet_capture $(CFLAGS) $(LIBS)

clean:
	rm -f sender receiver packet_capture
