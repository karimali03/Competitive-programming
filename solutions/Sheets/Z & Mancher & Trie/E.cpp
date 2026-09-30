#include <bits/stdc++.h>
using namespace std;

#define ln "\n"
#define ll long long
#define ld long double
#define ull unsigned long long
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define viii vector<vector<vector<int>>>
#define f(i, a, b) for(int i = a; i < b; i++)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define co(x) __builtin_popcountll(x)
#define ctz(x) __builtin_ctzll(x)
#define clz(x) __builtin_clzll(x)
#define PI acos(-1)
#define int long long
#define YES cout<<"YES\n"
#define NO cout<<"NO\n"
#define NA cout<<"-1\n"

template<typename T = int>
istream &operator>>(istream &in, vector<T> &v) {
    for (auto &x : v) in >> x;
    return in;
}

template<typename T = int>
ostream &operator<<(ostream &out, const vector<T> &v) {
    for (const T &x : v) out << x << ' ';
    return out;
}
struct Manacher {
    vector<int> p;

    // Builds the Manacher array in O(N) time
    Manacher(const string& s) {
        // Transform string: "abc" -> "^#a#b#c#$"
        // The '^' and '$' act as sentinels to prevent out-of-bounds errors.
        string t = "^#";
        for (char c : s) {
            t += c;
            t += '#';
        }
        t += '$';

        int n = t.length();
        p.assign(n, 0);
        int C = 0, R = 0; // Center and Right edge of the furthest reaching palindrome

        for (int i = 1; i < n - 1; i++) {
            int mirror = 2 * C - i; // Mirror index of i around center C

            // If i is within the right edge of the current center, 
            // initialize p[i] using the mirror property
            if (i < R) {
                p[i] = min(R - i, p[mirror]);
            }

            // Attempt to expand the palindrome centered at i
            while (t[i + 1 + p[i]] == t[i - 1 - p[i]]) {
                p[i]++;
            }

            // If the palindrome centered at i expands past R, adjust C and R
            if (i + p[i] > R) {
                C = i;
                R = i + p[i];
            }
        }
    }

    // Returns the maximum length of a palindrome in the string
    int getLongestPalindromeLength() {
        int maxLen = 0;
        for (int len : p) {
            maxLen = max(maxLen, len);
        }
        return maxLen;
    }

    // Returns the actual longest palindromic substring
    string getLongestPalindrome(const string& s) {
        if (s.empty()) return "";
        int maxLen = 0;
        int centerIndex = 0;
        
        for (int i = 1; i < (int)p.size() - 1; i++) {
            if (p[i] > maxLen) {
                maxLen = p[i];
                centerIndex = i;
            }
        }
        
        // Map back to the original string's index
        int start = (centerIndex - maxLen - 1) / 2;
        return s.substr(start, maxLen);
    }
    
    // Checks if the substring of the ORIGINAL string s[l...r] (inclusive) is a palindrome
    bool isPalindrome(int l, int r) {
        // Map original bounds to transformed string bounds
        // Original index i maps to transformed index 2*i + 2
        int center = l + r + 2; 
        int len = r - l + 1;
        return p[center] >= len;
    }
};
void solve(int test_case) {
    string s; cin>>s;
    int n = s.size();
    int l = 0 , r = n-1;
    while(l<=r && s[l] == s[r]) l++,r--;
    if(l<=r){
        auto man = Manacher(s);
        int mx1 = 0, mx2 = 0;
        for(int x = r ; x >= l ; x--){
            if(man.isPalindrome(l,x)){
                mx1 = x-l+1;
                break;
            }
        }
        for(int x = l ; x <= r ; x++){
            if(man.isPalindrome(x,r)){
                mx2 = r-x+1;
                break;
            }
        }
        if(l) cout<<s.substr(0,l);
        if(mx1 && mx1 >= mx2) cout<<s.substr(l,mx1);
        else if(mx2) cout<<s.substr(r-mx2+1,mx2);
        if(r+1 < n) cout<<s.substr(r+1,l);
        cout<<ln;
    }else{
        cout<<s<<ln;
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}