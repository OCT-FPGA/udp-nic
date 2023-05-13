#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/aes.h>

#define MAX_PACKET_SIZE 1408
#define AES_KEY_SIZE 128

void encrypt(const unsigned char *key, const unsigned char *plaintext, unsigned char *ciphertext) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, AES_KEY_SIZE, &aes_key);

    size_t i;
    for (i = 0; i < MAX_PACKET_SIZE; i += AES_BLOCK_SIZE) {
        AES_encrypt(plaintext + i, ciphertext + i, &aes_key);
    }
}

char *readFile(const char *fileName){
        FILE *file = fopen(fileName, "r");
        char *code;
        size_t n = 0;
        int c;

        if (file == NULL) return NULL; //could not open file
        fseek(file, 0, SEEK_END);
        long f_size = ftell(file);
        fseek(file, 0, SEEK_SET);
        code = (char*)malloc(f_size);
        while ((c = fgetc(file)) != EOF){
                code[n++] = (char)c;
        }
        code[n] = '\0';
	fclose(file);
        return code;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <number_of_packets> <encrypt|no-encrypt> <sender IP> <receiver IP>\n", argv[0]);
        return 1;
    }

    int numPackets = atoi(argv[1]);
    int doEncrypt = strcmp(argv[2], "encrypt") == 0 ? 1 : 0;

    int sockfd;
    struct sockaddr_in serverAddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error in socket");
        return 1;
    }

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(60000);
    serverAddr.sin_addr.s_addr = argc < 5 ? inet_addr("192.168.40.11") : inet_addr(argv[4]); // Receiver IP

    unsigned char plaintext[MAX_PACKET_SIZE];
    unsigned char ciphertext[MAX_PACKET_SIZE];
    unsigned char key[AES_KEY_SIZE / 8];
    unsigned char *ptr_packetdata = (unsigned char*) malloc(1408);
    unsigned int packet_size_total = MAX_PACKET_SIZE*numPackets;
	// Read text file
    char *code = readFile("./alice29.txt");
    for (unsigned int i = 0; i < packet_size_total; i++){
	    	ptr_packetdata[i] = code[i];
    }
    for (int i = 0; i < AES_KEY_SIZE / 8; i++) {
    		key[i] = i;
    }	

    // Set the sender IP
    struct sockaddr_in senderAddr;
    senderAddr.sin_family = AF_INET;
    senderAddr.sin_port = 50000;
    senderAddr.sin_addr.s_addr = argc < 4 ? inet_addr("192.168.40.10") : inet_addr(argv[3]); // Sender IP

    if (bind(sockfd, (struct sockaddr *)&senderAddr, sizeof(senderAddr)) < 0) {
        perror("Error in binding");
        return 1;
    }

    for (int i = 0; i < numPackets; i++) {
	unsigned char *start_ptr = ptr_packetdata + (i * MAX_PACKET_SIZE); // calculate start pointer
	memcpy(plaintext, start_ptr, MAX_PACKET_SIZE); 
        // Encrypt packet if required
        if (doEncrypt) {
            encrypt(key, plaintext, ciphertext);
        } else {
            memcpy(ciphertext, plaintext, sizeof(plaintext));
        }
        // Send packet
        sendto(sockfd, ciphertext, sizeof(ciphertext), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
        printf("Sent packet %d\n", i + 1);
    }
    close(sockfd);
    return 0;
}

