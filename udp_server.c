#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

int main(int argc, char **argv){
	if(argc != 2){
		printf("Usage: %s <port>", argv[0]);
		exit(0);
	}

	int port = atoi(argv[1]);
	int sockfd;
	struct sockaddr_in si_me, si_other;
	char buffer[4]; // 4 *8 = 32 bit
	time_t tid_nu;
	socklen_t addr_size;

	sockfd=socket(AF_INET, SOCK_DGRAM, 0);
	
	memset(&si_me, '\0', sizeof(si_me));
	si_me.sin_family=AF_INET;
	si_me.sin_port=htons(port);
	si_me.sin_addr.s_addr = INADDR_ANY;

	// Koppling till klient
	bind(sockfd, (struct sockaddr*)&si_me, sizeof(si_me));

	addr_size = sizeof(si_other);
 	recvfrom(sockfd, (char *)buffer, sizeof(buffer), 0, (struct sockaddr*)&si_other, &addr_size);

	// Få tid
	tid_nu = time(NULL);
	tid_nu += 2208988800UL; // seconds from Jan 1, 1900 to Jan 1, 1970

	// Till network type
	uint32_t tid = htonl((uint32_t)tid_nu);

	// Skicka till klient
    sendto(sockfd, &tid, sizeof(tid), 0, (struct sockaddr*)&si_other, addr_size);
	
}

