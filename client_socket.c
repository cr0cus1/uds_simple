#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/socket"
struct sockaddr_un client_addr;

int create_client_socket() {
    char msg[256];
    int client_fd, ret;

    if((client_fd = socket(AF_UNIX, SOCK_STREAM, 0)) != -1) {
        puts("Client socket created...");

    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sun_family = AF_UNIX;
    strcpy(client_addr.sun_path, SOCKET_PATH);

    strcpy(msg, "hello world from client!");

    ret = connect(client_fd, (struct sockaddr *) &client_addr, sizeof(struct sockaddr_un));
    if(ret == -1)
        perror("connection failed");
    else {
        puts("Connected!");
        if(write(client_fd, msg, strlen(msg)) == -1)
            perror("send failed");

        printf("%s \n", msg);
    }



    return 0;
    }
}

int main(int argc, char **argv) {
    int ret;
    ret = create_client_socket();
}
