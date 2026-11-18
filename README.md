# 🧠 eda-fib · Estructures de Dades i Algorismes

> **Pràctiques, laboratoris i resolució de problemes algorísmics de l'assignatura Estructures de Dades i Algorismes (EDA) del Grau en Enginyeria Informàtica a la Facultat d'Informàtica de Barcelona (UPC · FIB).**

[![Language](https://img.shields.io/badge/Language-C%2B%2B17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)](https://isocpp.org)
[![University](https://img.shields.io/badge/UPC-FIB-0070BA?style=for-the-badge)](https://www.fib.upc.edu)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](LICENSE)

> [!NOTE]
> **Estat del repositori & Migració en curs:**  
> El contingut complet d'aquesta assignatura es troba actualment en procés de migració des d'un altre disc dur. Aniré afegint a poc a poc més exercicis, laboratoris i apunts quan disposi de temps lliure.  
> 
> *Aquest repositori té una finalitat secundària com a demostració del meu coneixement base en fonaments d'enginyeria informàtica (el focus primordial del meu perfil professional i desenvolupament es troba en els meus projectes d'enginyeria de programari).*

---

## 📚 Continguts i Blocs Temàtics

1. **📦 STL (Standard Template Library):**
   - Ús eficient de contenidors de C++: std::map, std::set, std::vector, std::priority_queue.
   - Anàlisi asimptòtica de complexitat temporal i espacial ((1)$, (\log n)$, (n)$).

2. **⚔️ Divide & Conquer (D&C):**
   - Disseny d'algorismes divideix i venç (Cerca binària, ordenacions, exponenciació ràpida).
   - Teorema mestre per a relacions de recurrència.

3. **🕸️ Algorismes de Grafs (Graphs):**
   - Recorreguts en amplada (**BFS**) per a distàncies mínimes.
   - Recorreguts en profunditat (**DFS**) per a components connexes, cicles i ordenació topològica.
   - Algorisme de **Dijkstra** per a camins mínims ponderats.
   - Algorismes d'arbres d'expansió mínima (**Kruskal** i **Prim**).

---

## 🛠️ Compilació i Execució

`ash
g++ -O2 -std=c++17 -Wall nom_problema.cc -o nom_problema
./nom_problema < entrada.txt
`

---

## 📄 Llicència

Distribuït sota la llicència MIT.