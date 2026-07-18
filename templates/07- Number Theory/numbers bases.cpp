// to convert x in base A to base b 
// covert from A to 10 then from 10 to B
string letters = "0123456789ABCDEF";
int toDecimal(string in , int base){
            int res = 0;
            for(int i = 0 ; i < in.size() ; i++){
                res *= base;
                res += letters.find(in[i]);
            }
            return res;
}
string fromDecimal(int num , int base){
         if(!num) return "0";
         string res;
         while(num){
                res =  letters[num % base] + res;
                num /= base;
         }
         return res;
}

/*
* Node 1: Standard Base Expansion
  - A number X in base b is represented by digits a_i, where 0 <= a_i < b.
  - Formula: X = a_0 + a_1*b + a_2*b^2 + a_3*b^3 + ...

* Node 2: Grouping by Chunk Size k
  - Group terms into blocks of length k and factor out powers of b^k.
  - X = [a_0 + a_1*b + ... + a_(k-1)*b^(k-1)] + 
        [a_k + a_(k+1)*b + ... + a_(2k-1)*b^(k-1)] * b^k + ...

* Node 3: The "Super Digit" Invariant
  - The maximum value for any bracketed chunk occurs when every digit is b-1.
  - The chunk's total value is strictly bounded in the range [0, b^k - 1].
  - Conclusion: Each bracket functions mathematically as a single, valid digit 
    in a new numeral system of base b^k.

* Node 4: The Collapsed Polynomial
  - Replace each chunk with a "Super Digit" variable (A_0, A_1, A_2 ...).
  - X = A_0 + A_1*(b^k)^1 + A_2*(b^k)^2 + A_3*(b^k)^3 + ...
  - To compute X mod n, evaluate this collapsed polynomial by substituting b^k 
    with the integer value of (b^k mod n).

*/
