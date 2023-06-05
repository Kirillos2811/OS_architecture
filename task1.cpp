#include <unistd.h>
#include <sstream>
using namespace std;

int main(){
    if (fork()){
        sleep(120);
    }
    else{
        exit(0);
    }
    return 0;
}