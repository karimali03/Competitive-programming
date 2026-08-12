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

int p10(string &s){
    int n = s.size();
    if(s[0] != '1') return -1;
    int c = 0;
    for(int i = 1 ;i < n ; i++) c += (s[i] == '0');
    if(c == n-1) return c;
    return -1;
}

int num(string &s){
    int n = s.size();
    int c = 0;
    for(int i = n-1 ; i >= 0 ; i--){
        if(s[i] != '0') break;
        c++;
    }
    return c;
}
string chk(string &s){
    string ret;
    int x = p10(s);
    if(x != -1){
        if(x < 4) return s;
        ret = "10^{" + to_string(x) + "}";
        return ret;
    }
    x = num(s);
    if(x < 4) return s;
    ret.push_back(s[0]);
    if(x+1 < (int)s.size())
    ret += '.';

    for(int i = 1 ;i < (int)s.size() - x ; i++) ret += s[i];
    ret = ret + "\\cdot10^{" + to_string((int)s.size()-1) + "}";
    return ret;
}
vector<string> read(){
    vector<string> ret;
    string line;
    getline(cin, line);
    stringstream ss(line);
    string token; 
    while(ss >> token){
      //  cout<<token<<endl;
        bool vld = true;
        for(auto &it : token){
            if(it < '0' || it > '9'){
                vld = false;
            }
        }
    //    cout<<vld<<endl;
        if(vld){
            ret.push_back(chk(token));
        }else ret.push_back(token);
    //    cout<<"--"<<endl;
    }
    return ret;
}
void solve(int test_case) {
    int n; cin>>n;
    string line;
    getline(cin,line);  
    vector<vector<string>>ret(n);
    for(int i = 0;i < n ; i++){
        ret[i] = read();
    }
    for(int i = 0; i <  n; i++){
        if(i) cout<<ln;
        for(int j = 0;j < (int)ret[i].size() ; j++){
            if(j) cout<<" ";
            cout<<ret[i][j];
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int t = 1;
   // cin >> t;
    for (int i = 1; i <= t; i++) {
        solve(i);
    }

    return 0;
}