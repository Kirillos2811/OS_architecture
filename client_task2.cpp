#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
using namespace std;

#define PORT 9877

int main(int argc, char* argv[]){
    if (argc == 1){
        cout << "Pass socket name as a parameter" << endl;
        return -1;
    }
    char socket_name[100];
    strcpy(socket_name, argv[1]);

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in sock_addr;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = INADDR_ANY;
    sock_addr.sin_port = htons(PORT);

    connect(sock, (sockaddr *) &sock_addr, sizeof(sock_addr));

    send(sock, socket_name, strlen(socket_name) + 1, 0);
    return 0;
}