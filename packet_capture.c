#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ether.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <pcap.h>

#define MAX_PACKETS 1000

void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet);

int main(int argc, char *argv[]) {
    char *dev = "enp175s0";  // interface to capture packets from
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    int packet_count = 0;
    
    // open the interface for capturing packets
    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Error opening interface: %s\n", errbuf);
        exit(1);
    }
    
    // capture packets
    pcap_loop(handle, MAX_PACKETS, packet_handler, (u_char *)&packet_count);
    
    // close the interface
    pcap_close(handle);
    
    return 0;
}

void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    int packet_count = *(int *)args;
    pcap_t *handle = (pcap_t *)args;
    //printf("Packet #%d, Size: %d\n", ++packet_count, header->len);
    
    // Ethernet frame info
    struct ether_header *eth_header = (struct ether_header *) packet;
    /*printf("Source MAC: %s\n", ether_ntoa((const struct ether_addr *)&eth_header->ether_shost));
    printf("Destination MAC: %s\n", ether_ntoa((const struct ether_addr *)&eth_header->ether_dhost));
    */    
    // IP header info
    struct iphdr *ip_header = (struct iphdr*)(packet + sizeof(struct ether_header));
    /*printf("Source IP: %s\n", inet_ntoa(*(struct in_addr *)&ip_header->saddr));
    printf("Destination IP: %s\n", inet_ntoa(*(struct in_addr *)&ip_header->daddr));
    printf("IP Protocol: %d\n", (unsigned int)ip_header->protocol);
    */
    // UDP header info
    if (ip_header->protocol == IPPROTO_UDP) {
        struct udphdr *udp_header = (struct udphdr *)(packet + sizeof(struct ether_header) + sizeof(struct iphdr));
        //printf("Source Port: %d\n", ntohs(udp_header->source));
        //printf("Destination Port: %d\n", ntohs(udp_header->dest));
        printf("UDP Length: %d\n", ntohs(udp_header->len));
	int payload_size = ntohs(udp_header->len) - sizeof(struct udphdr);
	printf("Packet #%d, Payload Size: %d\n", ++packet_count, payload_size);
    }
    *(int *)args = packet_count;		
}

