# Competitive Programming

My C++ library for ICPC and Codeforces: algorithm templates organized by topic, a stress-testing kit for finding wrong answers fast, and solutions from contests, gyms and training sheets.

```
.
├── templates/        algorithm templates, one folder per topic
├── Stress Testing/   stress-test script + gen/brute library (KACTL-style)
├── solutions/        contests, gyms, sheets (+ root.sh to manage them)
└── git               one-command pull / commit / push helper
```

---

## Templates

| # | Topic | Highlights |
|---|---|---|
| 01 | [Notes](<templates/01- Notes>) | Contest `main.cpp` template, tips, testing notes |
| 02 | [Bitwise](<templates/02- Bitwise>) | Bit ops, masks, submask iteration, bitset, XOR basis |
| 03 | [Combinatorics](<templates/03- Combinatorics>) | nCr (with mod), derangements, Motzkin numbers, Legendre's formula, probability |
| 04 | [Data Structures](<templates/04- Data Structures>) | Coordinate compression, Trie, Persistent Trie, STL tricks |
| 05 | [DP](<templates/05- DP>) | Knapsack, LIS, LCS, digit DP, bitmask DP, SOS, Knuth, divide & conquer DP, DP on DAG |
| 06 | [Graph Theory](<templates/06- Graph Theory>) | BFS/DFS, DSU, shortest paths, MST, flow, bridges & articulation points, cycles, topological sort, segment-tree graph |
| 07 | [Number Theory](<templates/07- Number Theory>) | Primes, divisors, GCD, modular arithmetic, matrices, polynomials, bases, geometry |
| 08 | [Range Queries](<templates/08- Range Queries>) | Segment tree (recursive & iterative), BIT, sqrt decomposition, binary lifting, monotonic stack, 2D prefix sums |
| 09 | [Searching and Sorting](<templates/09- Searching and Sorting>) | Binary / ternary / parallel binary search, two pointers, inversions, counting sort |
| 10 | [String Processing](<templates/10- String Processing>) | KMP, Z-function, Manacher, hashing, Aho–Corasick, suffix automaton |
| 11 | [Trees](<templates/11- Trees>) | LCA, HLD (vertex & edge), rerooting DP, DSU on tree (sack), small-to-large merging |
| 12 | [General Ideas](<templates/12- general ideas>) | Dilworth, diagonal tricks, min cost |
| 13 | [Game Theory](<templates/13 - Game Theory>) | Strategy-stealing argument |
| 14 | [Miscellaneous](<templates/14- Miscellaneous>) | Interactive template, randomizer, mex, overflow checks, sliding window, I/O helpers |

---

## Stress Testing

Find the bug when you get WA: compare your solution against a slow brute force on thousands of small random tests.

```bash
cd "Stress Testing"
# write sol.cpp (your solution), brute.cpp (slow but correct), gen.cpp (random input), chk.cpp (checker)
./stress.sh sol brute gen chk
```

```
AC 1
AC 2
...
WA on test 7  (rerun this test: ./gen 7)
8 -2
-2 1 -1 -1 1 2 1 -1
```

- The test number is the generator's seed, so `./gen 7` always prints the same failing test.
- `chk.cpp` gets `in.txt out.txt ans.txt` and returns 0 if the answer is accepted. Use it when a problem allows several correct answers; otherwise just compare tokens.

### `lib/`: ready-made generators and brute forces

A KACTL-inspired library with one folder per topic. Each has a `gen.cpp` (random input generators) and a `brute.cpp` (slow, obviously-correct solutions). Copy the function you need instead of writing it under contest pressure. Every brute has been checked against KACTL or an independent method on thousands of random inputs.

| Folder | Examples |
|---|---|
| graph | random graph / DAG / bipartite · Floyd–Warshall, SCC, max flow by min cut, matching, 2-SAT |
| trees | uniform random tree (Prüfer), path / star / deep trees · naive LCA, diameter, centroids |
| geometry | random simple & convex polygons · convex hull, closest pair, point in polygon |
| strings | balanced brackets, Thue–Morse anti-hash · naive KMP / Z, suffix array, palindromes |
| number-theory | primes, edge values · factorization, discrete log, CRT, modular sqrt |
| numerical | polynomials, matrices, linear systems · naive convolution, determinant, recurrences |
| data-structures | range-query ops, anti-`unordered_map` keys · range sum/min/max, k-th in range |
| combinatorics | multisets, grids · Catalan, Stirling, Bell, partitions by enumeration (+ formulas) |
| bitwise | small-value arrays · pairwise XOR/AND/OR sums, SOS, XOR basis (+ formulas) |
| game-theory | piles, move sets · win/lose + Grundy, 8 classic games, **pattern finder** |
| various | knapsack, intervals, partitions · LIS, knapsack, TSP, edit distance by brute force |

See [`Stress Testing/lib/README.md`](<Stress Testing/lib/README.md>) for every function.

```bash
cd "Stress Testing/lib/trees"
g++ -O2 gen.cpp -o gen && g++ -O2 brute.cpp -o brute
./gen 5 | ./brute
```

---

## Solutions

| Folder | Contents |
|---|---|
| [`solutions/Contests`](solutions/Contests) | Codeforces rounds (Div. 1/2/3, Educational) |
| [`solutions/Gyms`](solutions/Gyms) | ICPC-style gym contests (ECPC, DAPC, Mexico, Ethiopia, …) |
| [`solutions/Sheets`](solutions/Sheets) | Topic training sheets: FFT, HLD, centroid, Aho–Corasick, DSU on tree, game theory, matrix exponentiation, … |

`solutions/root.sh` is an interactive manager. It creates a new contest / gym / sheet folder with one file per problem from the template, opens existing ones, and archives finished ones.

```bash
cd solutions && ./root.sh
```

---

## Git helper

```bash
./git                       # pull, add everything, commit "🔧 Update changes", push
./git "Add HLD template"    # same, with your own message
```
