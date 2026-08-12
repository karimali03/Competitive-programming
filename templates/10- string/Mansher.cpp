/*

  d1[i] -> odd center i
  range = [i-d1[i]+1, i+d1[i]-1]

  d2[i] -> even center between i-1,i
  range = [i-d2[i], i+d2[i]-1]

  odd length  = 2*d1[i]-1
  even length = 2*d2[i]

  sum(d1)+sum(d2) = # palindromic substrings
  
*/
struct Manacher {
    int n;
    string s;
    vector<int> d1, d2;

    Manacher(string _s) : s(_s) {
        n = s.size();
        d1.resize(n);
        d2.resize(n);
        build();
    }

    void build() {
        // odd: [i-d1[i]+1 ... i+d1[i]-1]
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r ? 1 : min(d1[l+r-i], r-i+1));

            while (i-k >= 0 && i+k < n && s[i-k] == s[i+k])
                k++;

            d1[i] = k--;

            if (i+k > r) {
                l = i-k;
                r = i+k;
            }
        }

        // even: [i-d2[i] ... i+d2[i]-1]
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r ? 0 : min(d2[l+r-i+1], r-i+1));

            while (i-k-1 >= 0 && i+k < n && s[i-k-1] == s[i+k])
                k++;

            d2[i] = k--;

            if (i+k > r) {
                l = i-k-1;
                r = i+k;
            }
        }
    }

    // 0-indexed inclusive [l, r]
    bool is_pal(int l, int r) {
        int len = r-l+1;

        if (len & 1) {
            int mid = (l+r)/2;
            return d1[mid] >= len/2 + 1;
        } else {
            int mid = (l+r+1)/2;
            return d2[mid] >= len/2;
        }
    }
};
