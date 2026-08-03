/**
 * ============================================================================
 * MANHATTAN DISTANCE TRICK (45-Degree Rotation / Chebyshev Transformation)
 * ============================================================================
 * 
 * THE PROBLEM:
 * Evaluating Manhattan distance D = |x1 - x2| + |y1 - y2| across many pairs 
 * is difficult because the X and Y components depend on each other when 
 * maximizing or minimizing.
 * 
 * THE TRICK:
 * Transform every point (x, y) into a new coordinate system (u, v):
 *      u = x + y
 *      v = x - y
 * 
 * In this new system, the Manhattan distance between any two original points 
 * perfectly equals the maximum absolute difference of their new coordinates 
 * (Chebyshev distance):
 *      D = max(|u1 - u2|, |v1 - v2|)
 * 
 * WHY IT WORKS (The Proof):
 * For any real numbers a and b: |a| + |b| = max(|a + b|, |a - b|)
 * If you substitute a = x1 - x2 and b = y1 - y2, expanding the right side 
 * naturally yields |u1 - u2| and |v1 - v2|.
 * 
 * CLASSIC USE-CASE: Maximum Manhattan Distance among N points in O(N).
 * Instead of checking all pairs in O(N^2), you track the minimum and maximum 
 * values of both u and v across all points. The answer is simply the maximum 
 * spread in either the u or v dimension.
 */

// O(N) solution to find the maximum Manhattan distance between any two points
long long maxManhattanDistance(const vector<pair<long long, long long>>& points) {
    long long min_u = 2e18, max_u = -2e18;
    long long min_v = 2e18, max_v = -2e18;

    for (const auto& p : points) {
        long long u = p.first + p.second;
        long long v = p.first - p.second;

        min_u = min(min_u, u);
        max_u = max(max_u, u);
        min_v = min(min_v, v);
        max_v = max(max_v, v);
    }

    // The maximum Manhattan distance is the largest spread in either axis
    return max(max_u - min_u, max_v - min_v);
}
