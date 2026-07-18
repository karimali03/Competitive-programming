#include <bits/stdc++.h>
using namespace std;

struct ManacherSplit {
    string s;
    int n;
    vector<int> d1; // Odd length palindromes
    vector<int> d2; // Even length palindromes

    ManacherSplit(const string& str) : s(str), n(str.size()) {
        d1.resize(n);
        d2.resize(n);
        
        // 1. Compute d1 (Odd-length palindromes centered at i)
        // d1[i] = k means palindrome s[i-k+1 ... i+k-1] exists.
        // Length = 2*k - 1.
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r) ? 1 : min(d1[l + r - i], r - i + 1);
            while (0 <= i - k && i + k < n && s[i - k] == s[i + k]) {
                k++;
            }
            d1[i] = k--;
            if (i + k > r) {
                l = i - k;
                r = i + k;
            }
        }

        // 2. Compute d2 (Even-length palindromes centered between i-1 and i)
        // d2[i] = k means palindrome s[i-k ... i+k-1] exists.
        // Length = 2*k.
        for (int i = 0, l = 0, r = -1; i < n; i++) {
            int k = (i > r) ? 0 : min(d2[l + r - i + 1], r - i + 1);
            while (0 <= i - k - 1 && i + k < n && s[i - k - 1] == s[i + k]) {
                k++;
            }
            d2[i] = k--;
            if (i + k > r) {
                l = i - k - 1;
                r = i + k;
            }
        }
    }

    // --- UTILITIES ---

    /**
     * Checks if s[l...r] is a palindrome in O(1).
     */
    bool isPalindrome(int l, int r) {
        int len = r - l + 1;
        if (len % 2 == 1) {
            // Odd length: Center is exactly at (l+r)/2
            int mid = (l + r) / 2;
            int radius = (len + 1) / 2;
            return d1[mid] >= radius;
        } else {
            // Even length: Center is "split" between mid-1 and mid
            // For range [0, 3] (len 4), center is boundary at index 2 (between 1 and 2)
            int mid = (l + r + 1) / 2; 
            int radius = len / 2;
            return d2[mid] >= radius;
        }
    }

    /**
     * Returns the longest palindrome substring.
     */
    string getLongestPalindrome() {
        int maxLen = 0;
        int start = 0;

        // Check odds
        for (int i = 0; i < n; i++) {
            int len = 2 * d1[i] - 1;
            if (len > maxLen) {
                maxLen = len;
                start = i - d1[i] + 1;
            }
        }

        // Check evens
        for (int i = 0; i < n; i++) {
            int len = 2 * d2[i];
            if (len > maxLen) {
                maxLen = len;
                start = i - d2[i];
            }
        }

        return s.substr(start, maxLen);
    }
    
    // Returns max length found
    int getMaxLen() {
        int mx = 0;
        for(int x : d1) mx = max(mx, 2*x - 1);
        for(int x : d2) mx = max(mx, 2*x);
        return mx;
    }
};
