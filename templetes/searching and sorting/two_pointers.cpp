#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int longestSubarrayLessThanX(const std::vector<int>& v, int x) {
    int l = 0, r = 0, sum = 0, maxLength = 0;

    for(int r = 0 ; r < v.size() ; r++){
        sum += v[r];

        while (sum >= x && l <= r) {
            sum -= v[l];
            ++l;
        }
    
        maxLength = max(maxLength, r - l + 1);
        
    }
    
    return maxLength;
}
