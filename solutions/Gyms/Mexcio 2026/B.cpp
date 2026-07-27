#include <bits/stdc++.h>
using namespace std;
#define ln "\n";
#define ll long long
#define vi vector<ll>
#define vii vector<vi>
#define all(X) X.begin(), X.end()

const int INF = 1e9;

struct Trie {
    struct node {
        int nxt[26];
        bool leaf;
        int cnt;
        node() {
            leaf = false;
            cnt = 0;
            memset(nxt,-1,sizeof(nxt));
        }
    };
    vector<node> child;

    Trie() {
        child.push_back(node());
    }

    void insert(string &s) {
        int cur = 0;
        int sz = s.size();
        child[0].cnt++;
        for(int i = 0;i < sz ; i++){
            int idx = s[i] - 'a';
            if(child[cur].nxt[idx] == -1){
                child[cur].nxt[idx] = child.size();
                child.push_back(node());                
            }
            cur = child[cur].nxt[idx];
            child[cur].cnt++;   
        }
        child[cur].leaf = true;
    }
 

    vi calc(int x){
        vi dp(1);
        for(int ch = 0;ch<26;ch++) if(child[x].nxt[ch] != -1){
            vi dp_ch = calc(child[x].nxt[ch]);
            int sz1 = dp.size();
            int sz2 = dp_ch.size();
            int new_sz = sz1+sz2-1;
            vi new_dp(new_sz,INF);
            for(int i = 0 ;i < sz1 ; i++){
                if(dp[i] == INF) continue;
                for(int j =0;j < sz2 ; j++){
                    new_dp[i+j] = min(new_dp[i+j] , dp[i] + dp_ch[j]);
                }
            }
            dp = move(new_dp);
        }
        dp.resize(child[x].cnt+1);
        dp[child[x].cnt] = 1;
        return dp;
    }
};



void solve(){
    int n,k; cin>>n>>k;
    Trie st;
    for(int i = 0;i < n ; i++){
        string s; cin>>s;
        st.insert(s);
    }
    if(k == 1){
        cout<<1<<ln;
        return;
    }
    auto dp = st.calc(0);
    cout << dp[k] << '\n';
}



int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1;
    
    while(t--) solve();
}