#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <unistd.h> 
#include <string.h> 

//Arnold is the Client
//Brandi is the Server

int main(int argc, char *argv[])
{
    int socket_FileDescriptor, port_number, e;

    struct sockaddr_in arnold;
    struct hostent *server;

    char outgoingMessage[32];
    char incommingMessage[32]="Error";
    port_number = atoi(argv[2]);
    socket_FileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    server = gethostbyname(argv[1]);
   
    bzero((char *) &arnold, sizeof(arnold));
    arnold.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&arnold.sin_addr.s_addr, server->h_length);
    arnold.sin_port = htons(port_number);
 if (connect(socket_FileDescriptor,(struct sockaddr *)&arnold,sizeof(arnold)) < 0) 
        printf("ERROR connecting to server");

    // get input from user now
    printf("Choose whether you will betray Brandi or stay silent. \nEnter S for Silent or B for Betray: ");
    //loop to ensure the user enters the correct letter
    while(outgoingMessage[0] != 'B' && outgoingMessage[0] != 'S'){
        bzero(outgoingMessage,32); 
        fgets(outgoingMessage,31,stdin);
        if(outgoingMessage[0] == 'b' || outgoingMessage[0] == 's' )
            printf("Only capitols please. \n");
        if(outgoingMessage[0] != 'B' && outgoingMessage[0] != 'S' && outgoingMessage[0] != 'b' && outgoingMessage[0] != 's')
            printf("Enter either S or B. \n");
    }

    e = write(socket_FileDescriptor,outgoingMessage,strlen(outgoingMessage));
    //if there's an error writing it will exit app
    if (e < 0) {
        printf("failed writing socket");
        return 0;
    }

   //outputs game result:
    bzero(incommingMessage,32);
    e = read(socket_FileDescriptor,incommingMessage,31);
    if (e < 0) 
         printf("failed reading socket");
    printf("%s\n",incommingMessage);

    return 0;
}
void error(char *j){};