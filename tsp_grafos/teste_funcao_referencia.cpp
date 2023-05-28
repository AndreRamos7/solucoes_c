#include <iostream>
using namespace std;

void dobrar(int&, int&);

int main(int args, char* argsv[]){

    int a = 2, b = 3;

    dobrar(a, b);
    cout << "results: " << a << ", " << b << endl; 

    return 0;
}

void dobrar(int& pa, int& pb){
    pa = pa * 2;
    pb = pb * 2;
}