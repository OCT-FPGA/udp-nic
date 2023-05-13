# Makefile for compiling the sender, receiver, and packet_capture programs

CC = gcc
CFLAGS = -Wall
LIBS = -lpcap
LDFLAGS = -lssl -lcrypto

all: sender receiver packet_capture

sender: sender.c
	$(CC) -o sender sender.c $(CFLAGS) $(LDFLAGS) 

receiver: receiver.c
	$(CC) -o receiver receiver.c $(CFLAGS) $(LDFLAGS)

packet_capture: packet_capture.c
	$(CC) -o packet_capture packet_capture.c $(LIBS)

clean:
	rm -f sender receiver packet_capture
