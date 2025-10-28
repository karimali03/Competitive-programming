- Permutation of r objects from n distinct objects
P(n,r) = !n / (n-r)! 
- Permutation of n objects not distinct
res = !n / (!n1 * !n2 .... !nk)
n = n1 + n2 + ... + nk
- Combinatorics of n distinct object
C(n,r) = !n / (!r * !(n-r))
- nCr laws
1 - C(n+1,r) = C(n,r) + C(n,r-1)
2 - Newtons Binomial Theorem
(x+y)^n = C(n,0) x^n + C(n,1) x^(n-1) y^1 + C(n,2) x^(n-2) y^2 + ... + C(n,r) x^(n-r) y^r + .. + C(n,n) y^n
3 - Symmetry rule :  C(n,k) = C(n,n-k)
4 - Factoring in :  C(n,k) = (n/k) C(n-1,k-1)
5 - Sum over k : sum[k=0 -> n ]C(n,k) = 2^n
6 - sum over n : sum[m=0 -> n ]C(m,k) = C(n+1,k+1)
7 - sum over n and k : sum[k=0 -> m]C(n+k,k) = C(n+m+1,m)
8 - sum of squares : C(n,0)^2 + C(n,1)^2 .... + C(n,n)^2 = C(2*n,n)
9 - weighted sum : C(n,1) + 2*C(n,2) + 3*C(n,3) ... + nC(n,n) = n*2^n-1
10 -Fib : C(n,0) + C(n-1,1) + ... + C(n-k,k) + .... + C(0,n) = F(n+1)
11 = um [j = 1 -> n ] { j * C(n-j,r) } = C(n+1,r+2)
- Stars and Bars 
1 - n balls k boxes (non empty) = C(n-1,k-1)
2 - n balls k boxes (empty allowed) = C(n+k-1,k-1)
- Multinomial Theorem
(c1*x1 + c2*x2 + c3*x3 + .... + cm*xm)^n = !n/(!k1!k2!k3!km) * x1^k1 x2^k2 xm^km
where sum k = n
- compositions of the integer k (i.e., ways to write k as a sum of positive integers, where order matters) = 2^k-1
- How many ways can you arrange $k$ distinct objects into $n$ distinct bins, where the order inside each bin matters and bins can be empty?
 = !(K+N-1)/!(N-1)