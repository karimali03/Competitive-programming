# Qual-2
Created: Thu Jul 16 01:03:38 PM EEST 2026

## Problem Overview

- **A** - A
- **B** - C+
- **C** - B
- **D** - C-
- **E** - C
- **F** - D
- **G** - []
- **H** - C
- **I** - D+
- **J** - D
- **K** - []
- **L** - []
- **M** - []
- **N** - C
- **O** - Ace

## Problem Notes

### Problem G

There are two major flaws in the problem statement that contradict the sample output and break the physical simulation.

#### 1. The Sample Output Math Mismatch

The problem text explicitly states that when the ball exits the wall, **"Ebrahim gains 0 points."** However, the sample output proves this is mathematically incorrect.

If we manually calculate the expected value for the sample case (n=3, q=1, x=2), Ibrahim's expected score evaluates to **20/9**:

* **Hits `|` at 2:** Probability is **1/3**. Score is 4. Expected = **12/9**.
* **Hits `|` at 1:** Probability is **1/9** (requires `\` at 2, `|` at 1). Score is 2. Expected = **2/9**.
* **Hits `|` at 3:** Probability is **1/9** (requires `/` at 2, `|` at 3). Score is 6. Expected = **6/9**.

The sample output provided is **777777785**. If we decode this modulo 10^9+7, it evaluates to exactly **16/9**:

$$16 \times 9^{-1} \equiv 16 \times 111111112 \equiv 1777777792 \equiv 777777785 \pmod{10^9+7}$$

There is a gap of **4/9** between the logical expected value (20/9) and the sample output (16/9). The probability of the ball exiting the wall is exactly **2/9**. Therefore, to achieve the sample output, Ebrahim must be gaining exactly **2 points** when the ball exits, not 0.

#### 2. Missing Infinite Loop Clause

The problem states that the ball is processed recursively up or down based on the mirrors (`\` or `/`). However, it fails to account for infinite loops.

If block 2 is `\` and block 1 is `/`, the ball will endlessly bounce between them. Without an explicit rule to handle this, the simulation will never terminate, and the expected value becomes mathematically undefined. The current math implies these loops yield 0 points, but this must be explicitly stated to the solver.

### Problem J

There are some missing Testcases in the problem that make wrong solutions pass.
(e.g., [382865360](https://codeforces.com/gym/704215/submission/382865360), [382864091](https://codeforces.com/gym/704215/submission/382864091), [382863259](https://codeforces.com/gym/704215/submission/382863259))

**Missing Testcase 1**
```
8
0 3 4 2 2 2 2 2
```
**EXPECTED:** `2`

**Missing Testcase 2**
```
6
3 1 2 2 2 2
```
**EXPECTED:** `2`

**Missing Testcase 3**
```
6
0 2 1 1 1 1
```
**EXPECTED:** `2`