#include <iostream>
#include <vector>
using namespace std;


typedef vector<string> VS;
typedef vector<VS> VSS;


/*El programa no genera una llista gegant amb totes les solucions i després les imprimeix. El que fa és:

Construeix UNA solució completa.
La imprimeix a l'instant (li fa una "foto").
Desfà l'últim pas (esborra una mica) per construir la següent.
Com funciona la variable sol?
La variable sol és com una pissarra única. Només en tens una.
Passeges la pissarra (sol) per les funcions recursives.
Cada funció hi escriu una paraula.
Quan la pissarra està plena (i == n), fas la "foto" (escriu).
Immediatament després, esborres l'última paraula (pop_back) per deixar lloc a una altra opció.*/

void escriu(const VSS& sol, int n, int nparam){
    // sol.size() ja val nparam perquè l'hem creat així al main
    for (int i = 0; i < nparam; ++i){
        cout << "subconjunt " << i + 1 << ':' << " {";
        for (int j = 0; j < sol[i].size(); ++j){
            cout << sol[i][j];
            if (j != sol[i].size() - 1) cout << ',';
        }
        cout << '}' << endl;
    }
    cout << endl;
}

void particions(VS& p, int nparam, int n, int i, VSS& sol){
    if (i == n){
        escriu(sol,n,nparam);
        return;
    }
    for (int k = 0; k < nparam; ++k){
            sol[k].push_back(p[i]);
            particions(p,nparam,n,i+1,sol);
            sol[k].pop_back();
    }

}

/*T'ho explico pas a pas:
La funció rep la paraula número i (per exemple, "hola").
Entra al bucle for per decidir a quin subconjunt la posa.
Imagina que decideix posar-la al subconjunt 0.
Fa push_back de "hola" al subconjunt 0.
Immediatament crida a la recursivitat passant i + 1.
Això vol dir: "Oblida't de la paraula 'hola', ara ens toca decidir sobre la paraula 'adeu'".
Per què no es repeteix? Com que hem saltat a i + 1 (el següent nivell de profunditat), 
la funció mai té l'oportunitat de tornar a agafar la paraula i ("hola") i posar-la al 
subconjunt 1 en la mateixa branca.
La paraula "hola" queda "gastada" en aquest pas. Només quan fem el backtracking (tornem 
enrere, fem el pop_back i el bucle avança) la traiem del subconjunt 0 i la posem al subconjunt 
1. Però mai estarà als dos llocs alhora.*/


int main(){
    int n, nparam;
    cin >> n;
    VS p(n);
    for (int i = 0; i < n; ++i){
        cin >> p[i];
    }
    cin >> nparam;

    VSS sol(nparam);
    particions(p,nparam,n,0,sol);
}

/*Exemple pas a pas (Traça)
Imagina: Paraules = {hola, adeu}, Subconjunts = 2. sol comença buit: [ [], [] ]

Torn paraula "hola": La poso al subconjunt 0.
sol: [ [hola], [] ]

Torn paraula "adeu": La poso al subconjunt 0.
sol: [ [hola, adeu], [] ]

BASE (i=2): Ja hem acabat!
-> IMPRIMEIXO el que hi ha a la pissarra ara: subconjunt 1: {hola, adeu}...

Torno enrere...
Backtracking: Esborro "adeu" del subconjunt 0.
sol: [ [hola], [] ]

Torn paraula "adeu" (2n intent): La poso al subconjunt 1.
sol: [ [hola], [adeu] ]
BASE (i=2): Ja hem acabat!

-> IMPRIMEIXO la pissarra tal com està ara: subconjunt 1: {hola}...*/