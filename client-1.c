/* Defines headers to be used with the program.
/* Defines input and output statements. *\
#include <stdio.h>
/* Defines the data types used in C. *\

#include <sys/types.h>

/* Defines structures required for sockets. *\
#include <sys/socket.h>


/* Defines the structures and constants required for IP addresses. *\
#include <netinet/in.h>

#include <netdb.h>


/* Displays an error message, with details, when a system call fails, and terminates the program. *\
 

void error(char *msg)
{

    perror(msg);

    exit(0);


/* Stores values, returned by system calls. *\

} 

int main(int argc, char *argv[])
{


/* "portno" stores the port used to accept requests. *\
/* "clien" stores the size of the IP address *\
    int sockfd, portno, n;


    struct sockaddr_in serv_addr;

    struct hostent *server;



/* Stores characters, read from connections. *\
    char buffer[256];

    if (argc < 3) {

       fprintf(stderr,"usage %s hostname port\n", argv[0]);

       exit(0);

    }
    portno = atoi(argv[2]);



/* Creates sockets using arguments, consisting of the address domain and socket type, before terminating the program. *\
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
 
        error("ERROR opening socket");

    server = gethostbyname(argv[1]);

    if (server == NULL) {

        fprintf(stderr,"ERROR, no such host\n");

        exit(0);

    }
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;


/* Copies addresses in the buffer and sets all values in the buffer. *\

    bcopy((char *)server->h_addr,
 
         (char *)&serv_addr.sin_addr.s_addr,

         server->h_length);



/* Converts the listening and server port to a string. *\
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
 
        error("ERROR connecting");

    printf("Please enter the message: ");

    bzero(buffer,256);

    fgets(buffer,255,stdin);

    n = write(sockfd,buffer,strlen(buffer));

    if (n < 0)
 
         error("ERROR writing to socket");

    bzero(buffer,256);

    n = read(sockfd,buffer,255);

    if (n < 0)
 
         error("ERROR reading from socket");

    printf("%s\n",buffer);

    return 0;
}
