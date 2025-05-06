/*
  Function to implement the Extended Euclidean Algorithm
  It computes gcd(a, b) and finds integers x and y such that:
  a * x + b * y = gcd(a, b)
  The general solution can be written as:
  x = x₀ + (b / gcd(a, b)) * t
  y = y₀ - (a / gcd(a, b)) * t
  where t is any integer, and (x₀, y₀) is the particular solution.
*/
int EEA(int a, int b, int& x, int& y) {
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}


