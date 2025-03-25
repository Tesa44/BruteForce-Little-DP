# Brute Force
# Little's Algorithm
# Dynamic Programming
# Solving ATSP 
eng below

## Wstęp
Asymetryczny problem komiwojażera (ATSP, z ang. Asymmetric Traveling 
Salesman Problem) stanowi jedno z kluczowych wyzwań optymalizacyjnych 
w teorii grafów oraz badań operacyjnych. Zadanie to polega na wyznaczeniu 
najkrótszej możliwej trasy, która pozwala komiwojażerowi odwiedzić 
wszystkie zadane miasta dokładnie raz i powrócić do punktu początkowego, 
przy czym odległości między miastami mogą się różnić w zależności od 
kierunku przejścia (asymetria). ATSP znajduje szerokie zastosowanie w 
logistyce, planowaniu tras oraz optymalizacji produkcji, a także w systemach 
komunikacji miejskiej i transporcie. Ze względu na swoją złożoność obliczeniową (problem należy do klasy NPtrudnych), rozwiązywanie ATSP wymaga zastosowania specjalistycznych 
algorytmów, takich jak algorytmy przeglądu zupełnego, podziału i ograniczeń 
lub programowania dynamicznego. Celem niniejszego badania jest ocena 
efektywności wybranych algorytmów stosowanych do rozwiązywania ATSP, 
poprzez analizę ich wyników w kontekście jakości uzyskanych rozwiązań oraz 
czasu obliczeń. Wyniki badania mają na celu dostarczenie informacji na temat 
praktycznej przydatności poszczególnych metod oraz wskazanie, które 
algorytmy mogą być szczególnie skuteczne w różnych przypadkach ATSP

## Brute Force
Algorytm Brute Force dla asymetrycznego problemu komiwojażera (ATSP) 
polega na wygenerowaniu wszystkich możliwych permutacji tras 
odwiedzających każde miasto dokładnie raz, a następnie powracających do 
punktu początkowego. Dla każdej permutacji obliczana jest całkowita długość 
trasy, a algorytm wybiera tę, która jest najkrótsza. Brute Force gwarantuje 
znalezienie rozwiązania optymalnego.

## Little's Algorithm
Algorytm Little’a jest metodą dokładnego rozwiązywania asymetrycznego 
problemu komiwojażera (ATSP) opartą na technice przeszukiwania z 
ograniczeniami (branch and bound). Algorytm rozpoczyna od skonstruowania 
macierzy kosztów podróży między miastami, po czym wykonuje redukcję 
wierszy i kolumn, aby zmniejszyć wartości kosztów i uzyskać oszacowanie 
dolne dla minimalnego kosztu trasy. Następnie dzieli problem na podproblemy
(podział drzewa przeszukiwań) i dla każdego z nich oblicza nowe oszacowania 
dolne, eliminując te gałęzie, które nie mogą prowadzić do rozwiązania 
optymalnego (odcięcie).

## Dynamic Programming
Dla algorytmu rozwiązującego problem komiwojażera metodą programowania 
dynamicznego, zwykle stosuje się algorytm oparty na podejściu BellmanaHelda-Karpa.
Algorytm Bellmana-Helda-Karpa oparty na programowaniu dynamicznym 
rozwiązuje problem komiwojażera, przechowując optymalne wyniki 
częściowych tras, aby uniknąć wielokrotnego obliczania kosztów dla tych 
samych podproblemów. W algorytmie tym dla każdego zbioru odwiedzonych 
miast oraz bieżącego miasta jako końcowego, zapisuje się minimalny koszt 
dotarcia do tej konfiguracji. Proces ten powtarza się rekurencyjnie dla 
wszystkich możliwych podzbiorów miast, a na końcu zwraca najkrótszą 
możliwą trasę.

### Uruchomienie programu
1. Sklonuj repozytorium:
    ```sh
   git clone https://github.com/Tesa44/PEA-projekt-1.git
2. Otwórz projekt w CLion
3. Skonfiguruj kompilator
4. Zbuduj projekt
5. Uruchom program

## Dokumentacja
Pełny przebieg badania znajduje się w pliku `PEA-projekt-1.pdf`

## Introduction
The Asymmetric Traveling Salesman Problem (ATSP) is one of the key optimization challenges in graph theory and operations research. The task involves determining the shortest possible route that allows a salesman to visit all given cities exactly once and return to the starting point, with distances between cities varying depending on the direction of travel (asymmetry). ATSP has wide applications in logistics, route planning, production optimization, as well as urban transportation and communication systems.
Due to its computational complexity (the problem belongs to the NP-hard class), solving ATSP requires specialized algorithms, such as exhaustive search, branch and bound, or dynamic programming. The objective of this study is to evaluate the efficiency of selected algorithms used to solve ATSP by analyzing their results in terms of solution quality and computation time. The findings aim to provide insights into the practical applicability of different methods and to identify which algorithms may be particularly effective in various instances of ATSP.

## Brute Force
The Brute Force algorithm for the Asymmetric Traveling Salesman Problem (ATSP) involves generating all possible permutations of routes that visit each city exactly once before returning to the starting point. For each permutation, the total route length is calculated, and the algorithm selects the shortest one. Brute Force guarantees finding the optimal solution.

## Little’s Algorithm
Little’s Algorithm is an exact method for solving the Asymmetric Traveling Salesman Problem (ATSP) based on the branch and bound technique. The algorithm begins by constructing a cost matrix of travel distances between cities and then performs row and column reduction to decrease cost values and obtain a lower bound estimate for the minimal route cost. Next, the problem is divided into subproblems (search tree branching), and for each subproblem, new lower bound estimates are calculated, eliminating branches that cannot lead to an optimal solution (pruning).

## Dynamic Programming
For solving the Traveling Salesman Problem using dynamic programming, the Bellman-Held-Karp algorithm is commonly applied.
The Bellman-Held-Karp algorithm, based on dynamic programming, solves the Traveling Salesman Problem by storing optimal results of partial routes to avoid redundant cost calculations for the same subproblems. In this algorithm, for each set of visited cities and the current city as the endpoint, the minimal cost to reach that configuration is recorded. This process is repeated recursively for all possible city subsets, ultimately returning the shortest possible route.

### Startup
1. Clone the repo
   ```sh
   git clone https://github.com/Tesa44/PEA-projekt-1.git
2. Open project in CLion
3. Configure compiler
4. Build the project
5. Run main.cpp

## Documentation
The full research process is documented in the file `PEA-projekt-1.pdf`
