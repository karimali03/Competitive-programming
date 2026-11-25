# Stress lib (KACTL-style)

Each folder: `gen.cpp` (random input generators) + `brute.cpp` (slow, obviously-correct answers).
Copy the function you need into your problem's `gen.cpp` / `brute.cpp` (in `Stress Testing/`), then run from there:
`./stress.sh sol brute gen chk` (file names without `.cpp`). The test number `i` is passed as the seed: `./gen i`. `chk.cpp` gets `in.txt out.txt ans.txt` and returns 0 if the answer is accepted.
Every `gen.cpp` starts with the same basics: `rnd(lo,hi)`, `randBool`, `randDouble`, `shuf`, `randVec`, `randPerm`, `randStr`.
`./gen` alone gives a random test; `./gen SEED` gives the same test every time (to rerun a failure). Each folder works out of the box: `./gen 5 | ./brute`.
Keep n SMALL. Small values and small alphabets find bugs fastest.

| Folder | gen | brute |
|---|---|---|
| graph | randGraph, connectedGraph, randDirected, randDAG, randBipartite, randFunctional, completeGraph, rand2SAT, printGraph | floyd, bellmanFord, countComps, bridges, artPoints, reach, sccMinNode, isDAG, isTopoOrder, isBipartite, mstWeight, maxMatching, maxIndSet, maxClique, minVertexCover, maxFlow (min cut), sat2, hasEuler, shortestPaths (count) |
| trees | randTree (Prufer), randParentTree, pathTree, starTree, caterpillar, binaryTree, relabel, printTree, parentToEdges, pathQueries, subtreeQueries, nodeValues | parentDepth, naiveLCA, pathVertices, kthAncestor, pathSumMax, distAll, diameter, sumDist, subtreeSizes, subtreeNodes, centroids, subtreeSum, pathSum |
| geometry | randPoint(s), randCollinear, randSegment, randTriangle, randSimplePolygon, randConvexPolygon, randCircle | area2, onSeg, segInter, inPoly, isSimple, hullBrute, closest2, farthest2, mecBrute, latticeCount, countInTri |
| strings | periodicStr, fibStr, runsStr, randPalindrome, randSubstr, randRotation, randPatterns, allStrings, randBrackets (balanced), randBracketsAny, thueMorse, antiHash64 (breaks mod 2^64 hashing) | occurrences, prefixFunc, zFunc, suffixArray, lcpArray, minRotation, isRotation, smallestPeriod, longestPal, countPals, isPal, distinctSubstrings, longestCommonSubstring, longestRepeated, countPatterns, isBalanced, countBalancedSubstrings |
| number-theory | randPrime, randComposite, randSmooth, randPower, randSquare, edgeVal, randPrimeMod, coprimePair, randCRT | gcdB, lcmB, checkEuclid, isPrimeB, factorB, primesUpToB, isqrtB, divisorsB, phiB, mobiusB, modpowB, modInvB, orderB, primRootB, dlogB, sqrtModB, crtB, binomB, modsumB, divsumB |
| numerical | randPoly, randVL, randMat, randSingular, randSystem, randRec, randSubset, randMod | polyMulB, polyEvalB / polyEvalD, checkInterpB, dftB, matMulB, matPowB, detPermB, rankModB, checkSolveB / checkSolveD, linRecB, checkRecB, subsetConvB, integralB |
| data-structures | randArr, edgeArr, randRange, pointOps, rangeOps, randGrid, randRect, randLines, randIntervals, setOps, antiUnorderedMap (TLE test: makes unordered_map O(n) per op on GCC) | pointSet/Add, rangeAdd, rangeAssign, rangeSum/Min/Max/Gcd/Xor, countDistinct, kthInRange, countLess, rectSum, maxLineAt, fenwickLowerBound, ms* (multiset), unionLength, segments (IntervalContainer), nextGreater, windowMin |
| game-theory | randPiles, randMoveSet, randDAG, randGameArray, randTreeParents | win / grundy (edit `moves()`), winV (vector state, edit `movesV()`), mex, dagWin, dagGrundy, endsDiff, nimFormula, takeUpToK. **Classic games (brute + formula):** wythoff, stair (Staircase Nim), moore (Nim_k), kaylesGrundy/kaylesFormula, grundysGame, euclid, chompBrute, hackenbush (tree). **Pattern finder:** `./brute 40` prints W/L, losing states and grundy for 0..40 |
| combinatorics | randNK, randMultiset, randGrid, randPrime, printGrid | by enumeration: binomB, multisetPermB, permFixedB, derangeB, stirling1B, stirling2B, bellB, setPartB, inversionsB, catalanB, partitionsB, compositionsB, latticeB, surjB, necklaceB. **Formulas** (`...F`): binom mod p, Catalan, derangements, Stirling, Bell, partitions, stars and bars, inclusion-exclusion, Burnside |
| bitwise | randBitArr, randRange, printArr | sumPairB / sumSubB (XOR/AND/OR over pairs/subarrays), countXorB, maxXorPairB, maxAndPairB, zeroPairsB, subsetXorsB, sosB, popRangeB, countBitsB, xorToB, popSumB, isGrayB, nextSamePopB. **Formulas** (`...F`): per-bit sums, prefix XOR + map, XOR basis (basisInsert, basisMax, basisRank), SOS DP, XOR 1..n, Gosper's hack |
| various | randSeq, randItems, randCoins, randJobs, randDistMat, randObsGrid, randPartition (k parts > 0), randPartition0 (k parts >= 0), randDistinct, randSorted | lisBrute, knapsack01, subsetSum, maxSubsetXor, coinMin, coinWays, lcsRec, editRec, tspBrute, maxWeightIntervals, gridPaths, maxSubarray, inversions |

Each function has a one-line comment above it with what it does, its complexity, and the largest safe n.
