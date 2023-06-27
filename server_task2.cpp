#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
using namespace std;

#define BUFF 1000
#define PORT 9877

int main(){
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in sock_addr;
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = INADDR_ANY;
    sock_addr.sin_port = htons(PORT); 

    bind(sock, (sockaddr *) &sock_addr, sizeof(sock_addr));
    listen(sock, 1);
    int new_sock = accept(sock, NULL, NULL);

    char msg[BUFF];
    size_t last_char_index = recv(new_sock, msg, BUFF, 0);
    if (last_char_index != -1){
        cout << "SOCKET NAME: " << msg << endl;
    }
    return 0;
}