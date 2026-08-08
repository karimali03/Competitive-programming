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

int countInversions(vi &v,int l,int r){
    if(l >= r) return 0;
    int mid = (l+r)/2;
    int res = countInversions(v,l,mid) + countInversions(v,mid+1,r);
    vi x(r-l+1);
    int i = l , j = mid+1 , k = 0;
    while(i <= mid && j <= r){
        if(v[i] <= v[j]){
            res+=(j-mid-1);
            x[k++] = v[i++];
        }
        else x[k++] = v[j++];
    }
    while(i <= mid){
        res+=(j-mid-1);
        x[k++] = v[i++];
    }
    while(j <= r){
        x[k++] = v[j++];
    }
    for(int i = l ; i <= r ; i++) v[i] = x[i-l];
    return res;
}


void solve(int test_case) {
    int n; cin>>n;
    string a,b; cin>>a>>b;
    if(count(all(a),'1') != count(all(b),'1')){
        NA; return;
    }   
    vi c1(2),c2(2);
    for(int i = 0;i < n ; i++){
        if(i&1){
            if(a[i] == '1') c1[0]++; 
            if(b[i] == '1') c2[0]++;
        }else{
            if(a[i] == '1') c1[1]++; 
            if(b[i] == '1') c2[1]++; 
        }
    }
    if(c1 != c2){
        NA; return;
    }
    vector<queue<int>>q1(2),q2(2);
    for(int i = 0;i < n ; i++){
        if(i&1){
            q2[b[i]-'0'].push(i);
        }else{
            q1[b[i]-'0'].push(i);
        }
    }
    vi id1,id2;
    for(int i = 0;i < n ; i++){
        if(i&1){
            id2.push_back(q2[a[i]-'0'].front());
            q2[a[i]-'0'].pop();
        }else{
            id1.push_back(q1[a[i]-'0'].front());
            q1[a[i]-'0'].pop(); 
        }
    }
    int res = countInversions(id1,0,(int)id1.size()-1) + countInversions(id2,0,(int)id2.size()-1);
    cout<<res<<ln;
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