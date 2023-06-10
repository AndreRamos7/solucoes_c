#include <algorithm>
#include <iostream>
#include <string>
using namespace std;
 
int main()
{
    string s = "cab";
    sort(s.begin(), s.end());
    bool prox = false;
    for(int i = 0; i < 6; i++){ 
        cout << s << ". prox: " << prox << '\n';
        prox = next_permutation(s.begin(), s.end());
    }
}