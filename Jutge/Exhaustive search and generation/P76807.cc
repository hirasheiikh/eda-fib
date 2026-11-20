#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> Fila;
typedef vector<Fila> Sudoku;
typedef vector<Sudoku> Sub_Sudoku;


Sudoku sudoku(9,Fila(9));
Sudoku fila;
Sudoku columna;
Sub_Sudoku tercio_sudoku;


void escriure(){
    for (int i = 0; i < 9; ++i){
        for (int j = 0; j < 9; ++j){
            cout << sudoku[i][j];
            if (j != 8) cout << ' ';
        }
        cout << endl;
    }
}

bool fer_sudoku(int i, int j){
    if (i == 9){
        escriure();
        return true;
    }
    else if (j == 9) return fer_sudoku(i+1,0);
    else if (sudoku[i][j] != 0) return fer_sudoku(i, j+1); 
    else{
        for (int d = 1; d <= 9; ++d){
            if (not fila[i][d] and not columna[j][d] and not tercio_sudoku[i/3][j/3][d]){
                fila[i][d] = columna[j][d] = tercio_sudoku[i/3][j/3][d] = true;
                sudoku[i][j] = d;
                if (fer_sudoku(i,j+1)) return true;
                sudoku[i][j] = 0;
                fila[i][d] = columna[j][d] = tercio_sudoku[i/3][j/3][d] = false;
            }
        }
        return false;
    }

}


int main(){
    int n;
    cin >> n;
    cout << n << endl;
    //creem el sudoku
    for (int u = 0; u < n; ++u){
        cout << endl;
        fila = Sudoku(9, Fila(10, false));
        columna = Sudoku(9, Fila(10, false)); // Atenció: columna[num][row] -> num va fins a 9
        tercio_sudoku = Sub_Sudoku(3, Sudoku(3, Fila(10, false)));
        for (int i = 0; i < 9; ++i){
            for (int j = 0; j < 9; ++j){
                char c;
                cin >> c;
                if (c == '.') sudoku[i][j] = 0;
                else{
                    int num = c -'0';
                    sudoku[i][j] = num;
                    fila[i][num] = columna[j][num] = tercio_sudoku[i/3][j/3][num] = true; //això seria com la nostra matriu de visitats pero hem de marcar tant les files
                        //com les columnes, com els terços ja que així és com es juga al sudoku.
                }   
            }
        }
        fer_sudoku(0,0);
    }
}