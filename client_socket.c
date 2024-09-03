#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/socket"
struct sockaddr_un client_addr;

int create_client_socket() {
    char msg[256];
    char client_input[250];
    char server_buff[250];
    int client_fd, ret;

    if((client_fd = socket(AF_UNIX, SOCK_STREAM, 0)) != -1) {
        puts("Client socket created...");

        memset(&client_addr, 0, sizeof(client_addr));
        client_addr.sun_family = AF_UNIX;
        strcpy(client_addr.sun_path, SOCKET_PATH);


        ret = connect(client_fd, (struct sockaddr *) &client_addr, sizeof(struct sockaddr_un));
        if(ret == -1) {
            perror("connection failed");
            return 1;
        }
        puts("Connected!");

        printf("> ");
        memset(client_input, 0, sizeof(client_input));
        while(fgets(client_input, 250, stdin) != NULL) {
            if(write(client_fd, client_input, strlen(client_input)) == -1)
                perror("send failed");

            memset(server_buff, 0, sizeof(server_buff));
//            if(read(client_fd, server_buff, sizeof(server_buff)) < 0)
//                perror("read from server");
//            printf("res = %s \n", server_buff);
//            printf("\n");
//            printf("> ");
        }

    }
    return 0;
}

int main(int argc, char **argv) {
    int ret;
    ret = create_client_socket();
}
