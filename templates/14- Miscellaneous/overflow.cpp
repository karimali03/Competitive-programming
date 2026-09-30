/*
 * ============================================================================
 * INTEGER OVERFLOW HANDLING TRICKS FOR COMPETITIVE PROGRAMMING
 * ============================================================================
 * 
 * Context:
 * When calculating large values like `(x - 1) * c`, the result can exceed the 
 * maximum limit of a 64-bit signed integer (~9.22 * 10^18). When this happens, 
 * the value silently wraps around to a massive negative number, which completely 
 * breaks `min()` logic in Dynamic Programming.
 * 
 * Core Idea:
 * The optimal answer is mathematically guaranteed to fit inside a `long long`. 
 * Therefore, we don't need to store the exact massive value of the overflow; 
 * we just need to cap it at a safe "Infinity" (like 2e18). This ensures it fits 
 * in a `long long` without wrapping to negative, and guarantees it will correctly 
 * lose in any `min()` comparison against the actual optimal answer.
 */

#include <iostream>
#include <algorithm>

using namespace std;

// A safe infinity value that fits comfortably inside a 64-bit integer
// without wrapping around when added to or manipulated slightly.
const long long INF = 2e18; 

// ----------------------------------------------------------------------------
// METHOD 1: The Safe Division Check
// ----------------------------------------------------------------------------
// Use this if you are strictly writing standard C++ and want to avoid 
// compiler-specific extensions.
// ----------------------------------------------------------------------------
long long calculateDirectCostMethod1(long long x, long long c) {
    long long ret;
    
    // We want to evaluate if `(x - 1) * c > INF`.
    // If we literally multiply it, it might overflow before the comparison.
    // So, we use algebra to rearrange the inequality: `(x - 1) > INF / c`
    
    if ((x - 1) > INF / c) {
        ret = INF;         // It would overflow, so cap it at infinity
    } else {
        ret = (x - 1) * c; // It is safe to perform the multiplication
    }
    
    return ret;
}


// ----------------------------------------------------------------------------
// METHOD 2: GCC's 128-bit Integer (Quickest for CP)
// ----------------------------------------------------------------------------
// Competitive Programming platforms usually compile with GCC, which provides 
// `__int128` under the hood. It can store up to ~3.4 * 10^38.
// ----------------------------------------------------------------------------
long long calculateDirectCostMethod2(long long x, long long c) {
    
    // 1. We cast both sides to `unsigned __int128` to ensure the multiplication 
    //    happens in a 128-bit space (impossible to overflow here).
    // 2. We use `min()` to compare it against our 64-bit INF limit.
    // 3. Because it is capped at INF, it is guaranteed to fit perfectly 
    //    when stored back into the 64-bit `long long ret`.
    
    long long ret = min((unsigned __int128)INF, (unsigned __int128)(x - 1) * c);
    
    return ret;
}