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
 
 // Variadic print function for debugging
 template<typename... Args>
 void print(Args... args) {
     ((cout << args << " "), ...);
     cout << endl;
 }
 
 template<typename T = int>
 istream &operator>>(istream &in, vector<T> &v) {
     for (auto &x: v) in >> x;
     return in;
 }
 
 // Overload for vector
 template<typename T = int>
 ostream &operator<<(ostream &out, const vector<T> &v) {
     for (const T &x : v) out << x << ' ';
     return out;
 }
 
 void solve(int test_case){
    string s; cin>>s;
    int n = s.size();
    int x; cin>>x;
    vi pos;
    for(int i = 0 ; i < n ; i++){
        if(s[i] == '0') pos.push_back(i);
        else{
            int st = i;
            while(i+1 < n && s[i] <= s[i+1]) i++;
            pos.push_back(st);
        }
    }
    if(pos.size() > x) cout<<-1<<ln;
    else{
        int rem = x - (int)pos.size();
        pos.push_back(n);
        for(int it = 0 ; it < (int)pos.size()-1 ; it++){
            if(s[it] == '0') cout<<0<<" ";
            else{
                int i = pos[it];
                rem++;
                while( rem > 0 && i < pos[it+1]){
                    if(rem == 1){
                        for(int j = i ; j < pos[it+1] ; j++) cout<<s[j];
                        cout<<" ";
                    }
                    else cout<<s[i++]<<" ";
                    rem--;
                }
            }
        }
        cout<<ln;
    }
       
 }
 
 signed main() {
     ios_base::sync_with_stdio(false);cin.tie(nullptr); cout.tie(nullptr);
    // freopen("collector.in", "r", stdin);  // Redirects standard input to read from "input.txt"
     int t = 1;
     cin >> t;
     for (int i = 1; i <= t; i++) {
         solve(i);
     }
     return 0;
 }