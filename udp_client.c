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
	struct sockaddr_in serverAddr;
	socklen_t addr_size;
	uint32_t tid_nu, tid_kommen;

	sockfd=socket(PF_INET, SOCK_DGRAM, 0);
	
	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons(port);
	
	// Upplkolping
    inet_pton(AF_INET, "localhost",&serverAddr.sin_addr);


	// Skicka tomt
 	sendto(sockfd, NULL, 0, 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));


	addr_size=sizeof(serverAddr);



	recvfrom(sockfd, &tid_nu, sizeof(tid_nu), 0, (struct sockaddr*)&serverAddr, &addr_size);

	 // Convert time to host byte order
    tid_kommen = ntohl(tid_nu);

    // Subtract seconds from Jan 1, 1900 to Jan 1, 1970
    time_t curr_tid = tid_kommen - 2208988800UL;

    // Convert time to readable format
    char *tid_str = ctime(&curr_tid);

    // Print time
    printf("[+]Data received: %s", tid_str);

	
}
