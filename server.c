#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <netinet/in.h>



int main(int argc, char* argv[]){
    int sockfd, newsockfd;
    socklen_t cli_length;
    struct sockaddr_in serv_addr, cli_addr;

    bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(argv[1]));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
<------>perror("Err create");
<------>return 1;
    }
    int binding =  bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if (binding < 0){
<------>perror("Err binding");
<------>return 2;
 }
    listen(sockfd, 5);
    cli_length = sizeof(cli_addr);
    printf("Server connected sukesfuly\n");
    while(1){
    newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &cli_length);
    if(newsockfd < 0){
<------>printf("nie\n");
    }
    }
    close(sockfd);
    return 0;
}
