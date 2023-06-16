#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
 
void mostrar_permutacao(vector<int>);

int main()
{
    vector<int> s;
    for(int c = 0; c < 6; c++)
        s.push_back(c);

    sort(s.begin(), s.end());
    bool prox = false;
    for(int i = 0; i < (6*5*4*3*2); i++){ 
        mostrar_permutacao(s);
        //cout << s.at(i) << ". prox: " << prox << '\n';
        prox = next_permutation(s.begin(), s.end());
    }
}

void mostrar_permutacao(vector<int> perm){
    for(int i = 0; i < perm.size(); i++)
        cout << perm.at(i) << "-";
    cout << endl;

}