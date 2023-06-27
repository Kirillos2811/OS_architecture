#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
using namespace std;

#define BUFF 1000

int main(int argc, char* argv[]){
    if (argc == 1){
        cout << "Pass socket name as a parameter" << endl;
        return -1;
    }
    char socket_name[100];
    strcpy(socket_name, argv[1]);

    int sfd = socket(AF_UNIX, SOCK_DGRAM, 0);
    sockaddr_un sock_addr;
    sock_addr.sun_family = AF_UNIX;

    strcpy(sock_addr.sun_path, socket_name);
    bind(sfd, (sockaddr *) &sock_addr, sizeof(sock_addr));

    char msg[BUFF];
    size_t last_char_index = recv(sfd, msg, BUFF - 1, 0);
    if (last_char_index != -1){
        cout << "SOCKET NAME: " << msg << endl;
    }
    return 0;
}