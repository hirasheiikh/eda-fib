#include <iostream>
#include <queue>
using namespace std;

int main(){
    char command;
    priority_queue<int> pq;

    while (cin >> command){
        if (command == 'S'){
            int x;
            cin >> x;
            pq.push(x);
        }
        else if (command == 'A'){
            if (not pq.empty()) cout << pq.top() << endl;
            else cout << "error!" << endl;
        }
        else if (command == 'R'){
            if (not pq.empty()) pq.pop();
            else cout << "error!" << endl;
        }
        else if (command == 'I'){
            if (not pq.empty()){
                int x;
                cin >> x;
                int num_gran = pq.top();
                pq.pop();
                num_gran += x;
                pq.push(num_gran);
            }
            else cout << "error!" << endl;
        }
        else if (command == 'D'){
            if (not pq.empty()){
                int x;
                cin >> x;
                int num_gran = pq.top();
                pq.pop();
                num_gran -= x;
                pq.push(num_gran);
            }
            else cout << "error!" << endl;
        }
    }
}