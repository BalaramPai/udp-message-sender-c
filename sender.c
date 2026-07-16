// sender.c
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>

#define PORT 8888	// Port of the host/receiver/server.

int main(int argc, char *argv[])

// argc = Argument Count
// It stores the number of command-line arguments.
//
// argv = Argument Vector
// It is an array of pointers to strings (char *).
// Each argv[i] points to the first character of one command-line argument.
//
// Example:
// ./copy file1.txt file2.txt
//
// argc = 3
//
// argv[0] --> "./copy"
// argv[1] --> "file1.txt"
// argv[2] --> "file2.txt"
//
// Therefore:
// argv[0] points to '.'
// argv[1] points to 'f'
// argv[2] points to 'f'
//
// We write char *argv[] because argv is an array whose elements are
// pointers to char (strings). When passed as a function parameter,
// the array decays to a pointer, so this is equivalent to:
//
// int main(int argc, char **argv)

{	

	if (argc!=2)
	{
		printf("Usage: %s <message>\n",argv[0]);	// This tells how to use the command line terminal (./sender "The message you want")
		return 0;
	}


	int sockfd;	// Socket File descriptor.
	// Here we create a IPv4 domain with DATAGRAM support socket.
        // The socket function returns a socket file descriptor , as this value is assigned to the sockfd varaiable.
	// SOCKET - is something that creates a communication endpoint or gateway.
	sockfd = socket(AF_INET,SOCK_DGRAM,0);   // As everything in linux is a file we need a file that helps in communication so we give the details and it gives us with 3(which is fd of comms).
	if (sockfd<0)
        {
                perror("Failed to create the socket.");
		exit(0);
        }
        
	struct sockaddr_in servaddr; 		// sockaddr_in is a structure used to store an IPv4 socket address.
    	bzero(&servaddr, sizeof(servaddr));	// The bzero() function clears the entire structure by filling all bytes with 0..
    	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");	// Converts  the  Internet  host(server)  address from the IPv4 numbers-and-dots notation into binary form (in network byte order).
								// Network byte order is the order in which the bytes are ordered to transmit.(Follows the big-endian format)-->(Largest Byte First).
    	servaddr.sin_port = htons(PORT);	// The htons() function converts the unsigned short integer hostshort from host byte order(OS) to network byte order and here we assign the port number of host.
    	servaddr.sin_family = AF_INET;		// Declare the family of protocol which is IPv4.
	// So in short to create the socket address we first clear the identifier declared with '0' then assign the (Server/Host/Reciever) address, the port number and the protocol family.

	
	// connect() requests the operating system to establish a connection
	// between our socket and the destination address stored in servaddr.
	if (connect(sockfd, (struct sockaddr *) &servaddr,sizeof(servaddr)) < 0)
	{
		perror("Error : Failed to Connect\n");
		exit(0);
	}
	
	printf("Sending Message...\n");

	// Just so that every message has a new line this micro optimisation code.
	char msg[1000];
	memset(msg,0,1000);	// Zeroing out the whole array.
	memcpy(msg,argv[1],strlen(argv[1]));
	msg[strlen(argv[1])] = '\n';
	// This above code adds a new line after every message.
	
	// Sends the custom input on the respective port(8888) in this case.
	send(sockfd,msg,strlen(msg),0);
	printf("Message Has been Sent.\n");

	return 0;
}
