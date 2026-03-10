#pragma GCC optimize ("Ofast")
#pragma GCC target ("avx,avx2")
#pragma GCC optimize("unroll-loops")

#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXN = 1000006;
const int V = 1024; // values < 1010 < 1024

int X[MAXN];
int rc[V];   // right-side frequency count
int hv[V];   // left-side frequency count
int pcnt[V]; // prefix count: pcnt[v] = #{r in right : r ^ m <= v}

void solve() {
    int n;
    scanf("%d", &n);

    memset(rc, 0, sizeof(rc));
    memset(hv, 0, sizeof(hv));

    for (int i = 0; i < n; i++) {
        scanf("%d", &X[i]);
        rc[X[i]]++;
    }

    ll sol = 0;

    for (int i = 0; i < n; i++) {
        int m = X[i];
        rc[m]--;

        // pcnt[v] = #{r in right : r ^ m <= v}
        //         = prefix sum of rc[x ^ m] over x = 0..v
        int running = 0;
        for (int x = 0; x < V; x++) {
            running += rc[x ^ m];
            pcnt[x] = running;
        }

        // contribution = sum_j hv[j] * pcnt[m | j]
        for (int j = 0; j < V; j++)
            sol += (ll)hv[j] * pcnt[m | j];

        hv[m]++;
    }

    printf("%lld\n", sol);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) solve();
}