#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

int create_server_socket() {
    int server_socket;
    int client_socket;
    struct sockaddr_un server_addr;

    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if(server_socket == -1)
        perror("socket creating");

    server_addr.sun_family = AF_UNIX;
    strcpy(server_addr.sun_path, "unix_socket");
    int socket_length = sizeof(server_addr);

    

    return 0;
    
}

int create_client_socket() {

}



int main(int argc, char **argv) {
    int ret = create_server_socket();

    printf("%d \n", ret);
}
