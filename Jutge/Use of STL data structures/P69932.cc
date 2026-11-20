#include <iostream>
#include <set>
#include <sstream>
using namespace std;


int main(){
    string linia;
    while (getline(cin,linia)){
        set<int> s;
        istringstream ss(linia);
        int num;
        int count = 1; 
        while (ss >> num){
            s.insert(num);
        }
        int ant;
        if (s.empty()) cout << 0 << endl;
        else{
            for (auto it = s.begin(); it != s.end(); ++it){
                if (it == s.begin()) ant = *it;
                else if ((*it%2 == 0 and ant%2 != 0) or (*it%2 != 0 and ant%2 == 0)){
                    ++count;
                    ant = *it;
                }
            }
            cout << count << endl;
        }
    }
}
