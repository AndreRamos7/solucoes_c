#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 10;
    vector<bool> verify(n, false);

    for(int i = 0; i < verify.size(); i++){
        cout << verify.at(i) << endl;
    }
    return 0;
}