#include <sys/wait.h>
#include <unistd.h>
#include <string>
#include <sstream>
#include <numeric>
using namespace std;
int fd1[2];
int fd2[2];
void multiply(){
    char input_string[1000];
    read(fd1[0], input_string, 1000);

    float a, b, c;
    stringstream input_string_stream(input_string);
    input_string_stream >> a;
    input_string_stream.ignore();
    input_string_stream >> b;
    write(fd2[1], to_string(a*b).c_str(), 1000);
}

int main(){
    int l = 3;
    int m = 2;
    int n = 3;

    float matrix1[l][m] = {
        {1, 2},
        {3, 4},
        {5, 6}
    };
    float matrix2[m][n] = {
        {7, 8, 9},
        {10, 11, 12}
    };
    float res_matrix[l][n];

    pid_t parent_pid = getpid();
    pipe(fd1);
    pipe(fd2);
    bool status = true;
    for (int i = 0; i < l; i++){
        for (int j = 0; j < n; j++){
            float temp_array[m];
            for (int r = 0; r < m; r++){
                string temp_string = to_string(matrix1[i][r]) + " " + to_string(matrix2[r][j]);
                write(fd1[1], temp_string.c_str(), temp_string.size() + 1);
                if (fork() == 0){
                    multiply();
                    status = false;
                    break;
                }else{
                    char temp[1000];
                    wait(NULL);
                    read(fd2[0], temp, 1000);
                    temp_array[r] = stof(temp);
                }
            }
            if (!status){
                break;
            }else{
                res_matrix[i][j] = accumulate(temp_array, temp_array + m, 0.0);
            }
        }
        if (!status){
            break;
        }
    }
    
    if (getpid() == parent_pid){
        printf("Resulting matrix\n");
        for (int i = 0; i < l; i++){
            for (int j = 0; j < n; j++){
                printf("%f ", res_matrix[i][j]);
            }
            printf("\n");
        }
    }
    return 0;
}