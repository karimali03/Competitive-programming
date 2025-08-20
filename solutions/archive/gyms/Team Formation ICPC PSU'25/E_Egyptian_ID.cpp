#include <iostream>
#include <bits/stdc++.h>
 
using namespace std;
#define ln "\n"
#define ll long long
#define ld long double
#define vec vector
#define vi vector<int>
#define vii vector<vector<int>>
#define f(i, a, b) for(int i=a;i<b;i++)
#define fr(n) for(int i=0;i<n;i++)
#define all(x)   x.begin(),x.end()
#define rall(x)   x.rbegin(),x.rend()
#define pi acos(-1)
#define cout_2d(vec, n, m) for(int i = 0; i < n; i++, cout << "\n") for(int j = 0; j < m && cout << vec[i][j] << " "; j++);
#define int long long
 
 
 
 
bool isValidDate(int year, int century, int day, int month) {
    // Validate input ranges
    if (year < 0 || year > 99 || (century != 2 && century != 3) || 
        month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }
 
    // Form full year (e.g., 23 and 2 -> 1923, 23 and 3 -> 2023)
    int fullYear = (century == 2 ? 1900 : 2000) + year;
 
    // Check valid days per month
    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
 
    // Adjust February for leap year
    bool isLeap = (fullYear % 4 == 0 && fullYear % 100 != 0) || (fullYear % 400 == 0);
    if (isLeap && month == 2) {
        daysInMonth[1] = 29;
    }
 
    // Check if day is valid for the given month
    if (day > daysInMonth[month - 1]) {
        return false;
    }
 
    return true;
}
 
void solve(int test_case){
    string s; cin>>s;
    int c = stoi(s.substr(0,1));
    if( c != 2 && c != 3) return void(cout<<"NO"<<ln);
    int g = stoi(s.substr(7,3));
    if(g < 1 || g  > 99) return void(cout<<"NO"<<ln);
    int y = stoi(s.substr(1,2));
    int m = stoi(s.substr(3,2));
    int d = stoi(s.substr(5,2));
    if(!isValidDate(y,c,d,m)) return void(cout<<"NO"<<ln);
    cout<<"YES"<<ln;
}
 
signed main() {
    ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    int t = 1;
    cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}
