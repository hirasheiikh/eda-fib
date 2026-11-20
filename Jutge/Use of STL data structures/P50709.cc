#include <iostream>
#include <queue>
using namespace std;

int main(){
    priority_queue<int> Q;
    char c;

    while (cin >> c){
        if (c == 'A'){
            if (Q.empty()){
                cout << "error!" << endl;
            }
            else{
                cout << Q.top() << endl;
            }
        }
        else if (c == 'S'){
            int x;
            cin >> x;
            Q.push(x);
        }
        else if (c == 'I'){
            int x;
            cin >> x;
            if (Q.empty()){
                cout << "error!" << endl;
            }
            else{
                int t = Q.top();
                Q.pop();
                t += x;
                Q.push(t);
            }
        }
        else if (c == 'D'){
            int x;
            cin >> x;
            if (Q.empty()){
                cout << "error!" << endl;
            }
            else{
                int t = Q.top();
                Q.pop();
                t -= x;
                Q.push(t);
            }
        }
        else if (c == 'R'){
            if (Q.empty()){
                cout << "error!" << endl;
            }
            else{
                Q.pop(); //elimina l'element més gran de la cua
            }
        }
    }

}