# 🧠 eda-fib · Estructures de Dades i Algorismes

> **Pràctiques, laboratoris i resolució de problemes algorísmics de l'assignatura Estructures de Dades i Algorismes (EDA) del Grau en Enginyeria Informàtica a la Facultat d'Informàtica de Barcelona (UPC · FIB).**

[![Language](https://img.shields.io/badge/Language-C%2B%2B17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org)
[![University](https://img.shields.io/badge/UPC-FIB-0070BA?style=for-the-badge)](https://www.fib.upc.edu)
[![Platform](https://img.shields.io/badge/Judge-Jutge.org-FFA116?style=for-the-badge)](https://jutge.org)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](LICENSE)

---

## 📚 Continguts i Blocs Temàtics

Aquest repositori conté les implementacions i resolucions completes de més de **80 problemes de Jutge.org**, exàmens i jocs d'estratègia d'EDA:

1. **📦 Ús d'Estructures de Dades de la STL (`Jutge/Use of STL data structures/`):**
   - Ús eficient de contenidors de C++: `std::map`, `std::set`, `std::vector`, `std::priority_queue`, `std::stack`, `std::queue`.
   - Anàlisi asimptòtica de complexitat temporal i d'espai ($\mathcal{O}(1)$, $\mathcal{O}(\log n)$, $\mathcal{O}(n)$).

2. **⚔️ Divideix i Venç (`Jutge/Divide and conquer/`):**
   - Disseny d'algorismes divide and conquer (Cerca binària en vectors rotats/ordenats, potències de matrius, càlcul eficient de Fibonacci).
   - Relacions de recurrència i Teorema Màster.

3. **🔍 Cerca Exhaustiva i Generació (`Jutge/Exhaustive search and generation/`):**
   - Generació combinatòria (permutacions, combinacions, subconjunts).
   - Backtracking amb poda d'espais d'estats (problema de les $N$ reines, particions d'elements).

4. **🕸️ Algorismes de Grafs (`Jutge/Graph algorithms/`):**
   - Recorreguts en amplada (**BFS**) per a camins mínims en grafs no ponderats / graelles.
   - Recorreguts en profunditat (**DFS**) per a components connexes, detecció de cicles i ordenació topològica.
   - Algorisme de **Dijkstra** per a camins de cost mínim amb pesos no negatius.
   - Arbres d'expansió mínima (**MST**) amb **Kruskal** i **Prim**.

5. **🎮 Jocs d'Estratègia d'EDA (`Jutge/Games/`):**
   - Implementació de jugadors intel·ligents (bots) per a competicions multijugador d'EDA (BFS multiobjectiu, càlcul de distàncies, assignació greedy de rols i defensa/atac).
   - *The Walking Dead*, *Pandemic*, *Money Heist* i *Harry Potter*.

6. **📝 Exàmens Parcials i Finals (`Jutge/Exam problems/`):**
   - Col·lecció de 26 problemes d'exàmens oficials de cursos anteriors resolts i validats amb veredicte verd a Jutge.org.

---

## 📁 Estructura del Repositori

```text
eda-fib/
├── 1- STL/                                # Exercicis de laboratori i jocs de proves STL
├── 2- DIVIDE & CONQUER/                   # Exercicis de laboratori D&C
├── 3-GRAFS/                               # Exercicis de laboratori de Grafs
└── Jutge/                                 # 81 Resolucions oficials de Jutge.org
    ├── Divide and conquer/                # 14 problemes D&C
    ├── Exam problems/                     # 26 problemes d'exàmens (P22295, P27258, ...)
    ├── Exhaustive search and generation/  # 11 problemes de backtracking i generació
    ├── Games/                             # 4 IA de jocs de competició EDA
    ├── Graph algorithms/                  # 15 problemes de grafs (Dijkstra, BFS, DFS)
    └── Use of STL data structures/        # 11 problemes d'estructures STL
```

---

## 🛠️ Compilació i Execució

```bash
# Compilació amb flags estrictes de Jutge / C++17
g++ -O2 -std=c++17 -Wall -Wextra nom_problema.cc -o nom_problema

# Execució amb redirecció d'entrada
./nom_problema < entrada.txt
```

---

## 📄 Llicència

Distribuït sota la llicència MIT.
