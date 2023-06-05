#include <iostream>
#include <vector>
using namespace std;

int main(){
    int n = 100;
    vector<int> verify;

    cout << "Antes de preencher" << endl;
    cout << "Verify size() = " << verify.size() << endl;
    for(int i = 0; i < verify.size(); ++i){
        cout << verify.at(i) << endl;
    }

    cout << "preenchendo" << endl;
    for(int i = 0; i < n; i++){
        verify.push_back(i*2);
    }
    cout << "Verify size() = " << verify.size() << endl;
    for(int i = 0; i < verify.size(); ++i){
        cout << verify.at(i) << endl;
    }
    return 0;
}