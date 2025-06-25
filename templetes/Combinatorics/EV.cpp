/*
==========================================
      EXPECTED VALUE & CONTRIBUTION 
      Competitive Programming Reference
==========================================

------------------------------------------
BASICS OF EXPECTED VALUE (EV)
------------------------------------------

// EV definition:
E[X] = sum over all outcomes (P_i * X_i)

// Linearity of Expectation (Always holds):
E[X + Y] = E[X] + E[Y]
E[sum of N variables] = sum of their expectations

// Even if X and Y are dependent!

------------------------------------------
CONTRIBUTION TECHNIQUE (INDICATOR TRICK)
------------------------------------------

// For counting events:
// Define indicator variable I_i = 1 if event i happens, 0 otherwise
// Then: E[Total count] = sum of E[I_i] = sum of P(event i happens)

// Main strategy:
// 1. Fix one element/event.
// 2. Calculate its probability to contribute.
// 3. Multiply by its contribution amount.
// 4. Sum over all elements/events.

------------------------------------------
COMMON PROBLEM PATTERNS
------------------------------------------

// 1. Selecting items (subset problems):
  - Each element contributes independently.
  - Often involves powers of 2 for subsets.

// 2. Max/Min over subsets:
  - Sort the array.
  - For each element:
      E[max] += a_i * 2^(i-1)
      E[min] += a_i * 2^(N-i)

// 3. Trees:
  - For edge between subtree sizes s and (N-s):
      Contribution = s * (N - s)

// 4. Geometric problems (convex hull, perimeter):
  - For each edge:
    P(edge exists) = (1/4) * [ (1/2)^L + (1/2)^R ]
    (L and R: points on each side of the edge)

// 5. Recursion in sequential problems (coin flips, waiting times):
  - Set up recursive formula for EV.

------------------------------------------
USEFUL LAWS AND TRICKS
------------------------------------------

// Negative binomial expectation (for k successes):
  E = k / p

// For 'first success' problems (geometric distribution):
  E = 1 / p

// Birthday paradox EV (N people, D days):
  E = D * (1 - (D-1)/D)^N

// Eating Ends problem (exact):
  P(a_i survives) = 1 / C(N-1, i-1)
  EV = sum (a_i * 1/C(N-1, i-1))

------------------------------------------
SOLVING STRATEGY FOR EV PROBLEMS
------------------------------------------

// 1. Try Linearity of Expectation first.
// 2. Apply contribution technique (fix element).
// 3. Use indicator variables where possible.
// 4. Decompose into independent parts.
// 5. Sort when dealing with Max/Min.
// 6. Use recursion for sequential/random processes.
// 7. Pay attention to combinatorics in survival probabilities.
// 8. Powers of 2 often appear in subset problems.
// 9. In trees, edge contributions dominate.
// 10. Think: "When does this item contribute?"

==========================================
END OF EV REFERENCE
==========================================
*/

