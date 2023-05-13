# Makefile for compiling the sender, receiver, and packet_capture programs

CC = gcc
CFLAGS = -Wall
LIBS = -lpcap

all: sender receiver packet_capture

sender: sender.c
	$(CC) $(CFLAGS) $(LIBS) -o sender sender.c

receiver: receiver.c
	$(CC) $(CFLAGS) $(LIBS) -o receiver receiver.c

packet_capture: packet_capture.c
	$(CC) $(CFLAGS) $(LIBS) -o packet_capture packet_capture.c

clean:
	rm -f sender receiver packet_capture
