#include <iostream>
#include <set>
using namespace std;

int main(){
    int num;
    set<int> s;
    int count = 0;
    while(cin >> num){
        auto it = s.find(num);
        if (it == s.end()){ //no volem números repetits
            s.insert(num);
            auto it2 = s.find(num);
            if (it2 != s.begin()) --it2;
            if (*it2%2 == 1 and num%2 == 1){
                s.erase(num);
            }
            else if (*it2%2 == 0 and num%2 == 0){
                s.erase(num);
            }
        }
    }
    cout << s.size() << endl;

}