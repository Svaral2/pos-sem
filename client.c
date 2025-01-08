#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>



int main(int argc, char* argv[]){
    int sockfd;
    struct sockaddr_in serv_addr;
    struct hostent* server;
    server = gethostbyname(argv[1]);
    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(
    (char*)server->h_addr,
    (char*)&serv_addr.sin_addr.s_addr,
    server->h_length
    );
    serv_addr.sin_port = htons(atoi(argv[2]));
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
<------>perror("Nepripojilo sa :(");
<------>return 4;
    }
    printf("Blutuz device konekted sukesfuli");
    return 0;
}
