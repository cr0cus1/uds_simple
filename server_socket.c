#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <errno.h>
#include <stdlib.h>

#define SOCKET_PATH "/tmp/socket"
struct sockaddr_un server_addr;

int create_server_socket() {
    int ret;
    int msg;
    int server_fd;
    int client_fd;
    char client_buffer[255];
    char server_buffer[255];
    unlink(SOCKET_PATH);

    if((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) != -1) {
        puts("Server socket was created...");
        //socket's address details
        memset(&server_addr, 0, sizeof(server_addr));
        server_addr.sun_family = AF_UNIX;
        strcpy(server_addr.sun_path, SOCKET_PATH);

        ret = bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr));
        if(ret != 0)
            perror("bind failed");
        puts("Binded to the address...");

        ret = listen(server_fd, 5);
        if(ret == -1)
            perror("listen failed");

        puts("Listening...");
        socklen_t peer_addr_size;
        peer_addr_size = sizeof(server_addr);

        client_fd = accept(server_fd, (struct sockaddr *) &server_addr, &peer_addr_size);
        if(client_fd == -1) {
            perror("accept failed");
            return 1;
        }
        puts("Connected to the client!");

        memset(server_buffer, 0, sizeof(server_buffer));
        while(read(client_fd, server_buffer, sizeof(server_buffer)) > 0) {
            int first_digit = server_buffer[0] - '0';
            int second_digit = server_buffer[2] - '0';

            int res;

            if(server_buffer[1] == '-') 
                res = first_digit-second_digit;
            else if(server_buffer[1] == '+') 
                res = first_digit+second_digit;
                

            printf("%d \n", res);
//            sprintf(client_buffer, "%d", res);
//
//            if(write(client_fd, client_buffer, sizeof(client_buffer)) < 0)
//                perror("write");
//
        }

    }
    else
        perror("socket creating");

    close(server_fd);
    return 0;
    
}

int main(int argc, char **argv) {
    int ret;
    ret = create_server_socket();
}
