#include <iostream>
#include <cmath>

int main() {
    
    freopen("distance1.in", "r", stdin);
    freopen("distance1.out", "w", stdout);
    
    // Read the five integers: x, y, A, B, C
    long long x, y, A, B, C;
    std::cin >> x >> y >> A >> B >> C;

    // Calculate the numerator: |Ax + By + C|
    long double numerator = std::abs(A * x + B * y + C);

    // Calculate the denominator: sqrt(A^2 + B^2)
    long double denominator = std::sqrt(A * A + B * B);

    // Calculate the distance
    long double distance = numerator / denominator;

    // Print the result with sufficient precision
    std::cout.precision(10);
    std::cout << distance << std::endl;

    return 0;
}