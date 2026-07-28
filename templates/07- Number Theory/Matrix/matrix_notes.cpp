/*
================================================================================
                MATRIX EXPONENTIATION - TRANSITION MATRIX CHEAT SHEET
================================================================================

GOLDEN RULE: The transition matrix (T) can ONLY contain constants. 
             Any variables (like n) must be tracked and updated entirely 
             inside the state vector.
             
             Equation format: Target Vector = Transition Matrix * Current Vector

1. CLASSIC LINEAR COMBINATIONS
   Equation: f(n) = 1*f(n-1) + 2*f(n-2) + 3*f(n-3)
   
   [ f(n)   ]   [ 1  2  3 ]   [ f(n-1) ]
   [ f(n-1) ] = [ 1  0  0 ] * [ f(n-2) ]
   [ f(n-2) ]   [ 0  1  0 ]   [ f(n-3) ]


2. HANDLING CONSTANTS
   Equation: f(n) = 2*f(n-1) + 3*f(n-2) + 5
   Trick: Add a dummy '1' to the bottom of the state vector to carry the constant.
   
   [ f(n)   ]   [ 2  3  5 ]   [ f(n-1) ]
   [ f(n-1) ] = [ 1  0  0 ] * [ f(n-2) ]
   [   1    ]   [ 0  0  1 ]   [   1    ]


3. HANDLING VARIABLES (e.g., + n or + n^2)
   Equation: f(n) = f(n-1) + n^2
   Trick: Expand the target step (n+1)^2 = n^2 + 2n + 1. 
          Your state vector must carry all polynomial terms needed (n^2, n, 1).
          
   [ f(n)    ]   [ 1  1  0  0 ]   [ f(n-1) ]
   [ (n+1)^2 ] = [ 0  1  2  1 ] * [ n^2    ]
   [ n+1     ]   [ 0  0  1  1 ]   [ n      ]
   [ 1       ]   [ 0  0  0  1 ]   [ 1      ]


4. RUNNING SUMS
   Equation: S(n) = S(n-1) + f(n), assuming f(n) = f(n-1) + f(n-2)
   Trick: Substitute f(n) in the sum formula so it only uses previous states:
          S(n) = S(n-1) + f(n-1) + f(n-2)
          
   [ S(n)   ]   [ 1  1  1 ]   [ S(n-1) ]
   [ f(n)   ] = [ 0  1  1 ] * [ f(n-1) ]
   [ f(n-1) ]   [ 0  1  0 ]   [ f(n-2) ]


5. HANDLING PRODUCTS
   Equation: f(n) = f(n-1) * f(n-2) * f(n-3)
   Trick: Matrix multiplication only works for addition. You must shift to 
          calculating the EXPONENTS of the base cases instead.
          
   - Let base cases be A=f(1), B=f(2), C=f(3). Future terms are A^a * B^b * C^c
   - The exponents (a, b, c) follow a standard addition relation: 
     P(n) = P(n-1) + P(n-2) + P(n-3)
   - Use a standard linear matrix (like section 1) to find the final exponents.
   
   CRITICAL MODULO TRICK (Fermat's Little Theorem): 
   Because you are calculating powers, all matrix math to find the exponents 
   MUST be done modulo (MOD - 1), assuming MOD is prime. 
   
   Final answer: (power(A, a, MOD) * power(B, b, MOD) * power(C, c, MOD)) % MOD

================================================================================
*/
/*
 * =========================================================================
 * EXPONENT MODULO TRICK (Fermat's Little Theorem)
 * =========================================================================
 * When calculating A^B % MOD (where MOD is a prime number like 1e9+7):
 * 
 * 1. The BASE (A) is calculated modulo MOD.
 * 2. The EXPONENT (B) MUST be calculated modulo (MOD - 1).
 * 
 * Theorem: A^(MOD-1) ≡ 1 (mod MOD)
 * Therefore: A^B ≡ A^(B % (MOD - 1)) (mod MOD)
 * 
 * Application in this problem:
 * - MOD = 1e9+7 
 * - PHI = 1e9+6 (which is MOD - 1)
 * 
 * Since the transition matrix calculates the *growth of the exponents* 
 * rather than the actual values, ALL matrix operations (addition and 
 * multiplication) MUST be done using % PHI. 
 * 
 * Only the final binary exponentiation (base^exp) uses % MOD.
 * =========================================================================
 */