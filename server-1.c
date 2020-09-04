/* A simple server in the internet domain using TCP
   The port number is passed as an argument */


/* Defines headers to be used within the network *\
/* defines input and output statements. *\
#include <stdio.h>

/* Defines data types used in C. *\
#include <sys/types.h> 

/* Defines structures required for sockets. *\
#include <sys/socket.h>

/* Defines the structures and constants required for IP addresses. *\
#include <netinet/in.h>

/* Displays and error message, with details, when a system call fails, and terminates the program. *\
void error(char *msg)
{

    perror(msg);

    exit(1);


/* Store values, returned by system calls. *\
} 

int main(int argc, char *argv[])
{

/* portno stores the port used to accept connections. *\
/* clien stores the size of the IP address. *\

     int sockfd, newsockfd, portno, clilen;


/* Stores characters read from connections. *\
     char buffer[256];


/* Structure containg internet addresses. *\

     struct sockaddr_in serv_addr, cli_addr;

     int n;

     if (argc < 2) {


         fprintf(stderr,"ERROR, no port provided\n");

         exit(1);

     }


/* Creates a socket using arguments, consisting of the address domain and socket type, before creating an entry in the file descriptor table. *\ 
     sockfd = socket(AF_INET, SOCK_STREAM, 0);

     if (sockfd < 0)
 
        error("ERROR opening socket");


/* Sets all the values in the buffer using the size of the buffer and pointer. *\
     bzero((char *) &serv_addr, sizeof(serv_addr));

/* Converts the listening port to a string. *\

     portno = atoi(argv[1]);


/* Defines the family of addresses to be used. *\
     serv_addr.sin_family = AF_INET;

/* Contains the IP address of the server and host. *\

     serv_addr.sin_addr.s_addr = INADDR_ANY;

     serv_addr.sin_port = htons(portno);



/* Attaches the sockets to the host and port number to run on the server. *\
     if (bind(sockfd, (struct sockaddr *) &serv_addr,

              sizeof(serv_addr)) < 0)
 
              error("ERROR on binding");

     listen(sockfd,5);

     clilen = sizeof(cli_addr);

     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

     if (newsockfd < 0)
 
          error("ERROR on accept");

     bzero(buffer,256);

     n = read(newsockfd,buffer,255);

     if (n < 0) error("ERROR reading from socket");

     printf("Here is the message: %s\n",buffer);

     n = write(newsockfd,"I got your message",18);

     if (n < 0) error("ERROR writing to socket");

     return 0; 
}
