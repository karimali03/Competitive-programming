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



struct BinaryLifting {
    int n;
    int LOG;
    int dummy;
    vector<vector<int>> jmp;

    // next_node[i] should contain the destination of 1 step from node i.
    // dummy_node is the "out of bounds" index (e.g., n + 1 for jumping right, 0 for left).
    BinaryLifting(int n, const vector<int>& next_node, int dummy_node) {
        this->n = n;
        this->dummy = dummy_node;
        
        // Calculate the maximum power of 2 needed for n elements
        LOG = 0;
        while ((1 << LOG) <= n) {
            LOG++;
        }
        // Alternatively, use a fixed size like LOG = 20 for n <= 10^6

        // Initialize table: jmp[node][k]
        // Default everything to the dummy node to avoid out-of-bounds errors
        jmp.assign(n + 2, vector<int>(LOG, dummy));

        // STEP 1: Base Case (2^0 = 1 jump)
        for (int i = 1; i <= n; i++) {
            jmp[i][0] = next_node[i];
        }

        // STEP 2: Build the Table
        // OUTER LOOP MUST BE 'k' (the power of 2)
        for (int k = 1; k < LOG; k++) {
            // INNER LOOP is the starting node 'i'
            for (int i = 1; i <= n+1 ; i++) { 
                int halfway = jmp[i][k - 1];
                jmp[i][k] = jmp[halfway][k - 1];
            }
        }
    }

    // STEP 3: The Query (Jump as far as possible without passing the target)
    // Returns the total number of jumps required to reach or stay behind the target.
    int count_jumps_to_target(int start, int target) {
        int curr = start;
        int jumps = 0;

        // Iterate k BACKWARDS from largest to smallest
        for (int k = LOG - 1; k >= 0; k--) {
            // Condition to check if this jump is valid.
            // Example: jumping right, we want to stay <= target
            if (jmp[curr][k] <= target) { 
                curr = jmp[curr][k]; // Make the jump
                jumps += (1 << k);   // Add 2^k steps to our counter
            }
        }
        
        return jumps;
    }

    // Alternative Query: Just find where you land after exactly 'x' steps
    int jump_exactly(int start, int x) {
        int curr = start;
        for (int k = 0; k < LOG; k++) {
            // If the k-th bit of x is 1, we need to take a jump of size 2^k
            if ((x >> k) & 1) {
                curr = jmp[curr][k];
            }
        }
        return curr;
    }
};

int nxt[N][LOG],prv[N][LOG];
int a[N];

vector<int> NGE(int n){
    stack<int>st;
    vector<int>res(n+1,n+1);
    for(int i = 1;i <= n ; i++){
        while(!st.empty() && a[st.top()] < a[i]){
            res[st.top()] = i; st.pop();
        }
        st.push(i);
    }
    return res;
}

vector<int> PGE(int n){
    stack<int>st;
    vector<int>res(n+1,0);
    for(int i = n;i >= 1  ; i--){
        while(!st.empty() && a[st.top()] < a[i]){
            res[st.top()] = i; st.pop();
        }
        st.push(i);
    }
    return res;
}


const int N = 200005;
const int LOG = 20;
int rmq[N][LOG];  

void build_rmq(int n){
    for (int i = 1; i <= n; i++) {
        rmq[i][0] = i;
    }
    for (int k = 1; k < LOG; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++){
            int left_idx = rmq[i][k - 1];
            int right_idx = rmq[i + (1 << (k - 1))][k - 1];
            if (a[left_idx] >= a[right_idx]) {
                rmq[i][k] = left_idx;
            } else {
                rmq[i][k] = right_idx;
            }
        }
    }
}

int query(int l, int r){
    int len = r - l + 1;
    //  63 - __builtin_clzll(len) for long long  
    int k = 31 - __builtin_clz(len); 
    int left_idx = rmq[l][k];
    int right_idx = rmq[r - (1 << k) + 1][k];

    if (a[left_idx] >= a[right_idx]) {
        return left_idx;
    } else {
        return right_idx;
    }
}


int calc(int l,int r){
    int m = query(l,r);
    int ret = 0;
    int cur = l;
    for(int k = LOG-1 ; k >= 0 ; k--){
        if(nxt[cur][k] <= m){
            ret += (1 << k);
            cur = nxt[cur][k];
        }
    }
    cur = r;
    for(int k = LOG-1 ; k >= 0 ; k--){
        if(prv[cur][k] >= m){
            ret += (1 << k);
            cur = prv[cur][k];
        }
    }
    return ret + 1;
}

void solve(int test_case) {
    int n,q; cin>>n>>q;
    for(int i = 1;i <= n ; i++) cin>>a[i];
    build_rmq(n);
    auto ng = NGE(n);
    auto pg = PGE(n);
    // init spt
    for(int i = 0 ; i <= n+1 ; i++){
        for(int lg = 0; lg < LOG ; lg++){
            nxt[i][lg] = n+1;
            prv[i][lg] = 0;
        }
    }
    for(int i = 1 ; i <= n ; i++){
        nxt[i][0] = ng[i];
        prv[i][0] = pg[i];
    }
    for(int k = 1 ;k < LOG ; k++){
        for(int i = 1; i <= n; i++){
            nxt[i][k] = nxt[nxt[i][k-1]][k-1];
            prv[i][k] = prv[prv[i][k-1]][k-1];
        }
    }

    for(int i = 0;i < q ; i++){
        int l,r; cin>>l>>r; 
        cout<<calc(l,r)<<ln;
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