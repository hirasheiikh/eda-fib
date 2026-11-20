#include <iostream>
#include <map>
using namespace std;


int main(){
    int n;
    while (cin >> n){
        map<string,int> jocs;
        int total = n;
        for (int i = 0; i < n; ++i){
            string s;
            cin >> s;
            ++jocs[s];
        }

        int nous;
        cin >> nous;
        for (int i = 0; i < nous; ++i){
            string jnou;
            cin >> jnou;
            int quantitat = jocs[jnou];
            if (quantitat + 1 <= total - quantitat){
                ++jocs[jnou];
                ++total;
            }
        }
        for (auto it = jocs.begin(); it != jocs.end(); ++it){
            cout << it->first << ' ' << it->second << endl;
        }
        cout << string(20,'-') << endl;

    }
}