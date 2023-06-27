#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
using namespace std;

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
    connect(sfd, (sockaddr *) &sock_addr, sizeof(sock_addr));

    send(sfd, socket_name, strlen(socket_name), 0);
    return 0;
}