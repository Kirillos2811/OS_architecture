#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

int main(){
    ifstream ifile("coordinates.txt", ios::in);
    string str;
    while (getline(ifile, str)){
        stringstream ss(str);
        float latitude, longtitude;
        ss.ignore();
        ss >> latitude;
        ss.ignore();
        ss.ignore();
        ss >> longtitude;
        if ((latitude >= 50 and latitude <= 80) and (longtitude >= 20 and longtitude <= 45)){
            cout << str << endl;
        }
    }
    return 0;
}