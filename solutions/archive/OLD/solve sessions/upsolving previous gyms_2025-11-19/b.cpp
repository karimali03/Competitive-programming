    #include <bits/stdc++.h>
    using namespace std;
    #define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    #define int long long
    #define ll long long
    #define all(x) x.begin(),x.end()
    #define ln "\n"
    #define vi vector<ll>
    #define pl pair<ll, ll>
    #define vp vector<pl>

    vector<int> prefix_function(string &s){
        int n = s.size();
        vector<int>pi(n);
        int j = 0;
        for(int i = 1;i < n ; i++){
            while(j > 0 && s[i] != s[j]) j = pi[j-1]; 
            if(s[i] == s[j]) j++;
            pi[i] = j;
        }
        return pi;
    }



vector<int> suffixarray(string &s) {
    s += '$';
    int n = s.size();
    vector<int> suff(n), P(n);
    vector<pair<int, int>> V(n);
    for (int i = 0; i < n; i++) suff[i]=i, V[i] = {s[i], s[i]};
    
    auto comp = [&](int i, int j) {
        if (V[i].first != V[j].first) return V[i].first < V[j].first;
        return V[i].second < V[j].second;
    };
    sort(all(suff), comp);
    
    vector<int> tmp(n), frq(n), C(n);
    for (int k = 1; k < n; k*=2)
    {
        C[0] = frq[0] = P[suff[0]] = 0;
        for (int i = 1; i < n; i++) P[suff[i]] = P[suff[i-1]] + (V[suff[i]] != V[suff[i-1]]), frq[i] = 0;
        for (int i = 0; i < n; i++) V[i] = {P[i], P[(i+k)%n]}, suff[i] = (suff[i] - k + n) % n, frq[P[i]]++;
        for (int i = 1; i < n; i++) C[i] = C[i-1] + frq[i-1];
        for (int i = 0; i < n; i++) tmp[C[V[suff[i]].first]] = suff[i], C[V[suff[i]].first]++;
        swap(suff, tmp);
    }

    return suff;
}


int calc(string &s){
    auto suff = suffixarray(s);
    ll n = s.size();
    vi ind(n), lcp(n-1); 
    for (int i = 0; i < n; i++) ind[suff[i]] = i;
    
    int ls = 0;
    for (int i = 0; i < n-1; i++)
    {
        int prv = suff[ind[i]-1];
        while (s[i+ls]==s[prv+ls])ls++;
        lcp[ind[i]-1] = ls, ls = max(0ll, ls-1);
    }
    ll sol = ((n)*(n-1))/2;
    for (auto a : lcp) sol -= a;
    return sol;
}


    #define ull unsigned ll
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    ll rand_range(ll l, ll r) { return l + (ull) rng() % (r - l + 1); }
    string compute(int n){
        int len = rand_range(30,30*n);
        string ret(len,'X');
        for(int i = 0;i < len;i++) if(rand_range(0,1)) ret[i] = 'O';
        return ret;
    }

    
    void solve(){
        int n; cin>>n;
        vector<string>v(30);
        for(int i = 0; i < n ; i++){
            set<int>st;
            while(true){
                string cur = compute(n);
                v[i] = cur;
                set<int>tmp;
                bool vld = true;
                for(int x = 0;x < i && vld; x++){
                    string a = v[x] + v[i];
                    string b = v[i] + v[x];
                    string c = v[i] + v[i];
                    int c1 = calc(a); int c2 = calc(b); int c3 = calc(c);
                    if(tmp.count(c1) || tmp.count(c2) || c1 == c2 || st.count(c1) || st.count(c2)) vld = false; 
                    if(c1 == c3 || c2 == c3 || tmp.count(c3) || st.count(c3)) vld = false;
                    tmp.insert(c1); tmp.insert(c2); tmp.insert(c3);
                }
                if(!vld) continue;
                for(auto it : tmp) st.insert(it);
                break;
            }
        }
    
        
        for(int i = 0; i < n ;i++){
            cout<<v[i]<<endl;
        }
        // map<int,pair<int,int>>res;
        // int q; cin>>q;
        // for(int i = 0 ;i < n ; i++){
        //     for(int j = 0;j < n;j++){
        //         string cur = v[i] + v[j];
        //         int ans = calc(cur);
        //         res[ans] = {i+1,j+1};
        //     }
        // }
        // while(q--){ 
        //     int x; cin>>x;
        //     cout<<res[x].first<<" "<<res[x].second<<endl;
        // }
    }

    signed main(){
        fast
        int t=1;
        while(t--){
            solve();
        }
    }