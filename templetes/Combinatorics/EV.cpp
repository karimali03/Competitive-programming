# === Core Probability ===
P(A) = (Favorable Outcomes) / (Total Outcomes)
P(A or B) = P(A) + P(B) - P(A and B)
P(A and B) = P(A) * P(B|A)
P(A and B) = P(A) * P(B)         (If A and B are independent)
P(not A) = 1 - P(A)              (Complementary Probability - often easier to calculate)
P(A|B) = P(A and B) / P(B)       (Conditional Probability)
Bayes' Theorem: P(A|B) = P(B|A) * P(A) / P(B)

# === Core Expected Value (EV) ===
E(X) = Sum[ value(i) * P(X = value(i)) ]  (Definition)
**E(X + Y) = E(X) + E(Y)** (Linearity of Expectation - THE MOST IMPORTANT TRICK. X and Y can be dependent.)
E(c * X) = c * E(X)              (Scaling)
E(X) = Sum[ E(I_i) ]             (Using Indicator Variables)
Indicator Variable I_A: E(I_A) = 1 * P(A) + 0 * P(not A) = P(A)

# === Common Tricks & Scenarios ===
Contribution Technique: Total E(X) = Sum(E(X_i)) = Sum(P(event i) * value(event i))
Expected # of trials for one success (prob p) = 1/p (Geometric Distribution)
Expected # of successes in N trials (prob p) = N * p (Binomial Mean)
Waiting Time: E(time to get N items) = Sum[ E(time from i-1 to i items) ]
E(max(X, Y)) != max(E(X), E(Y))
E(X*Y) = E(X) * E(Y)             (Only if X and Y are independent)

# === DP with Probability ===
State: dp[i] = Probability of reaching state i
Transition: dp[i] = Sum( dp[j] * P(transition from j to i) )
Base Case: dp[start_state] = 1

# === DP with Expected Value ===
State: dp[i] = Expected cost/value *starting from* state i *to the end*
Transition: dp[i] = Sum( P(i -> j) * (cost(i -> j) + dp[j]) )
Example (cost is 1 per step): dp[i] = 1 + Sum( P(i -> j) * dp[j] )
Base Case: dp[end_state] = 0 (No cost to go from the end to the end)

# === DP with Cycles in EV ===
If a state can transition to itself: E_i = P_i * E_i + (1 - P_i) * (Other_Costs)
Solve for E_i: E_i * (1 - P_i) = Other_Costs  =>  E_i = Other_Costs / (1 - P_i)
For systems of equations: E_i = Sum(P_ij * E_j) + C_i. Use Gaussian elimination or iterative substitution.
