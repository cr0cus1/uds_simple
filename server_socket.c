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
    int server_fd;
    char msg[30];

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
        int tmp;
        while(1) {
            ret = accept(server_fd, (struct sockaddr *) &server_addr, &peer_addr_size);
            if(ret == -1)
                perror("accept failed");

            tmp = read(ret, msg, 20);
            if(tmp == -1)
                perror("msg failed");
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
