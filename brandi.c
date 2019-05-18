#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

//Arnold is the Client
//Brandi is the Server
int main(int argc, char *argv[])
{
    char incommingMessage[32];
    char outgoingMessage[32]="Error";
    int port_number;    
    port_number = atoi(argv[1]);
    int socket_filedescriptor, socket_return_filedescriptor;
    socklen_t adddressSize;
    struct sockaddr_in arnold,brandi;
    //make socket
    socket_filedescriptor = socket(AF_INET, SOCK_STREAM, 0);
    brandi.sin_family = AF_INET;
    brandi.sin_addr.s_addr = INADDR_ANY;
    brandi.sin_port = htons(port_number);

    bind(socket_filedescriptor, (struct sockaddr *) &brandi, sizeof(brandi));
    listen(socket_filedescriptor,1);  //wait for a connection
    printf("%s\n","Where you at Arnold, the cops are trying to break me. I know you'll pull through my good good friend.......");
    int e=1;
    while (e>0) { //Server remains open until error
        

        adddressSize = sizeof(arnold);
        socket_return_filedescriptor = accept(socket_filedescriptor, (struct sockaddr *) &arnold, &adddressSize);
        bzero((char *) &brandi, sizeof(brandi));
         e = read(socket_return_filedescriptor,incommingMessage,32);
         if (e < 0) printf("failed reading socket");
         printf("Arnold said: %s\n",incommingMessage);
         int serversChoice = rand()%2; //0 for S, 1 for B
         bzero(outgoingMessage,32);
         //determine Prisoner’s Dilemma
         if (incommingMessage[0]=='S') {
            if (serversChoice == 0){
                strcpy(outgoingMessage, "Brandi was silent. 1 Year each");
            }
            if (serversChoice == 1) {
                 strcpy(outgoingMessage, "Brandi betrayed. 3 for Arnold!");
            }
        }else if (incommingMessage[0]=='B') {
            if (serversChoice == 0){
                 strcpy(outgoingMessage, "Brandi was silent. 3 for Brandi");
            }
            if (serversChoice == 1) {
                strcpy(outgoingMessage, "Brandi betrayed. 2 for Each!!!!");
            }
        } else {
             strcpy(outgoingMessage, "I don't unerstand 0-o"); //theoreticaly won't be called
        }
         e = write(socket_return_filedescriptor,outgoingMessage,31);
         if (e < 0) printf("failed writing socket");
         printf("Result: %s\n",outgoingMessage);
         bzero(incommingMessage,32);
    }
    return 0; 
}
void error(char *j){};