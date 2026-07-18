double calc(double x){
    return 2.0*x; // your calculations here
}
double ternary_search(double l, double r) {      
    while (r - l > 1e-6) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        double f1 = calc(m1);    
        double f2 = calc(m2);      
        if (f1 < f2)  // f1 > f2 for min
            l = m1;
        else
            r = m2;
    }
    return calc(l);   //return the maximum of f(x) in [l, r]
}


// ternary search on integers
int calc(int x){
    return 2*x; // your calculations here
}
int ternary_search(int l, int r) {
    while (r - l > 2) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;

        if (calc(m1) < calc(m2))  // > for min
            l = m1;
        else
            r = m2;
    }
    
    int best_x = l;
    for (int x = l; x <= r; x++) {
        if (calc(x) > calc(best_x)) best_x = x;
    }
    
    return best_x;  // Return the integer x that maximize f(x)
}
