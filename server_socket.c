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

    if((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) != -1) {
        puts("Server socket was created...");
        unlink(SOCKET_PATH);
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

        while(1) {
            memset(client_buffer, 0, sizeof(client_buffer));
            msg = read(client_fd, client_buffer, 255);
            if(msg == -1)
                perror("msg failed");
            
            printf("client: %s \n", client_buffer);

            printf("root > ");
            fgets(server_buffer, sizeof(server_buffer)+1, stdin);

            if(write(server_fd, server_buffer, strlen(server_buffer)) == -1)
                perror("send failed");
            printf("\n");
        }
        close(server_fd);
    }
    else
        perror("socket creating");

    return 0;
    
}

int main(int argc, char **argv) {
    int ret;
    ret = create_server_socket();
}
