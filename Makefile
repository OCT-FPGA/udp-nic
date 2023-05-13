# Makefile for compiling the sender, receiver, and packet_capture programs

CC = gcc
CFLAGS = -Wall

all: sender receiver packet_capture

sender: sender.c
	$(CC) $(CFLAGS) -o sender sender.c

receiver: receiver.c
	$(CC) $(CFLAGS) -o receiver receiver.c

packet_capture: packet_capture.c
	$(CC) $(CFLAGS) -lpcap -o packet_capture packet_capture.c

clean:
	rm -f sender receiver packet_capture
